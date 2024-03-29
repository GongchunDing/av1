/*
 * Copyright (c) 2016, Alliance for Open Media. All rights reserved
 *
 * This source code is subject to the terms of the BSD 2 Clause License and
 * the Alliance for Open Media Patent License 1.0. If the BSD 2 Clause License
 * was not distributed with this source code in the LICENSE file, you can
 * obtain it at www.aomedia.org/license/software. If the Alliance for Open
 * Media Patent License 1.0 was not distributed with this source code in the
 * PATENTS file, you can obtain it at www.aomedia.org/license/patent.
 */

#include <assert.h>
#include <stdio.h>
#include <limits.h>

#include "config/aom_config.h"
#include "config/aom_dsp_rtcd.h"
#include "config/aom_scale_rtcd.h"

#include "aom/aom_integer.h"
#include "aom_dsp/blend.h"

#include "av1/common/blockd.h"
#include "av1/common/mvref_common.h"
#include "av1/common/reconinter.h"
#include "av1/common/reconintra.h"
#include "av1/common/onyxc_int.h"
#include "av1/common/obmc.h"
#include "av1/encoder/reconinter_enc.h"

static INLINE void enc_calc_subpel_params(
    MACROBLOCKD *xd, const struct scale_factors *const sf, const MV *const mv,
    int plane, int pre_x, int pre_y, int x, int y, struct buf_2d *const pre_buf,
    int bw, int bh, const WarpTypesAllowed *const warp_types, int ref,
#if CONFIG_OPTFLOW_REFINEMENT
    int use_optflow_refinement,
#endif  // CONFIG_OPTFLOW_REFINEMENT
    const void *const args, uint8_t **pre, SubpelParams *subpel_params,
    int *src_stride) {
  (void)warp_types;
  (void)ref;
  (void)args;
  struct macroblockd_plane *const pd = &xd->plane[plane];
  const int is_scaled = av1_is_scaled(sf);
  if (is_scaled) {
    int ssx = pd->subsampling_x;
    int ssy = pd->subsampling_y;
    int orig_pos_y = (pre_y + y) << SUBPEL_BITS;
    orig_pos_y += mv->row * (1 << (1 - ssy));
    int orig_pos_x = (pre_x + x) << SUBPEL_BITS;
    orig_pos_x += mv->col * (1 << (1 - ssx));
    int pos_y = sf->scale_value_y(orig_pos_y, sf);
    int pos_x = sf->scale_value_x(orig_pos_x, sf);
    pos_x += SCALE_EXTRA_OFF;
    pos_y += SCALE_EXTRA_OFF;

    const int top = -AOM_LEFT_TOP_MARGIN_SCALED(ssy);
    const int left = -AOM_LEFT_TOP_MARGIN_SCALED(ssx);
    const int bottom = (pre_buf->height + AOM_INTERP_EXTEND)
                       << SCALE_SUBPEL_BITS;
    const int right = (pre_buf->width + AOM_INTERP_EXTEND) << SCALE_SUBPEL_BITS;
    pos_y = clamp(pos_y, top, bottom);
    pos_x = clamp(pos_x, left, right);

    *pre = pre_buf->buf0 + (pos_y >> SCALE_SUBPEL_BITS) * pre_buf->stride +
           (pos_x >> SCALE_SUBPEL_BITS);
    subpel_params->subpel_x = pos_x & SCALE_SUBPEL_MASK;
    subpel_params->subpel_y = pos_y & SCALE_SUBPEL_MASK;
    subpel_params->xs = sf->x_step_q4;
    subpel_params->ys = sf->y_step_q4;
  } else {
    const MV mv_q4 =
        clamp_mv_to_umv_border_sb(xd, mv, bw, bh,
#if CONFIG_OPTFLOW_REFINEMENT
                                  use_optflow_refinement,
#endif  // CONFIG_OPTFLOW_REFINEMENT
                                  pd->subsampling_x, pd->subsampling_y);
    subpel_params->xs = subpel_params->ys = SCALE_SUBPEL_SHIFTS;
    subpel_params->subpel_x = (mv_q4.col & SUBPEL_MASK) << SCALE_EXTRA_BITS;
    subpel_params->subpel_y = (mv_q4.row & SUBPEL_MASK) << SCALE_EXTRA_BITS;
    *pre = pre_buf->buf + (y + (mv_q4.row >> SUBPEL_BITS)) * pre_buf->stride +
           (x + (mv_q4.col >> SUBPEL_BITS));
  }
  *src_stride = pre_buf->stride;
}

