/*
 * Copyright (c) 2019, Alliance for Open Media. All rights reserved
 *
 * This source code is subject to the terms of the BSD 2 Clause License and
 * the Alliance for Open Media Patent License 1.0. If the BSD 2 Clause License
 * was not distributed with this source code in the LICENSE file, you can
 * obtain it at www.aomedia.org/license/software. If the Alliance for Open
 * Media Patent License 1.0 was not distributed with this source code in the
 * PATENTS file, you can obtain it at www.aomedia.org/license/patent.
 */

#ifndef AOM_AV1_ENCODER_PARTITION_STRATEGY_H_
#define AOM_AV1_ENCODER_PARTITION_STRATEGY_H_

#include "av1/encoder/block.h"
#include "av1/encoder/encodeframe.h"
#include "av1/encoder/encodeframe_utils.h"
#include "av1/encoder/encodemb.h"
#include "av1/encoder/encoder.h"

#define FEATURE_SIZE_SMS_SPLIT_FAST 6
#define FEATURE_SIZE_SMS_SPLIT 17
#define FEATURE_SIZE_SMS_PRUNE_PART 25
#define FEATURE_SIZE_SMS_TERM_NONE 28
#define FEATURE_SIZE_FP_SMS_TERM_NONE 20
#define FEATURE_SIZE_MAX_MIN_PART_PRED 13
#define MAX_NUM_CLASSES_MAX_MIN_PART_PRED 4

#define FEATURE_SMS_NONE_FLAG 1
#define FEATURE_SMS_SPLIT_FLAG (1 << 1)
#define FEATURE_SMS_RECT_FLAG (1 << 2)

#define FEATURE_SMS_PRUNE_PART_FLAG \
  (FEATURE_SMS_NONE_FLAG | FEATURE_SMS_SPLIT_FLAG | FEATURE_SMS_RECT_FLAG)
#define FEATURE_SMS_SPLIT_MODEL_FLAG \
  (FEATURE_SMS_NONE_FLAG | FEATURE_SMS_SPLIT_FLAG)

void av1_intra_mode_cnn_partition(const AV1_COMMON *const cm, MACROBLOCK *x,
                                  int bsize, int label_idx,
                                  int *partition_none_allowed,
                                  int *partition_horz_allowed,
                                  int *partition_vert_allowed,
                                  int *do_rectangular_split,
                                  int *do_square_split);

// Performs a simple_motion_search with a single reference frame and extract
// the variance of residues. Then use the features to determine whether we want
// to go straight to splitting without trying PARTITION_NONE
void av1_simple_motion_search_based_split(
    AV1_COMP *const cpi, MACROBLOCK *x, SIMPLE_MOTION_DATA_TREE *sms_tree,
    int mi_row, int mi_col, BLOCK_SIZE bsize, int *partition_none_allowed,
    int *partition_horz_allowed, int *partition_vert_allowed,
    int *do_rectangular_split, int *do_square_split);

// Performs a simple_motion_search with two reference frames and extract
// the variance of residues. Then use the features to determine whether we want
// to prune some partitions.
void av1_simple_motion_search_prune_part(
    AV1_COMP *const cpi, MACROBLOCK *x, SIMPLE_MOTION_DATA_TREE *sms_tree,
    int mi_row, int mi_col, BLOCK_SIZE bsize, int *partition_none_allowed,
    int *partition_horz_allowed, int *partition_vert_allowed,
    int *do_square_split, int *do_rectangular_split, int *prune_horz,
    int *prune_vert);

#if !CONFIG_REALTIME_ONLY
// Early terminates PARTITION_NONE using simple_motion_search features and the
// rate, distortion, and rdcost of PARTITION_NONE. This is only called when:
//  - The frame is a show frame
//  - The frame is not intra only
//  - The current bsize is > BLOCK_8X8
//  - blk_row + blk_height/2 < total_rows and blk_col + blk_width/2 < total_cols
void av1_simple_motion_search_early_term_none(
    AV1_COMP *const cpi, MACROBLOCK *x, SIMPLE_MOTION_DATA_TREE *sms_tree,
    int mi_row, int mi_col, BLOCK_SIZE bsize, const RD_STATS *none_rdc,
    int *early_terminate);

// Get the features for selecting the max and min partition size. Currently this
// performs simple_motion_search on 16X16 subblocks of the current superblock,
// and then extract the statistics of sse and motion vectors as features.
void av1_get_max_min_partition_features(AV1_COMP *const cpi, MACROBLOCK *x,
                                        int mi_row, int mi_col,
                                        float *features);

// Predict the maximum BLOCK_SIZE to be used to encoder the current superblock.
BLOCK_SIZE av1_predict_max_partition(AV1_COMP *const cpi, MACROBLOCK *const x,
                                     const float *features);

