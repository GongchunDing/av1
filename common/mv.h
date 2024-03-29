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

#ifndef AOM_AV1_COMMON_MV_H_
#define AOM_AV1_COMMON_MV_H_

#include <stdlib.h>

#include "av1/common/common.h"
#include "av1/common/common_data.h"
#include "aom_dsp/aom_filter.h"

#ifdef __cplusplus
extern "C" {
#endif

#define INVALID_MV 0x80008000

typedef struct mv {
  int16_t row;
  int16_t col;
} MV;

static const MV kZeroMv = { 0, 0 };

typedef union int_mv {
  uint32_t as_int;
  MV as_mv;
} int_mv; /* facilitates faster equality tests and copies */

typedef struct mv32 {
  int32_t row;
  int32_t col;
} MV32;

enum {
  MV_SUBPEL_NONE = 0,
  MV_SUBPEL_HALF_PRECISION = 1,
  MV_SUBPEL_QTR_PRECISION = 2,
  MV_SUBPEL_EIGHTH_PRECISION = 3,
  MV_SUBPEL_PRECISIONS,
} SENUM1BYTE(MvSubpelPrecision);

// DISALLOW_ONE_DOWN_FLEX_MVRES 0 => allow all possible down precisions
// DISALLOW_ONE_DOWN_FLEX_MVRES 1 => allow all possible down precisions except 1
// DISALLOW_ONE_DOWN_FLEX_MVRES 2 => allow only 0 and 2 down precisions
#if CONFIG_FLEX_MVRES
#define DISALLOW_ONE_DOWN_FLEX_MVRES 2  // Choose one of the above
#define MV_PREC_DOWN_CONTEXTS 2
#else
#define DISALLOW_ONE_DOWN_FLEX_MVRES 0
#endif  // CONFIG_FLEX_MVRES
#define FLEX_MV_COSTS_SIZE \
  ((MV_SUBPEL_PRECISIONS) - (DISALLOW_ONE_DOWN_FLEX_MVRES))
#define NUM_PB_FLEX_QUALIFIED_MAX_PREC \
  ((MV_SUBPEL_PRECISIONS) - (MV_SUBPEL_QTR_PRECISION))

// Whether to adapt at the sb level
#if CONFIG_SB_FLEX_MVRES
#define ENABLE_SB_RES 1
#else
#define ENABLE_SB_RES 0
#endif  // CONFIG_SB_FLEX_MVRES
// Whether to adapt at the pb level
#if CONFIG_PB_FLEX_MVRES
#define ENABLE_PB_RES 1
#else
#define ENABLE_PB_RES 0
#endif

#if CONFIG_COMPANDED_MV
#define COMPANDED_INTMV_THRESH_QTR 96
#define COMPANDED_INTMV_THRESH_HALF 256
#endif  // CONFIG_COMPANDED_MV

// Bits of precision used for the model
#define WARPEDMODEL_PREC_BITS 16
#define WARPEDMODEL_ROW3HOMO_PREC_BITS 16

#define WARPEDMODEL_TRANS_CLAMP (128 << WARPEDMODEL_PREC_BITS)
#define WARPEDMODEL_NONDIAGAFFINE_CLAMP (1 << (WARPEDMODEL_PREC_BITS - 3))
#define WARPEDMODEL_ROW3HOMO_CLAMP (1 << (WARPEDMODEL_PREC_BITS - 2))

// Bits of subpel precision for warped interpolation
#define WARPEDPIXEL_PREC_BITS 6
#define WARPEDPIXEL_PREC_SHIFTS (1 << WARPEDPIXEL_PREC_BITS)

#define WARP_PARAM_REDUCE_BITS 6

#define WARPEDDIFF_PREC_BITS (WARPEDMODEL_PREC_BITS - WARPEDPIXEL_PREC_BITS)

/* clang-format off */
enum {
  IDENTITY = 0,      // identity transformation, 0-parameter
  TRANSLATION = 1,   // translational motion 2-parameter
  ROTZOOM = 2,       // simplified affine with rotation + zoom only, 4-parameter
  AFFINE = 3,        // affine, 6-parameter
  TRANS_TYPES,
} UENUM1BYTE(TransformationType);
/* clang-format on */

// Number of types used for global motion (must be >= 3 and <= TRANS_TYPES)
// The following can be useful:
// GLOBAL_TRANS_TYPES 3 - up to rotation-zoom
// GLOBAL_TRANS_TYPES 4 - up to affine
// GLOBAL_TRANS_TYPES 6 - up to hor/ver trapezoids
// GLOBAL_TRANS_TYPES 7 - up to full homography
#define GLOBAL_TRANS_TYPES 4

typedef struct {
  int global_warp_allowed;
  int local_warp_allowed;
} WarpTypesAllowed;

// number of parameters used by each transformation in TransformationTypes
static const int trans_model_params[TRANS_TYPES] = { 0, 2, 4, 6 };

// The order of values in the wmmat matrix below is best described
// by the homography:
//      [x'     (m2 m3 m0   [x
//  z .  y'  =   m4 m5 m1 *  y
//       1]      m6 m7 1)    1]
typedef struct {
  int32_t wmmat[8];
  int16_t alpha, beta, gamma, delta;
  TransformationType wmtype;
  int8_t invalid;
} WarpedMotionParams;

/* clang-format off */
static const WarpedMotionParams default_warp_params = {
  { 0, 0, (1 << WARPEDMODEL_PREC_BITS), 0, 0, (1 << WARPEDMODEL_PREC_BITS), 0,
    0 },
  0, 0, 0, 0,
  IDENTITY,
  0,
};
/* clang-format on */

// The following constants describe the various precisions
// of different parameters in the global motion experiment.
//
// Given the general homography:
//      [x'     (a  b  c   [x
//  z .  y'  =   d  e  f *  y
//       1]      g  h  i)    1]
//
// Constants using the name ALPHA here are related to parameters
// a, b, d, e. Constants using the name TRANS are related
// to parameters c and f.
//
// Anything ending in PREC_BITS is the number of bits of precision
// to maintain when converting from double to integer.
//
// The ABS parameters are used to create an upper and lower bound
// for each parameter. In other words, after a parameter is integerized
// it is clamped between -(1 << ABS_XXX_BITS) and (1 << ABS_XXX_BITS).
//
// XXX_PREC_DIFF and XXX_DECODE_FACTOR
// are computed once here to prevent repetitive
// computation on the decoder side. These are
// to allow the global motion parameters to be encoded in a lower
// precision than the warped model precision. This means that they
// need to be changed to warped precision when they are decoded.
//
// XX_MIN, XX_MAX are also computed to avoid repeated computation

#define SUBEXPFIN_K 3
#define GM_TRANS_PREC_BITS 6
#define GM_ABS_TRANS_BITS 12
#define GM_ABS_TRANS_ONLY_BITS (GM_ABS_TRANS_BITS - GM_TRANS_PREC_BITS + 3)
#define GM_TRANS_PREC_DIFF (WARPEDMODEL_PREC_BITS - GM_TRANS_PREC_BITS)
#define GM_TRANS_ONLY_PREC_DIFF (WARPEDMODEL_PREC_BITS - 3)
#define GM_TRANS_DECODE_FACTOR (1 << GM_TRANS_PREC_DIFF)
#define GM_TRANS_ONLY_DECODE_FACTOR (1 << GM_TRANS_ONLY_PREC_DIFF)

#define GM_ALPHA_PREC_BITS 15
#define GM_ABS_ALPHA_BITS 12
#define GM_ALPHA_PREC_DIFF (WARPEDMODEL_PREC_BITS - GM_ALPHA_PREC_BITS)
#define GM_ALPHA_DECODE_FACTOR (1 << GM_ALPHA_PREC_DIFF)

#define GM_ROW3HOMO_PREC_BITS 16
#define GM_ABS_ROW3HOMO_BITS 11
#define GM_ROW3HOMO_PREC_DIFF \
  (WARPEDMODEL_ROW3HOMO_PREC_BITS - GM_ROW3HOMO_PREC_BITS)
#define GM_ROW3HOMO_DECODE_FACTOR (1 << GM_ROW3HOMO_PREC_DIFF)

#define GM_TRANS_MAX (1 << GM_ABS_TRANS_BITS)
#define GM_ALPHA_MAX (1 << GM_ABS_ALPHA_BITS)
#define GM_ROW3HOMO_MAX (1 << GM_ABS_ROW3HOMO_BITS)

#define GM_TRANS_MIN -GM_TRANS_MAX
#define GM_ALPHA_MIN -GM_ALPHA_MAX
#define GM_ROW3HOMO_MIN -GM_ROW3HOMO_MAX

static INLINE int block_center_x(int mi_col, BLOCK_SIZE bs) {
  const int bw = block_size_wide[bs];
  return mi_col * MI_SIZE + bw / 2 - 1;
}

static INLINE int block_center_y(int mi_row, BLOCK_SIZE bs) {
  const int bh = block_size_high[bs];
  return mi_row * MI_SIZE + bh / 2 - 1;
}

static INLINE int convert_to_trans_prec(MvSubpelPrecision precision, int coor) {
  if (precision > MV_SUBPEL_QTR_PRECISION)
    return ROUND_POWER_OF_TWO_SIGNED(coor, WARPEDMODEL_PREC_BITS - 3);
  else
    return ROUND_POWER_OF_TWO_SIGNED(coor, WARPEDMODEL_PREC_BITS - 2) * 2;
}

static INLINE void lower_mv_precision(MV *mv, MvSubpelPrecision precision) {
  const int radix = (1 << (MV_SUBPEL_EIGHTH_PRECISION - precision));
  if (radix == 1) return;
  int mod = (mv->row % radix);
  if (mod != 0) {
    mv->row -= mod;
    if (abs(mod) > radix / 2) {
      if (mod > 0) {
        mv->row += radix;
      } else {
        mv->row -= radix;
      }
    }
  }

  mod = (mv->col % radix);
  if (mod != 0) {
    mv->col -= mod;
    if (abs(mod) > radix / 2) {
      if (mod > 0) {
        mv->col += radix;
      } else {
        mv->col -= radix;
      }
    }
  }
}
// Convert a global motion vector into a motion vector at the centre of the
// given block.
//
// The resulting motion vector will have three fractional bits of precision. If
// allow_hp is zero, the bottom bit will always be zero. If CONFIG_AMVR and
// is_integer is true, the bottom three bits will be zero (so the motion vector
// represents an integer)
static INLINE int_mv gm_get_motion_vector(const WarpedMotionParams *gm,
                                          MvSubpelPrecision precision,
                                          BLOCK_SIZE bsize, int mi_col,
                                          int mi_row) {
  int_mv res;

  if (gm->wmtype == IDENTITY) {
    res.as_int = 0;
    return res;
  }

  const int32_t *mat = gm->wmmat;
  int x, y, tx, ty;

  if (gm->wmtype == TRANSLATION) {
    // All global motion vectors are stored with WARPEDMODEL_PREC_BITS (16)
    // bits of fractional precision. The offset for a translation is stored in
    // entries 0 and 1. For translations, all but the top three (two if
    // cm->fr_mv_precision is qtr) fractional bits are always zero.
    //
    // After the right shifts, there are 3 fractional bits of precision. If
    // allow_hp is false, the bottom bit is always zero (so we don't need a
    // call to convert_to_trans_prec here)
    res.as_mv.row = gm->wmmat[0] >> GM_TRANS_ONLY_PREC_DIFF;
    res.as_mv.col = gm->wmmat[1] >> GM_TRANS_ONLY_PREC_DIFF;
    assert(IMPLIES(1 & (res.as_mv.row | res.as_mv.col),
                   precision > MV_SUBPEL_QTR_PRECISION));
    lower_mv_precision(&res.as_mv, precision);
    return res;
  }

  x = block_center_x(mi_col, bsize);
  y = block_center_y(mi_row, bsize);

  if (gm->wmtype == ROTZOOM) {
    assert(gm->wmmat[5] == gm->wmmat[2]);
    assert(gm->wmmat[4] == -gm->wmmat[3]);
  }

  const int xc =
      (mat[2] - (1 << WARPEDMODEL_PREC_BITS)) * x + mat[3] * y + mat[0];
  const int yc =
      mat[4] * x + (mat[5] - (1 << WARPEDMODEL_PREC_BITS)) * y + mat[1];
  tx = convert_to_trans_prec(precision, xc);
  ty = convert_to_trans_prec(precision, yc);

  res.as_mv.row = ty;
  res.as_mv.col = tx;

  lower_mv_precision(&res.as_mv, precision);
  return res;
}

static INLINE TransformationType get_wmtype(const WarpedMotionParams *gm) {
  if (gm->wmmat[5] == (1 << WARPEDMODEL_PREC_BITS) && !gm->wmmat[4] &&
      gm->wmmat[2] == (1 << WARPEDMODEL_PREC_BITS) && !gm->wmmat[3]) {
    return ((!gm->wmmat[1] && !gm->wmmat[0]) ? IDENTITY : TRANSLATION);
  }
  if (gm->wmmat[2] == gm->wmmat[5] && gm->wmmat[3] == -gm->wmmat[4])
    return ROTZOOM;
  else
    return AFFINE;
}

typedef struct candidate_mv {
  int_mv this_mv;
  int_mv comp_mv;
} CANDIDATE_MV;

static INLINE int is_zero_mv(const MV *mv) {
  return *((const uint32_t *)mv) == 0;
}

static INLINE int is_equal_mv(const MV *a, const MV *b) {
  return *((const uint32_t *)a) == *((const uint32_t *)b);
}

static INLINE void clamp_mv(MV *mv, int min_col, int max_col, int min_row,
                            int max_row) {
  mv->col = clamp(mv->col, min_col, max_col);
  mv->row = clamp(mv->row, min_row, max_row);
}

static INLINE MvSubpelPrecision get_mv_component_precision(int comp) {
  if (comp & 1)
    return MV_SUBPEL_EIGHTH_PRECISION;
  else if (comp & 3)
    return MV_SUBPEL_QTR_PRECISION;
#if CONFIG_FLEX_MVRES
  else if (comp & 7)
    return MV_SUBPEL_HALF_PRECISION;
#endif  // CONFIG_FLEX_MVRES
  else
    return MV_SUBPEL_NONE;
}

#if CONFIG_COMPANDED_MV
static INLINE MvSubpelPrecision get_companded_mv_precision(int comp, int ref) {
  const int sign = comp < 0;
  const int comp1 = sign ? comp + 1 : comp - 1;
  const int mv_mag = abs((comp1 / 8) + (ref / 8));
#if CONFIG_FLEX_MVRES
  if (mv_mag > COMPANDED_INTMV_THRESH_HALF) return MV_SUBPEL_HALF_PRECISION;
#endif  // CONFIG_FLEX_MVRES
  if (mv_mag > COMPANDED_INTMV_THRESH_QTR) return MV_SUBPEL_QTR_PRECISION;
  return MV_SUBPEL_EIGHTH_PRECISION;
}
#endif  // CONFIG_COMPANDED_MV

static INLINE MvSubpelPrecision
get_mv_precision(const MV mv, MvSubpelPrecision max_precision) {
  (void)max_precision;
  MvSubpelPrecision precision = MV_SUBPEL_NONE;
  if ((mv.row & 1) || (mv.col & 1))
    precision = MV_SUBPEL_EIGHTH_PRECISION;
  else if ((mv.row & 3) || (mv.col & 3))
    precision = MV_SUBPEL_QTR_PRECISION;
  else if ((mv.row & 7) || (mv.col & 7))
    precision = MV_SUBPEL_HALF_PRECISION;
  else
    precision = MV_SUBPEL_NONE;
  assert(precision <= max_precision);
#if DISALLOW_ONE_DOWN_FLEX_MVRES == 2
  if ((max_precision - precision) & 1) precision += 1;
#elif DISALLOW_ONE_DOWN_FLEX_MVRES == 1
  if (max_precision - precision == 1) precision = max_precision;
#endif  // DISALLOW_ONE_DOWN_FLEX_MVRES
  return precision;
}

#if CONFIG_FLEX_MVRES
static INLINE MvSubpelPrecision
get_mv_precision2(const MV mv, const MV mv2, MvSubpelPrecision max_precision) {
  return (MvSubpelPrecision)AOMMAX(get_mv_precision(mv, max_precision),
                                   get_mv_precision(mv2, max_precision));
}
#endif  // CONFIG_FLEX_MVRES

#ifdef __cplusplus
}  // extern "C"
#endif

#endif  // AOM_AV1_COMMON_MV_H_