static void enc_build_inter_predictors(const AV1_COMMON *cm, MACROBLOCKD *xd,
                                       int plane, MB_MODE_INFO *mi,
                                       int build_for_obmc, int bw, int bh,
                                       int mi_x, int mi_y, bool store_border) {
  const int border =
      store_border ? av1_calc_border(xd, plane, build_for_obmc) : 0;
  av1_build_inter_predictors(cm, xd, plane, mi, build_for_obmc, bw, bh, mi_x,
                             mi_y, enc_calc_subpel_params, NULL,
                             xd->plane[plane].dst.buf,
                             xd->plane[plane].dst.stride, border);
}

// If store_border is true, then the border is stored at a negative offset in
// xd->plane[plane].dst.buf. Otherwise, it is computed separately, used for
// the predictor, and only the predictor is stored in xd->plane[plane].dst.buf.
static void build_inter_predictors_for_plane(const AV1_COMMON *cm,
                                             MACROBLOCKD *xd, int mi_row,
                                             int mi_col, const BUFFER_SET *ctx,
                                             BLOCK_SIZE bsize, int plane_idx,
                                             bool store_border) {
  const struct macroblockd_plane *pd = &xd->plane[plane_idx];
  if (plane_idx && !xd->mi[0]->chroma_ref_info.is_chroma_ref) return;

  const int mi_x = mi_col * MI_SIZE;
  const int mi_y = mi_row * MI_SIZE;
  const int build_for_obmc = 0;
  if (!is_interintra_pred(xd->mi[0])) {
    enc_build_inter_predictors(cm, xd, plane_idx, xd->mi[0], build_for_obmc,
                               pd->width, pd->height, mi_x, mi_y, store_border);
    return;
  }

  BUFFER_SET default_ctx = { { NULL, NULL, NULL }, { 0, 0, 0 } };
  if (!ctx) {
    default_ctx.plane[plane_idx] = xd->plane[plane_idx].dst.buf;
    default_ctx.stride[plane_idx] = xd->plane[plane_idx].dst.stride;
    ctx = &default_ctx;
  }
  // If a border is needed, build the inter-predictor with one. A larger
  // buffer is needed, so alloc/dealloc as needed. If no border is needed,
  // it can be written directly into xd->plane[plane_idx].buf
  const int border = av1_calc_border(xd, plane_idx, build_for_obmc);
  uint8_t *interpred = xd->plane[plane_idx].dst.buf;
  int interpred_stride = xd->plane[plane_idx].dst.stride;
  if (!store_border && border > 0) {
    av1_alloc_buf_with_border(&interpred, &interpred_stride, border,
                              is_cur_buf_hbd(xd));
  }

  av1_build_inter_predictors(
      cm, xd, plane_idx, xd->mi[0], build_for_obmc, pd->width, pd->height, mi_x,
      mi_y, enc_calc_subpel_params, NULL, interpred, interpred_stride, border);
  // Stores the result in xd->plane[plane_idx].dst.buf.
  av1_build_interintra_predictors_sbp(cm, xd, interpred, interpred_stride, ctx,
                                      plane_idx, bsize, border);
  if (!store_border && border > 0) {
    av1_free_buf_with_border(interpred, interpred_stride, border,
                             is_cur_buf_hbd(xd));
  }
}