// Attempts an early termination after PARTITION_SPLIT.
void av1_ml_early_term_after_split(AV1_COMP *const cpi, MACROBLOCK *const x,
                                   SIMPLE_MOTION_DATA_TREE *const sms_tree,
                                   BLOCK_SIZE bsize, int64_t best_rd,
                                   int64_t part_none_rd, int64_t part_split_rd,
                                   int64_t *split_block_rd, int mi_row,
                                   int mi_col,
                                   int *const terminate_partition_search);

// Use the rdcost ratio and source var ratio to prune PARTITION_HORZ and
// PARTITION_VERT.
// TODO(chiyotsai@google.com): Currently this model does not use q value and has
// no information about rectangular partitions. Preliminary experiments suggest
// that we can get better performance by adding in q_index and rectangular
// sse/var from SMS. We should retrain and tune this model later.
void av1_ml_prune_rect_partition(const AV1_COMP *const cpi,
                                 const MACROBLOCK *const x, BLOCK_SIZE bsize,
                                 int64_t best_rd, int64_t none_rd,
                                 int64_t *split_rd, int *const dst_prune_horz,
                                 int *const dst_prune_vert);

// Use a ML model to predict if horz_a, horz_b, vert_a, and vert_b should be
// considered.
void av1_ml_prune_ab_partition(BLOCK_SIZE bsize, int part_ctx, int var_ctx,
                               int64_t best_rd, int64_t horz_rd[2],
                               int64_t vert_rd[2], int64_t split_rd[4],
                               int *const horza_partition_allowed,
                               int *const horzb_partition_allowed,
                               int *const verta_partition_allowed,
                               int *const vertb_partition_allowed);

// Use a ML model to predict if horz4 and vert4 should be considered.
void av1_ml_prune_4_partition(const AV1_COMP *const cpi, MACROBLOCK *const x,
                              BLOCK_SIZE bsize, int part_ctx, int64_t best_rd,
                              int64_t horz_rd[2], int64_t vert_rd[2],
                              int64_t split_rd[4],
                              int *const partition_horz4_allowed,
                              int *const partition_vert4_allowed,
                              unsigned int pb_source_variance, int mi_row,
                              int mi_col);

// ML-based partition search breakout after PARTITION_NONE
int av1_ml_predict_breakout(const AV1_COMP *const cpi, BLOCK_SIZE bsize,
                            const MACROBLOCK *const x,
                            const RD_STATS *const rd_stats,
                            unsigned int pb_source_variance);

void av1_get_max_min_partition_size(AV1_COMP *cpi, ThreadData *td,
                                    BLOCK_SIZE *max_sq_size,
                                    BLOCK_SIZE *min_sq_size, int mi_row,
                                    int mi_col);
#endif  // !CONFIG_REALTIME_ONLY

#if CONFIG_EXT_RECUR_PARTITIONS
SimpleMotionData *av1_get_sms_data_entry(SimpleMotionDataBufs *sms_bufs,
                                         int mi_row, int mi_col,
                                         BLOCK_SIZE bsize, BLOCK_SIZE sb_size);

SimpleMotionData *av1_get_sms_data(AV1_COMP *const cpi,
                                   const TileInfo *const tile, MACROBLOCK *x,
                                   int mi_row, int mi_col, BLOCK_SIZE bsize);

static AOM_INLINE void av1_add_mode_search_context_to_cache(
    SimpleMotionData *sms_data, PICK_MODE_CONTEXT *ctx) {
  if (!sms_data->mode_cache[0] ||
      sms_data->mode_cache[0]->rd_stats.rdcost > ctx->rd_stats.rdcost) {
    sms_data->mode_cache[0] = ctx;
  }
}

static INLINE void av1_set_best_mode_cache(MACROBLOCK *x,
                                           PICK_MODE_CONTEXT *mode_cache[1]) {
  if (mode_cache[0] && mode_cache[0]->rd_stats.rate != INT_MAX) {
    x->inter_mode_cache = &mode_cache[0]->mic;
  } else {
    x->inter_mode_cache = NULL;
  }
}

void av1_cache_best_partition(SimpleMotionDataBufs *sms_bufs, int mi_row,
                              int mi_col, BLOCK_SIZE bsize, BLOCK_SIZE sb_size,
                              PARTITION_TYPE partition);

typedef struct SMSPartitionStats {
  const SimpleMotionData *sms_data[4];
  int num_sub_parts;
  int part_rate;
} SMSPartitionStats;

static INLINE void init_sms_partition_stats(SMSPartitionStats *stats) {
  memset(stats->sms_data, 0, sizeof(stats->sms_data));
  stats->num_sub_parts = 0;
  stats->part_rate = INT_MAX;
}

// Returns 1 if we think the old part is better and we should prune new
// partition, 0 otherwise.
int av1_prune_new_part(const SMSPartitionStats *old_part,
                       const SMSPartitionStats *new_part, int rdmult,
                       BLOCK_SIZE bsize);
#endif  // CONFIG_EXT_RECUR_PARTITIONS

