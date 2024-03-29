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

#ifndef AOM_AV1_ENCODER_AV1_FWD_TXFM1D_H_
#define AOM_AV1_ENCODER_AV1_FWD_TXFM1D_H_

#include "av1/common/av1_txfm.h"

#if CONFIG_MODE_DEP_INTRA_TX || CONFIG_MODE_DEP_INTER_TX
#include "av1/common/mdtx_bases.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if CONFIG_MODE_DEP_INTRA_TX || CONFIG_MODE_DEP_INTER_TX
void av1_fmdt4(const int32_t *input, int32_t *output, int8_t cos_bit,
               const int8_t *side_info);
void av1_fmdt8(const int32_t *input, int32_t *output, int8_t cos_bit,
               const int8_t *side_info);
void av1_fmdt16(const int32_t *input, int32_t *output, int8_t cos_bit,
                const int8_t *side_info);
#endif
void av1_fdct4_new(const int32_t *input, int32_t *output, int8_t cos_bit,
                   const int8_t *stage_range);
void av1_fdct8_new(const int32_t *input, int32_t *output, int8_t cos_bit,
                   const int8_t *stage_range);
void av1_fdct16_new(const int32_t *input, int32_t *output, int8_t cos_bit,
                    const int8_t *stage_range);
void av1_fdct32_new(const int32_t *input, int32_t *output, int8_t cos_bit,
                    const int8_t *stage_range);
void av1_fdct64_new(const int32_t *input, int32_t *output, int8_t cos_bit,
                    const int8_t *stage_range);
void av1_fadst4_new(const int32_t *input, int32_t *output, int8_t cos_bit,
                    const int8_t *stage_range);
void av1_fadst8_new(const int32_t *input, int32_t *output, int8_t cos_bit,
                    const int8_t *stage_range);
void av1_fadst16_new(const int32_t *input, int32_t *output, int8_t cos_bit,
                     const int8_t *stage_range);
#if CONFIG_DST_32X32
void av1_fadst32_new(const int32_t *input, int32_t *output, int8_t cos_bit,
                     const int8_t *stage_range);
#endif
void av1_fidentity4_c(const int32_t *input, int32_t *output, int8_t cos_bit,
                      const int8_t *stage_range);
void av1_fidentity8_c(const int32_t *input, int32_t *output, int8_t cos_bit,
                      const int8_t *stage_range);
void av1_fidentity16_c(const int32_t *input, int32_t *output, int8_t cos_bit,
                       const int8_t *stage_range);
void av1_fidentity32_c(const int32_t *input, int32_t *output, int8_t cos_bit,
                       const int8_t *stage_range);
#if CONFIG_LGT
void av1_fadst4_lgt_intra(const int32_t *input, int32_t *output, int8_t cos_bit,
                          const int8_t *stage_range);
void av1_fadst4_lgt_inter(const int32_t *input, int32_t *output, int8_t cos_bit,
                          const int8_t *stage_range);
void av1_fadst8_lgt_intra(const int32_t *input, int32_t *output, int8_t cos_bit,
                          const int8_t *stage_range);
void av1_fadst8_lgt_inter(const int32_t *input, int32_t *output, int8_t cos_bit,
                          const int8_t *stage_range);
void av1_fadst16_lgt_intra(const int32_t *input, int32_t *output,
                           int8_t cos_bit, const int8_t *stage_range);
void av1_fadst16_lgt_inter(const int32_t *input, int32_t *output,
                           int8_t cos_bit, const int8_t *stage_range);
#endif  // CONFIG_LGT
#ifdef __cplusplus
}
#endif

#endif  // AOM_AV1_ENCODER_AV1_FWD_TXFM1D_H_