#if CONFIG_INTERINTRA_ML_DATA_COLLECT
void av1_enc_build_border_only_inter_predictor(const AV1_COMMON *cm,
                                               MACROBLOCKD *xd, int mi_row,
                                               int mi_col, int plane) {
  const struct macroblockd_plane *pd = &xd->plane[plane];
  const int mi_x = mi_col * MI_SIZE;
  const int mi_y = mi_row * MI_SIZE;
  const int build_for_obmc = 0;
  const bool store_border = true;
  enc_build_inter_predictors(cm, xd, plane, xd->mi[0], build_for_obmc,
                             pd->width, pd->height, mi_x, mi_y, store_border);
}
#endif  // CONFIG_INTERINTRA_ML_DATA_COLLECT

void av1_enc_build_inter_predictor(const AV1_COMMON *cm, MACROBLOCKD *xd,
                                   int mi_row, int mi_col,
                                   const BUFFER_SET *ctx, BLOCK_SIZE bsize,
                                   int plane_from, int plane_to) {
  for (int plane_idx = plane_from; plane_idx <= plane_to; ++plane_idx) {
    build_inter_predictors_for_plane(cm, xd, mi_row, mi_col, ctx, bsize,
                                     plane_idx, false);
  }
}

void av1_enc_build_border_inter_predictor(const AV1_COMMON *cm, MACROBLOCKD *xd,
                                          int mi_row, int mi_col,
                                          const BUFFER_SET *ctx,
                                          BLOCK_SIZE bsize, int plane_from,
                                          int plane_to) {
  for (int plane_idx = plane_from; plane_idx <= plane_to; ++plane_idx) {
    build_inter_predictors_for_plane(cm, xd, mi_row, mi_col, ctx, bsize,
                                     plane_idx, true);
  }
}

// TODO(sarahparker):
// av1_build_inter_predictor should be combined with
// av1_make_inter_predictor
void av1_build_inter_predictor(const uint8_t *src, int src_stride, uint8_t *dst,
                               int dst_stride, const MV *src_mv,
                               const struct scale_factors *sf, int w, int h,
                               ConvolveParams *conv_params,
                               int_interpfilters interp_filters,
                               const WarpTypesAllowed *warp_types, int p_col,
                               int p_row, int plane, int ref,
                               mv_precision precision, int x, int y,
                               const MACROBLOCKD *xd, int can_use_previous) {
  const int is_q4 = precision == MV_PRECISION_Q4;
  const MV mv_q4 = { is_q4 ? src_mv->row : src_mv->row * 2,
                     is_q4 ? src_mv->col : src_mv->col * 2 };
  MV32 mv = av1_scale_mv(&mv_q4, x, y, sf);
  mv.col += SCALE_EXTRA_OFF;
  mv.row += SCALE_EXTRA_OFF;

  const SubpelParams subpel_params = { sf->x_step_q4, sf->y_step_q4,
                                       mv.col & SCALE_SUBPEL_MASK,
                                       mv.row & SCALE_SUBPEL_MASK };
  src += (mv.row >> SCALE_SUBPEL_BITS) * src_stride +
         (mv.col >> SCALE_SUBPEL_BITS);

  const int border = 0;
  av1_make_inter_predictor(src, src_stride, dst, dst_stride, &subpel_params, sf,
                           w, h, conv_params, interp_filters, warp_types, p_col,
                           p_row, plane, ref, xd->mi[0], 0, xd,
                           can_use_previous, border);
}