// A simplified version of set_offsets meant to be used for
// simple_motion_search.
static INLINE void set_offsets_for_motion_search(const AV1_COMP *const cpi,
                                                 MACROBLOCK *const x,
                                                 int mi_row, int mi_col,
                                                 BLOCK_SIZE bsize) {
  const AV1_COMMON *const cm = &cpi->common;
  const int num_planes = av1_num_planes(cm);
  MACROBLOCKD *const xd = &x->e_mbd;
  const int mi_width = mi_size_wide[bsize];
  const int mi_height = mi_size_high[bsize];

  set_mode_info_offsets(cpi, x, xd, mi_row, mi_col);

  // Set up destination pointers.
  av1_setup_dst_planes(xd->plane, &cm->cur_frame->buf, mi_row, mi_col, 0,
                       num_planes, NULL);

  // Set up limit values for MV components.
  // Mv beyond the range do not produce new/different prediction block.
  x->mv_limits.row_min =
      -(((mi_row + mi_height) * MI_SIZE) + AOM_INTERP_EXTEND);
  x->mv_limits.col_min = -(((mi_col + mi_width) * MI_SIZE) + AOM_INTERP_EXTEND);
  x->mv_limits.row_max = (cm->mi_rows - mi_row) * MI_SIZE + AOM_INTERP_EXTEND;
  x->mv_limits.col_max = (cm->mi_cols - mi_col) * MI_SIZE + AOM_INTERP_EXTEND;

  CHROMA_REF_INFO chr_ref_info = {
    1, 0, mi_row, mi_col, AOMMAX(BLOCK_8X8, bsize), AOMMAX(BLOCK_8X8, bsize)
  };
  set_plane_n4(xd, bsize, num_planes, &chr_ref_info);

  // Set up distance of MB to edge of frame in 1/8th pel units.
  assert(!(mi_col & (mi_width - 1)) && !(mi_row & (mi_height - 1)));
  xd->mb_to_top_edge = -((mi_row * MI_SIZE) * 8);
  xd->mb_to_bottom_edge = ((cm->mi_rows - mi_height - mi_row) * MI_SIZE) * 8;
  xd->mb_to_left_edge = -((mi_col * MI_SIZE) * 8);
  xd->mb_to_right_edge = ((cm->mi_cols - mi_width - mi_col) * MI_SIZE) * 8;

  // Set up source buffers.
  av1_setup_src_planes(x, cpi->source, mi_row, mi_col, num_planes,
                       &chr_ref_info);
}

static INLINE void init_simple_motion_search_mvs(
    SIMPLE_MOTION_DATA_TREE *sms_tree) {
  av1_zero(sms_tree->mv_ref_fulls);

  av1_zero(sms_tree->sms_none_feat);
  av1_zero(sms_tree->sms_rect_feat);
  av1_zero(sms_tree->sms_none_valid);
  av1_zero(sms_tree->sms_rect_valid);

  if (sms_tree->block_size >= BLOCK_8X8) {
    init_simple_motion_search_mvs(sms_tree->split[0]);
    init_simple_motion_search_mvs(sms_tree->split[1]);
    init_simple_motion_search_mvs(sms_tree->split[2]);
    init_simple_motion_search_mvs(sms_tree->split[3]);
  }
}

PARTITION_TYPE av1_get_prev_partition(AV1_COMP *const cpi, MACROBLOCK *x,
                                      int mi_row, int mi_col, BLOCK_SIZE bsize);

#if CONFIG_EXT_RECUR_PARTITIONS
static INLINE void av1_init_sms_data_bufs(SimpleMotionDataBufs *data_bufs) {
  memset(data_bufs, 0, sizeof(*data_bufs));
}
#endif  // CONFIG_EXT_RECUR_PARTITIONS

static INLINE int is_full_sb(AV1_COMMON *const cm, int mi_row, int mi_col,
                             BLOCK_SIZE sb_size) {
  const int sb_mi_wide = mi_size_wide[sb_size];
  const int sb_mi_high = mi_size_high[sb_size];

  return (mi_row + sb_mi_high) <= cm->mi_rows &&
         (mi_col + sb_mi_wide) <= cm->mi_cols;
}

static INLINE int use_auto_max_partition(AV1_COMP *const cpi,
                                         BLOCK_SIZE sb_size, int mi_row,
                                         int mi_col) {
  assert(IMPLIES(cpi->gf_group.size > 0,
                 cpi->gf_group.index < cpi->gf_group.size));
  AV1_COMMON *const cm = &cpi->common;
  return !frame_is_intra_only(cm) &&
         cpi->sf.auto_max_partition_based_on_simple_motion != NOT_IN_USE &&
         sb_size == BLOCK_128X128 && is_full_sb(cm, mi_row, mi_col, sb_size) &&
         cpi->gf_group.update_type[cpi->gf_group.index] != OVERLAY_UPDATE &&
         cpi->gf_group.update_type[cpi->gf_group.index] != INTNL_OVERLAY_UPDATE;
}

#endif  // AOM_AV1_ENCODER_PARTITION_STRATEGY_H_