static INLINE void build_prediction_by_above_pred(
    MACROBLOCKD *xd, int rel_mi_col, uint8_t above_mi_width,
    MB_MODE_INFO *above_mbmi, void *fun_ctxt, const int num_planes) {
  struct build_prediction_ctxt *ctxt = (struct build_prediction_ctxt *)fun_ctxt;
  const int above_mi_col = xd->mi_col + rel_mi_col;
  int mi_x, mi_y;
  MB_MODE_INFO backup_mbmi = *above_mbmi;

  av1_setup_build_prediction_by_above_pred(xd, rel_mi_col, above_mi_width,
                                           &backup_mbmi, ctxt, num_planes);

  mi_x = above_mi_col << MI_SIZE_LOG2;
  mi_y = xd->mi_row << MI_SIZE_LOG2;

  const BLOCK_SIZE bsize = xd->mi[0]->sb_type;
  const int mi_row = xd->mi_row;
  const int mi_col = xd->mi_row;

  for (int j = 0; j < num_planes; ++j) {
    const struct macroblockd_plane *pd = &xd->plane[j];
    int bw = (above_mi_width * MI_SIZE) >> pd->subsampling_x;
    int bh = clamp(block_size_high[bsize] >> (pd->subsampling_y + 1), 4,
                   block_size_high[BLOCK_64X64] >> (pd->subsampling_y + 1));

    if (av1_skip_u4x4_pred_in_obmc(mi_row, mi_col, bsize, pd, 0)) continue;
    enc_build_inter_predictors(ctxt->cm, xd, j, &backup_mbmi, 1, bw, bh, mi_x,
                               mi_y, false /* store_border */);
  }
}

void av1_build_prediction_by_above_preds(const AV1_COMMON *cm, MACROBLOCKD *xd,
                                         uint8_t *tmp_buf[MAX_MB_PLANE],
                                         int tmp_width[MAX_MB_PLANE],
                                         int tmp_height[MAX_MB_PLANE],
                                         int tmp_stride[MAX_MB_PLANE]) {
  if (!xd->up_available) return;

  // Adjust mb_to_bottom_edge to have the correct value for the OBMC
  // prediction block. This is half the height of the original block,
  // except for 128-wide blocks, where we only use a height of 32.
  int this_height = xd->n4_h * MI_SIZE;
  int pred_height = AOMMIN(this_height / 2, 32);
  xd->mb_to_bottom_edge += (this_height - pred_height) * 8;

  struct build_prediction_ctxt ctxt = { cm,         tmp_buf,
                                        tmp_width,  tmp_height,
                                        tmp_stride, xd->mb_to_right_edge };
  BLOCK_SIZE bsize = xd->mi[0]->sb_type;
  foreach_overlappable_nb_above(cm, xd,
                                max_neighbor_obmc[mi_size_wide_log2[bsize]],
                                build_prediction_by_above_pred, &ctxt);

  xd->mb_to_left_edge = -((xd->mi_col * MI_SIZE) * 8);
  xd->mb_to_right_edge = ctxt.mb_to_far_edge;
  xd->mb_to_bottom_edge -= (this_height - pred_height) * 8;
}

static INLINE void build_prediction_by_left_pred(
    MACROBLOCKD *xd, int rel_mi_row, uint8_t left_mi_height,
    MB_MODE_INFO *left_mbmi, void *fun_ctxt, const int num_planes) {
  struct build_prediction_ctxt *ctxt = (struct build_prediction_ctxt *)fun_ctxt;
  const int left_mi_row = xd->mi_row + rel_mi_row;
  int mi_x, mi_y;
  MB_MODE_INFO backup_mbmi = *left_mbmi;

  av1_setup_build_prediction_by_left_pred(xd, rel_mi_row, left_mi_height,
                                          &backup_mbmi, ctxt, num_planes);
  mi_x = xd->mi_col << MI_SIZE_LOG2;
  mi_y = left_mi_row << MI_SIZE_LOG2;
  const BLOCK_SIZE bsize = xd->mi[0]->sb_type;
  const int mi_row = -xd->mb_to_top_edge >> (3 + MI_SIZE_LOG2);
  const int mi_col = -xd->mb_to_left_edge >> (3 + MI_SIZE_LOG2);

  for (int j = 0; j < num_planes; ++j) {
    const struct macroblockd_plane *pd = &xd->plane[j];
    int bw = clamp(block_size_wide[bsize] >> (pd->subsampling_x + 1), 4,
                   block_size_wide[BLOCK_64X64] >> (pd->subsampling_x + 1));
    int bh = (left_mi_height << MI_SIZE_LOG2) >> pd->subsampling_y;

    if (av1_skip_u4x4_pred_in_obmc(mi_row, mi_col, bsize, pd, 1)) continue;
    enc_build_inter_predictors(ctxt->cm, xd, j, &backup_mbmi, 1, bw, bh, mi_x,
                               mi_y, false /* store_border */);
  }
}

void av1_build_prediction_by_left_preds(const AV1_COMMON *cm, MACROBLOCKD *xd,
                                        uint8_t *tmp_buf[MAX_MB_PLANE],
                                        int tmp_width[MAX_MB_PLANE],
                                        int tmp_height[MAX_MB_PLANE],
                                        int tmp_stride[MAX_MB_PLANE]) {
  if (!xd->left_available) return;

  // Adjust mb_to_right_edge to have the correct value for the OBMC
  // prediction block. This is half the width of the original block,
  // except for 128-wide blocks, where we only use a width of 32.
  int this_width = xd->n4_w * MI_SIZE;
  int pred_width = AOMMIN(this_width / 2, 32);
  xd->mb_to_right_edge += (this_width - pred_width) * 8;

  struct build_prediction_ctxt ctxt = { cm,         tmp_buf,
                                        tmp_width,  tmp_height,
                                        tmp_stride, xd->mb_to_bottom_edge };
  BLOCK_SIZE bsize = xd->mi[0]->sb_type;
  foreach_overlappable_nb_left(cm, xd,
                               max_neighbor_obmc[mi_size_high_log2[bsize]],
                               build_prediction_by_left_pred, &ctxt);

  xd->mb_to_top_edge = -((xd->mi_row * MI_SIZE) * 8);
  xd->mb_to_right_edge -= (this_width - pred_width) * 8;
  xd->mb_to_bottom_edge = ctxt.mb_to_far_edge;
}

void av1_build_obmc_inter_predictors_sb(const AV1_COMMON *cm, MACROBLOCKD *xd) {
  const int num_planes = av1_num_planes(cm);
  uint8_t *dst_buf1[MAX_MB_PLANE], *dst_buf2[MAX_MB_PLANE];
  int dst_stride1[MAX_MB_PLANE] = { MAX_SB_SIZE, MAX_SB_SIZE, MAX_SB_SIZE };
  int dst_stride2[MAX_MB_PLANE] = { MAX_SB_SIZE, MAX_SB_SIZE, MAX_SB_SIZE };
  int dst_width1[MAX_MB_PLANE] = { MAX_SB_SIZE, MAX_SB_SIZE, MAX_SB_SIZE };
  int dst_width2[MAX_MB_PLANE] = { MAX_SB_SIZE, MAX_SB_SIZE, MAX_SB_SIZE };
  int dst_height1[MAX_MB_PLANE] = { MAX_SB_SIZE, MAX_SB_SIZE, MAX_SB_SIZE };
  int dst_height2[MAX_MB_PLANE] = { MAX_SB_SIZE, MAX_SB_SIZE, MAX_SB_SIZE };

  if (is_cur_buf_hbd(xd)) {
    int len = sizeof(uint16_t);
    dst_buf1[0] = CONVERT_TO_BYTEPTR(xd->tmp_obmc_bufs[0]);
    dst_buf1[1] =
        CONVERT_TO_BYTEPTR(xd->tmp_obmc_bufs[0] + MAX_SB_SQUARE * len);
    dst_buf1[2] =
        CONVERT_TO_BYTEPTR(xd->tmp_obmc_bufs[0] + MAX_SB_SQUARE * 2 * len);
    dst_buf2[0] = CONVERT_TO_BYTEPTR(xd->tmp_obmc_bufs[1]);
    dst_buf2[1] =
        CONVERT_TO_BYTEPTR(xd->tmp_obmc_bufs[1] + MAX_SB_SQUARE * len);
    dst_buf2[2] =
        CONVERT_TO_BYTEPTR(xd->tmp_obmc_bufs[1] + MAX_SB_SQUARE * 2 * len);
  } else {
    dst_buf1[0] = xd->tmp_obmc_bufs[0];
    dst_buf1[1] = xd->tmp_obmc_bufs[0] + MAX_SB_SQUARE;
    dst_buf1[2] = xd->tmp_obmc_bufs[0] + MAX_SB_SQUARE * 2;
    dst_buf2[0] = xd->tmp_obmc_bufs[1];
    dst_buf2[1] = xd->tmp_obmc_bufs[1] + MAX_SB_SQUARE;
    dst_buf2[2] = xd->tmp_obmc_bufs[1] + MAX_SB_SQUARE * 2;
  }

  const int mi_row = xd->mi_row;
  const int mi_col = xd->mi_col;
  av1_build_prediction_by_above_preds(cm, xd, dst_buf1, dst_width1, dst_height1,
                                      dst_stride1);
  av1_build_prediction_by_left_preds(cm, xd, dst_buf2, dst_width2, dst_height2,
                                     dst_stride2);
  av1_setup_dst_planes(xd->plane, &cm->cur_frame->buf, mi_row, mi_col, 0,
                       num_planes, &xd->mi[0]->chroma_ref_info);
  av1_build_obmc_inter_prediction(cm, xd, dst_buf1, dst_stride1, dst_buf2,
                                  dst_stride2);
}

// Builds the inter-predictor for the single ref case
// for use in the encoder to search the wedges efficiently.
static void build_inter_predictors_single_buf(MACROBLOCKD *xd, int plane,
                                              int bw, int bh, int x, int y,
                                              int w, int h, int mi_x, int mi_y,
                                              int ref, uint8_t *const ext_dst,
                                              int ext_dst_stride,
                                              int can_use_previous) {
  struct macroblockd_plane *const pd = &xd->plane[plane];
  const MB_MODE_INFO *mi = xd->mi[0];

  const struct scale_factors *const sf = xd->block_ref_scale_factors[ref];
  struct buf_2d *const pre_buf = &pd->pre[ref];
  uint8_t *const dst = get_buf_by_bd(xd, ext_dst) + ext_dst_stride * y + x;
  const MV mv = mi->mv[ref].as_mv;

  ConvolveParams conv_params = get_conv_params(0, plane, xd->bd);
  const WarpedMotionParams *const wm = &xd->global_motion[mi->ref_frame[ref]];
  const WarpTypesAllowed warp_types = { is_global_mv_block(mi, wm->wmtype),
                                        mi->motion_mode == WARPED_CAUSAL };
  const int pre_x = (mi_x) >> pd->subsampling_x;
  const int pre_y = (mi_y) >> pd->subsampling_y;
  uint8_t *pre;
  SubpelParams subpel_params;
  int src_stride;
  enc_calc_subpel_params(xd, sf, &mv, plane, pre_x, pre_y, x, y, pre_buf, bw,
                         bh, &warp_types, ref,
#if CONFIG_OPTFLOW_REFINEMENT
                         0,
#endif  // CONFIG_OPTFLOW_REFINEMENT
                         NULL, &pre, &subpel_params, &src_stride);

  const int border = 0;
  av1_make_inter_predictor(pre, src_stride, dst, ext_dst_stride, &subpel_params,
                           sf, w, h, &conv_params, mi->interp_filters,
                           &warp_types, pre_x + x, pre_y + y, plane, ref, mi, 0,
                           xd, can_use_previous, border);
}

void av1_build_inter_predictors_for_planes_single_buf(
    MACROBLOCKD *xd, BLOCK_SIZE bsize, int plane_from, int plane_to, int ref,
    uint8_t *ext_dst[3], int ext_dst_stride[3], int can_use_previous) {
  assert(bsize < BLOCK_SIZES_ALL);
  const int mi_row = xd->mi_row;
  const int mi_col = xd->mi_col;
  const int mi_x = mi_col * MI_SIZE;
  const int mi_y = mi_row * MI_SIZE;
  for (int plane = plane_from; plane <= plane_to; ++plane) {
    const BLOCK_SIZE bsize_base =
        plane ? xd->mi[0]->chroma_ref_info.bsize_base : bsize;
    const BLOCK_SIZE plane_bsize =
        get_plane_block_size(bsize_base, xd->plane[plane].subsampling_x,
                             xd->plane[plane].subsampling_y);
    assert(plane_bsize < BLOCK_SIZES_ALL);
    const int bw = block_size_wide[plane_bsize];
    const int bh = block_size_high[plane_bsize];
    build_inter_predictors_single_buf(xd, plane, bw, bh, 0, 0, bw, bh, mi_x,
                                      mi_y, ref, ext_dst[plane],
                                      ext_dst_stride[plane], can_use_previous);
  }
}

static void build_masked_compound(
    uint8_t *dst, int dst_stride, const uint8_t *src0, int src0_stride,
    const uint8_t *src1, int src1_stride,
    const INTERINTER_COMPOUND_DATA *const comp_data, BLOCK_SIZE sb_type, int h,
    int w) {
  // Derive subsampling from h and w passed in. May be refactored to
  // pass in subsampling factors directly.
  const int subh = (2 << mi_size_high_log2[sb_type]) == h;
  const int subw = (2 << mi_size_wide_log2[sb_type]) == w;
  const uint8_t *mask = av1_get_compound_type_mask(comp_data, sb_type);
  aom_blend_a64_mask(dst, dst_stride, src0, src0_stride, src1, src1_stride,
                     mask, block_size_wide[sb_type], w, h, subw, subh);
}

static void build_masked_compound_highbd(
    uint8_t *dst_8, int dst_stride, const uint8_t *src0_8, int src0_stride,
    const uint8_t *src1_8, int src1_stride,
    const INTERINTER_COMPOUND_DATA *const comp_data, BLOCK_SIZE sb_type, int h,
    int w, int bd) {
  // Derive subsampling from h and w passed in. May be refactored to
  // pass in subsampling factors directly.
  const int subh = (2 << mi_size_high_log2[sb_type]) == h;
  const int subw = (2 << mi_size_wide_log2[sb_type]) == w;
  const uint8_t *mask = av1_get_compound_type_mask(comp_data, sb_type);
  // const uint8_t *mask =
  //     av1_get_contiguous_soft_mask(wedge_index, wedge_sign, sb_type);
  aom_highbd_blend_a64_mask(dst_8, dst_stride, src0_8, src0_stride, src1_8,
                            src1_stride, mask, block_size_wide[sb_type], w, h,
                            subw, subh, bd);
}

static void build_wedge_inter_predictor_from_buf(
    MACROBLOCKD *xd, int plane, int x, int y, int w, int h, uint8_t *ext_dst0,
    int ext_dst_stride0, uint8_t *ext_dst1, int ext_dst_stride1) {
  MB_MODE_INFO *const mbmi = xd->mi[0];
  const int is_compound = has_second_ref(mbmi);
  MACROBLOCKD_PLANE *const pd = &xd->plane[plane];
  struct buf_2d *const dst_buf = &pd->dst;
  uint8_t *const dst = dst_buf->buf + dst_buf->stride * y + x;
  mbmi->interinter_comp.seg_mask = xd->seg_mask;
  const INTERINTER_COMPOUND_DATA *comp_data = &mbmi->interinter_comp;
  const int is_hbd = is_cur_buf_hbd(xd);

  if (is_compound && is_masked_compound_type(comp_data->type)) {
    if (!plane && comp_data->type == COMPOUND_DIFFWTD) {
#if CONFIG_CTX_ADAPT_LOG_WEIGHT || CONFIG_DIFFWTD_42
      if (is_hbd) {
        av1_build_compound_diffwtd_mask_highbd_c(
            comp_data->seg_mask, comp_data->mask_type,
            CONVERT_TO_BYTEPTR(ext_dst0), ext_dst_stride0,
            CONVERT_TO_BYTEPTR(ext_dst1), ext_dst_stride1, h, w, xd->bd);
      } else {
        av1_build_compound_diffwtd_mask_c(
            comp_data->seg_mask, comp_data->mask_type, ext_dst0,
            ext_dst_stride0, ext_dst1, ext_dst_stride1, h, w);
      }
#else
      if (is_hbd) {
        av1_build_compound_diffwtd_mask_highbd(
            comp_data->seg_mask, comp_data->mask_type,
            CONVERT_TO_BYTEPTR(ext_dst0), ext_dst_stride0,
            CONVERT_TO_BYTEPTR(ext_dst1), ext_dst_stride1, h, w, xd->bd);
      } else {
        av1_build_compound_diffwtd_mask(
            comp_data->seg_mask, comp_data->mask_type, ext_dst0,
            ext_dst_stride0, ext_dst1, ext_dst_stride1, h, w);
      }
#endif  // CONFIG_CTX_ADAPT_LOG_WEIGHT || CONFIG_DIFFWTD_42
    }

    if (is_hbd) {
      build_masked_compound_highbd(
          dst, dst_buf->stride, CONVERT_TO_BYTEPTR(ext_dst0), ext_dst_stride0,
          CONVERT_TO_BYTEPTR(ext_dst1), ext_dst_stride1, comp_data,
          mbmi->sb_type, h, w, xd->bd);
    } else {
      build_masked_compound(dst, dst_buf->stride, ext_dst0, ext_dst_stride0,
                            ext_dst1, ext_dst_stride1, comp_data, mbmi->sb_type,
                            h, w);
    }
  } else {
    if (is_hbd) {
      aom_highbd_convolve_copy(CONVERT_TO_BYTEPTR(ext_dst0), ext_dst_stride0,
                               dst, dst_buf->stride, NULL, 0, NULL, 0, w, h,
                               xd->bd);
    } else {
      aom_convolve_copy(ext_dst0, ext_dst_stride0, dst, dst_buf->stride, w, h);
    }
  }
}

void av1_build_wedge_inter_predictor_from_buf(MACROBLOCKD *xd, BLOCK_SIZE bsize,
                                              int plane_from, int plane_to,
                                              uint8_t *ext_dst0[3],
                                              int ext_dst_stride0[3],
                                              uint8_t *ext_dst1[3],
                                              int ext_dst_stride1[3]) {
  int plane;
  assert(bsize < BLOCK_SIZES_ALL);
  for (plane = plane_from; plane <= plane_to; ++plane) {
    const BLOCK_SIZE bsize_base =
        plane ? xd->mi[0]->chroma_ref_info.bsize_base : bsize;
    const BLOCK_SIZE plane_bsize =
        get_plane_block_size(bsize_base, xd->plane[plane].subsampling_x,
                             xd->plane[plane].subsampling_y);
    assert(plane_bsize < BLOCK_SIZES_ALL);
    const int bw = block_size_wide[plane_bsize];
    const int bh = block_size_high[plane_bsize];
    build_wedge_inter_predictor_from_buf(
        xd, plane, 0, 0, bw, bh, ext_dst0[plane], ext_dst_stride0[plane],
        ext_dst1[plane], ext_dst_stride1[plane]);
  }
}
