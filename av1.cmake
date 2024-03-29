#
# Copyright (c) 2017, Alliance for Open Media. All rights reserved
#
# This source code is subject to the terms of the BSD 2 Clause License and the
# Alliance for Open Media Patent License 1.0. If the BSD 2 Clause License was
# not distributed with this source code in the LICENSE file, you can obtain it
# at www.aomedia.org/license/software. If the Alliance for Open Media Patent
# License 1.0 was not distributed with this source code in the PATENTS file, you
# can obtain it at www.aomedia.org/license/patent.
#
if(AOM_AV1_AV1_CMAKE_)
  return()
endif() # AOM_AV1_AV1_CMAKE_
set(AOM_AV1_AV1_CMAKE_ 1)

list(APPEND AOM_AV1_COMMON_SOURCES
            "${AOM_ROOT}/av1/av1_iface_common.h"
            "${AOM_ROOT}/av1/common/alloccommon.c"
            "${AOM_ROOT}/av1/common/alloccommon.h"
            "${AOM_ROOT}/av1/common/av1_inv_txfm1d.c"
            "${AOM_ROOT}/av1/common/av1_inv_txfm1d.h"
            "${AOM_ROOT}/av1/common/av1_inv_txfm1d_cfg.h"
            "${AOM_ROOT}/av1/common/av1_inv_txfm2d.c"
            "${AOM_ROOT}/av1/common/av1_loopfilter.c"
            "${AOM_ROOT}/av1/common/av1_loopfilter.h"
            "${AOM_ROOT}/av1/common/av1_txfm.c"
            "${AOM_ROOT}/av1/common/av1_txfm.h"
            "${AOM_ROOT}/av1/common/blockd.c"
            "${AOM_ROOT}/av1/common/blockd.h"
            "${AOM_ROOT}/av1/common/cdef.c"
            "${AOM_ROOT}/av1/common/cdef.h"
            "${AOM_ROOT}/av1/common/cdef_block.c"
            "${AOM_ROOT}/av1/common/cdef_block.h"
            "${AOM_ROOT}/av1/common/cfl.c"
            "${AOM_ROOT}/av1/common/cfl.h"
            "${AOM_ROOT}/av1/common/chroma.h"
            "${AOM_ROOT}/av1/common/cnn.c"
            "${AOM_ROOT}/av1/common/cnn.h"
            "${AOM_ROOT}/av1/common/common.h"
            "${AOM_ROOT}/av1/common/common_data.h"
            "${AOM_ROOT}/av1/common/convolve.c"
            "${AOM_ROOT}/av1/common/convolve.h"
            "${AOM_ROOT}/av1/common/debugmodes.c"
            "${AOM_ROOT}/av1/common/entropy.c"
            "${AOM_ROOT}/av1/common/entropy.h"
            "${AOM_ROOT}/av1/common/entropymode.c"
            "${AOM_ROOT}/av1/common/entropymode.h"
            "${AOM_ROOT}/av1/common/entropymv.c"
            "${AOM_ROOT}/av1/common/entropymv.h"
            "${AOM_ROOT}/av1/common/enums.h"
            "${AOM_ROOT}/av1/common/filter.h"
            "${AOM_ROOT}/av1/common/frame_buffers.c"
            "${AOM_ROOT}/av1/common/frame_buffers.h"
            "${AOM_ROOT}/av1/common/idct.c"
            "${AOM_ROOT}/av1/common/idct.h"
            "${AOM_ROOT}/av1/common/mv.h"
            "${AOM_ROOT}/av1/common/mvref_common.c"
            "${AOM_ROOT}/av1/common/mvref_common.h"
            "${AOM_ROOT}/av1/common/obu_util.c"
            "${AOM_ROOT}/av1/common/obu_util.h"
            "${AOM_ROOT}/av1/common/odintrin.c"
            "${AOM_ROOT}/av1/common/odintrin.h"
            "${AOM_ROOT}/av1/common/onyxc_int.h"
            "${AOM_ROOT}/av1/common/pred_common.c"
            "${AOM_ROOT}/av1/common/pred_common.h"
            "${AOM_ROOT}/av1/common/quant_common.c"
            "${AOM_ROOT}/av1/common/quant_common.h"
            "${AOM_ROOT}/av1/common/reconinter.c"
            "${AOM_ROOT}/av1/common/reconinter.h"
            "${AOM_ROOT}/av1/common/reconintra.c"
            "${AOM_ROOT}/av1/common/reconintra.h"
            "${AOM_ROOT}/av1/common/resize.c"
            "${AOM_ROOT}/av1/common/resize.h"
            "${AOM_ROOT}/av1/common/restoration.c"
            "${AOM_ROOT}/av1/common/restoration.h"
            "${AOM_ROOT}/av1/common/scale.c"
            "${AOM_ROOT}/av1/common/scale.h"
            "${AOM_ROOT}/av1/common/scan.c"
            "${AOM_ROOT}/av1/common/scan.h"
            "${AOM_ROOT}/av1/common/seg_common.c"
            "${AOM_ROOT}/av1/common/seg_common.h"
            "${AOM_ROOT}/av1/common/thread_common.c"
            "${AOM_ROOT}/av1/common/thread_common.h"
            "${AOM_ROOT}/av1/common/tile_common.c"
            "${AOM_ROOT}/av1/common/tile_common.h"
            "${AOM_ROOT}/av1/common/timing.c"
            "${AOM_ROOT}/av1/common/timing.h"
            "${AOM_ROOT}/av1/common/token_cdfs.h"
            "${AOM_ROOT}/av1/common/txb_common.c"
            "${AOM_ROOT}/av1/common/txb_common.h"
            "${AOM_ROOT}/av1/common/warped_motion.c"
            "${AOM_ROOT}/av1/common/warped_motion.h")

if(CONFIG_INTERINTRA_ML)
  list(APPEND AOM_AV1_COMMON_SOURCES "${AOM_ROOT}/av1/common/interintra_ml.h"
              "${AOM_ROOT}/av1/common/interintra_ml.cc"
              "${AOM_ROOT}/av1/common/interintra_ml_model.h"
              "${AOM_ROOT}/av1/common/interintra_ml_model.cc")
endif()

if(CONFIG_LPF_MASK)
  list(APPEND AOM_AV1_COMMON_SOURCES "${AOM_ROOT}/av1/common/loopfiltermask.c")
endif()

if(CONFIG_INTRA_ENTROPY)
  list(APPEND AOM_AV1_COMMON_SOURCES
              "${AOM_ROOT}/av1/common/intra_entropy_models.h"
              "${AOM_ROOT}/av1/common/nn_em.h" "${AOM_ROOT}/av1/common/nn_em.c")
endif()

if(CONFIG_MFQE_RESTORATION)
  list(APPEND AOM_AV1_COMMON_SOURCES "${AOM_ROOT}/av1/common/mfqe.c"
              "${AOM_ROOT}/av1/common/mfqe.h")
endif()

if(CONFIG_NN_RECON)
  list(APPEND AOM_AV1_COMMON_SOURCES "${AOM_ROOT}/av1/common/nn_recon.h")
endif()

list(APPEND AOM_AV1_DECODER_SOURCES
            "${AOM_ROOT}/av1/av1_dx_iface.c"
            "${AOM_ROOT}/av1/decoder/decodeframe.c"
            "${AOM_ROOT}/av1/decoder/decodeframe.h"
            "${AOM_ROOT}/av1/decoder/decodemv.c"
            "${AOM_ROOT}/av1/decoder/decodemv.h"
            "${AOM_ROOT}/av1/decoder/decoder.c"
            "${AOM_ROOT}/av1/decoder/decoder.h"
            "${AOM_ROOT}/av1/decoder/decodetxb.c"
            "${AOM_ROOT}/av1/decoder/decodetxb.h"
            "${AOM_ROOT}/av1/decoder/detokenize.c"
            "${AOM_ROOT}/av1/decoder/detokenize.h"
            "${AOM_ROOT}/av1/decoder/dthread.h"
            "${AOM_ROOT}/av1/decoder/obu.h"
            "${AOM_ROOT}/av1/decoder/obu.c")

list(APPEND AOM_AV1_ENCODER_SOURCES
            "${AOM_ROOT}/av1/av1_cx_iface.c"
            "${AOM_ROOT}/av1/encoder/aq_complexity.c"
            "${AOM_ROOT}/av1/encoder/aq_complexity.h"
            "${AOM_ROOT}/av1/encoder/aq_cyclicrefresh.c"
            "${AOM_ROOT}/av1/encoder/aq_cyclicrefresh.h"
            "${AOM_ROOT}/av1/encoder/aq_variance.c"
            "${AOM_ROOT}/av1/encoder/aq_variance.h"
            "${AOM_ROOT}/av1/encoder/enc_enums.h"
            "${AOM_ROOT}/av1/encoder/av1_fwd_txfm1d.c"
            "${AOM_ROOT}/av1/encoder/av1_fwd_txfm1d.h"
            "${AOM_ROOT}/av1/encoder/av1_fwd_txfm1d_cfg.h"
            "${AOM_ROOT}/av1/encoder/av1_fwd_txfm2d.c"
            "${AOM_ROOT}/av1/encoder/av1_multi_thread.c"
            "${AOM_ROOT}/av1/encoder/av1_multi_thread.h"
            "${AOM_ROOT}/av1/encoder/av1_quantize.c"
            "${AOM_ROOT}/av1/encoder/av1_quantize.h"
            "${AOM_ROOT}/av1/encoder/bitstream.c"
            "${AOM_ROOT}/av1/encoder/bitstream.h"
            "${AOM_ROOT}/av1/encoder/block.h"
            "${AOM_ROOT}/av1/encoder/context_tree.c"
            "${AOM_ROOT}/av1/encoder/context_tree.h"
            "${AOM_ROOT}/av1/encoder/corner_detect.c"
            "${AOM_ROOT}/av1/encoder/corner_detect.h"
            "${AOM_ROOT}/av1/encoder/corner_match.c"
            "${AOM_ROOT}/av1/encoder/corner_match.h"
            "${AOM_ROOT}/av1/encoder/cost.c"
            "${AOM_ROOT}/av1/encoder/cost.h"
            "${AOM_ROOT}/av1/encoder/encodeframe.c"
            "${AOM_ROOT}/av1/encoder/encodeframe.h"
            "${AOM_ROOT}/av1/encoder/encodeframe_utils.c"
            "${AOM_ROOT}/av1/encoder/encodeframe_utils.h"
            "${AOM_ROOT}/av1/encoder/encodemb.c"
            "${AOM_ROOT}/av1/encoder/encodemb.h"
            "${AOM_ROOT}/av1/encoder/encodemv.c"
            "${AOM_ROOT}/av1/encoder/encodemv.h"
            "${AOM_ROOT}/av1/encoder/encode_strategy.c"
            "${AOM_ROOT}/av1/encoder/encode_strategy.h"
            "${AOM_ROOT}/av1/encoder/encoder.c"
            "${AOM_ROOT}/av1/encoder/encoder.h"
            "${AOM_ROOT}/av1/encoder/encodetxb.c"
            "${AOM_ROOT}/av1/encoder/encodetxb.h"
            "${AOM_ROOT}/av1/encoder/ethread.c"
            "${AOM_ROOT}/av1/encoder/ethread.h"
            "${AOM_ROOT}/av1/encoder/extend.c"
            "${AOM_ROOT}/av1/encoder/extend.h"
            "${AOM_ROOT}/av1/encoder/firstpass.c"
            "${AOM_ROOT}/av1/encoder/firstpass.h"
            "${AOM_ROOT}/av1/encoder/global_motion.c"
            "${AOM_ROOT}/av1/encoder/global_motion.h"
            "${AOM_ROOT}/av1/encoder/gop_structure.c"
            "${AOM_ROOT}/av1/encoder/gop_structure.h"
            "${AOM_ROOT}/av1/encoder/grain_test_vectors.h"
            "${AOM_ROOT}/av1/encoder/hash.c"
            "${AOM_ROOT}/av1/encoder/hash.h"
            "${AOM_ROOT}/av1/encoder/hash_motion.c"
            "${AOM_ROOT}/av1/encoder/hash_motion.h"
            "${AOM_ROOT}/av1/encoder/hybrid_fwd_txfm.c"
            "${AOM_ROOT}/av1/encoder/hybrid_fwd_txfm.h"
            "${AOM_ROOT}/av1/encoder/level.c"
            "${AOM_ROOT}/av1/encoder/level.h"
            "${AOM_ROOT}/av1/encoder/lookahead.c"
            "${AOM_ROOT}/av1/encoder/lookahead.h"
            "${AOM_ROOT}/av1/encoder/mbgraph.c"
            "${AOM_ROOT}/av1/encoder/mbgraph.h"
            "${AOM_ROOT}/av1/encoder/mcomp.c"
            "${AOM_ROOT}/av1/encoder/mcomp.h"
            "${AOM_ROOT}/av1/encoder/ml.c"
            "${AOM_ROOT}/av1/encoder/ml.h"
            "${AOM_ROOT}/av1/encoder/mv_prec.c"
            "${AOM_ROOT}/av1/encoder/mv_prec.h"
            "${AOM_ROOT}/av1/encoder/palette.c"
            "${AOM_ROOT}/av1/encoder/palette.h"
            "${AOM_ROOT}/av1/encoder/partition_search.h"
            "${AOM_ROOT}/av1/encoder/partition_search.c"
            "${AOM_ROOT}/av1/encoder/partition_search_utils.h"
            "${AOM_ROOT}/av1/encoder/partition_search_utils.c"
            "${AOM_ROOT}/av1/encoder/partition_strategy.h"
            "${AOM_ROOT}/av1/encoder/partition_strategy.c"
            "${AOM_ROOT}/av1/encoder/pass2_strategy.h"
            "${AOM_ROOT}/av1/encoder/pass2_strategy.c"
            "${AOM_ROOT}/av1/encoder/pickcdef.c"
            "${AOM_ROOT}/av1/encoder/picklpf.c"
            "${AOM_ROOT}/av1/encoder/picklpf.h"
            "${AOM_ROOT}/av1/encoder/pickrst.c"
            "${AOM_ROOT}/av1/encoder/pickrst.h"
            "${AOM_ROOT}/av1/encoder/ransac.c"
            "${AOM_ROOT}/av1/encoder/ransac.h"
            "${AOM_ROOT}/av1/encoder/ratectrl.c"
            "${AOM_ROOT}/av1/encoder/ratectrl.h"
            "${AOM_ROOT}/av1/encoder/rd.c"
            "${AOM_ROOT}/av1/encoder/rd.h"
            "${AOM_ROOT}/av1/encoder/rdopt.c"
            "${AOM_ROOT}/av1/encoder/nonrd_pickmode.c"
            "${AOM_ROOT}/av1/encoder/rdopt.h"
            "${AOM_ROOT}/av1/encoder/reconinter_enc.c"
            "${AOM_ROOT}/av1/encoder/reconinter_enc.h"
            "${AOM_ROOT}/av1/encoder/segmentation.c"
            "${AOM_ROOT}/av1/encoder/segmentation.h"
            "${AOM_ROOT}/av1/encoder/speed_features.c"
            "${AOM_ROOT}/av1/encoder/speed_features.h"
            "${AOM_ROOT}/av1/encoder/temporal_filter.c"
            "${AOM_ROOT}/av1/encoder/temporal_filter.h"
            "${AOM_ROOT}/av1/encoder/tokenize.c"
            "${AOM_ROOT}/av1/encoder/tokenize.h"
            "${AOM_ROOT}/av1/encoder/tpl_model.c"
            "${AOM_ROOT}/av1/encoder/tpl_model.h"
            "${AOM_ROOT}/av1/encoder/wedge_utils.c"
            "${AOM_ROOT}/av1/encoder/var_based_part.c"
            "${AOM_ROOT}/av1/encoder/var_based_part.h"
            "${AOM_ROOT}/third_party/fastfeat/fast.c"
            "${AOM_ROOT}/third_party/fastfeat/fast.h"
            "${AOM_ROOT}/third_party/fastfeat/fast_9.c"
            "${AOM_ROOT}/third_party/fastfeat/nonmax.c"
            "${AOM_ROOT}/third_party/vector/vector.c"
            "${AOM_ROOT}/third_party/vector/vector.h"
            "${AOM_ROOT}/av1/encoder/dwt.c"
            "${AOM_ROOT}/av1/encoder/dwt.h")

if(CONFIG_INTERINTRA_ML_DATA_COLLECT)
  list(APPEND AOM_AV1_ENCODER_SOURCES
              "${AOM_ROOT}/av1/encoder/interintra_ml_data_collect.h"
              "${AOM_ROOT}/av1/encoder/interintra_ml_data_collect.c")

endif()

if(CONFIG_SEGMENT_BASED_PARTITIONING)
  list(APPEND AOM_AV1_ENCODER_SOURCES "${AOM_ROOT}/av1/encoder/segment_patch.cc"
              "${AOM_ROOT}/av1/encoder/segment_patch.h")
endif()

list(APPEND AOM_AV1_COMMON_INTRIN_SSE2
            "${AOM_ROOT}/av1/common/cdef_block_sse2.c"
            "${AOM_ROOT}/av1/common/x86/cfl_sse2.c"
            "${AOM_ROOT}/av1/common/x86/convolve_2d_sse2.c"
            "${AOM_ROOT}/av1/common/x86/convolve_sse2.c"
            "${AOM_ROOT}/av1/common/x86/highbd_convolve_2d_sse2.c"
            "${AOM_ROOT}/av1/common/x86/jnt_convolve_sse2.c"
            "${AOM_ROOT}/av1/common/x86/wiener_convolve_sse2.c"
            "${AOM_ROOT}/av1/common/x86/av1_txfm_sse2.h"
            "${AOM_ROOT}/av1/common/x86/warp_plane_sse2.c")

list(APPEND AOM_AV1_COMMON_INTRIN_SSSE3
            "${AOM_ROOT}/av1/common/cdef_block_ssse3.c"
            "${AOM_ROOT}/av1/common/x86/av1_inv_txfm_ssse3.c"
            "${AOM_ROOT}/av1/common/x86/av1_inv_txfm_ssse3.h"
            "${AOM_ROOT}/av1/common/x86/cfl_ssse3.c"
            "${AOM_ROOT}/av1/common/x86/highbd_convolve_2d_ssse3.c"
            "${AOM_ROOT}/av1/common/x86/highbd_wiener_convolve_ssse3.c"
            "${AOM_ROOT}/av1/common/x86/jnt_convolve_ssse3.c"
            "${AOM_ROOT}/av1/common/x86/reconinter_ssse3.c")

list(APPEND AOM_AV1_COMMON_INTRIN_SSE4_1
            "${AOM_ROOT}/av1/common/cdef_block_sse4.c"
            "${AOM_ROOT}/av1/common/x86/av1_convolve_horiz_rs_sse4.c"
            "${AOM_ROOT}/av1/common/x86/av1_convolve_scale_sse4.c"
            "${AOM_ROOT}/av1/common/x86/av1_txfm_sse4.c"
            "${AOM_ROOT}/av1/common/x86/av1_txfm_sse4.h"
            "${AOM_ROOT}/av1/common/x86/nn_em_sse4.c"
            "${AOM_ROOT}/av1/common/x86/filterintra_sse4.c"
            "${AOM_ROOT}/av1/common/x86/grad_hist_sse4.c"
            "${AOM_ROOT}/av1/common/x86/highbd_convolve_2d_sse4.c"
            "${AOM_ROOT}/av1/common/x86/highbd_inv_txfm_sse4.c"
            "${AOM_ROOT}/av1/common/x86/highbd_jnt_convolve_sse4.c"
            "${AOM_ROOT}/av1/common/x86/highbd_warp_plane_sse4.c"
            "${AOM_ROOT}/av1/common/x86/intra_edge_sse4.c"
            "${AOM_ROOT}/av1/common/x86/reconinter_sse4.c"
            "${AOM_ROOT}/av1/common/x86/selfguided_sse4.c"
            "${AOM_ROOT}/av1/common/x86/warp_plane_sse4.c")

list(APPEND AOM_AV1_COMMON_INTRIN_AVX2
            "${AOM_ROOT}/av1/common/cdef_block_avx2.c"
            "${AOM_ROOT}/av1/common/x86/av1_inv_txfm_avx2.c"
            "${AOM_ROOT}/av1/common/x86/av1_inv_txfm_avx2.h"
            "${AOM_ROOT}/av1/common/x86/cfl_avx2.c"
            "${AOM_ROOT}/av1/common/x86/convolve_2d_avx2.c"
            "${AOM_ROOT}/av1/common/x86/convolve_avx2.c"
            "${AOM_ROOT}/av1/common/x86/highbd_convolve_2d_avx2.c"
            "${AOM_ROOT}/av1/common/x86/highbd_inv_txfm_avx2.c"
            "${AOM_ROOT}/av1/common/x86/highbd_jnt_convolve_avx2.c"
            "${AOM_ROOT}/av1/common/x86/highbd_wiener_convolve_avx2.c"
            "${AOM_ROOT}/av1/common/x86/jnt_convolve_avx2.c"
            "${AOM_ROOT}/av1/common/x86/reconinter_avx2.c"
            "${AOM_ROOT}/av1/common/x86/selfguided_avx2.c"
            "${AOM_ROOT}/av1/common/x86/warp_plane_avx2.c"
            "${AOM_ROOT}/av1/common/x86/wiener_convolve_avx2.c")

list(APPEND AOM_AV1_ENCODER_ASM_SSE2 "${AOM_ROOT}/av1/encoder/x86/dct_sse2.asm"
            "${AOM_ROOT}/av1/encoder/x86/error_sse2.asm")

list(APPEND AOM_AV1_ENCODER_INTRIN_SSE2
            "${AOM_ROOT}/av1/encoder/x86/av1_fwd_txfm_sse2.c"
            "${AOM_ROOT}/av1/encoder/x86/av1_fwd_txfm_sse2.h"
            "${AOM_ROOT}/av1/encoder/x86/av1_quantize_sse2.c"
            "${AOM_ROOT}/av1/encoder/x86/encodetxb_sse2.c"
            "${AOM_ROOT}/av1/encoder/x86/highbd_block_error_intrin_sse2.c"
            "${AOM_ROOT}/av1/encoder/x86/wedge_utils_sse2.c")

list(APPEND AOM_AV1_ENCODER_INTRIN_SSE3 "${AOM_ROOT}/av1/encoder/x86/ml_sse3.c")

list(APPEND AOM_AV1_ENCODER_ASM_SSSE3_X86_64
            "${AOM_ROOT}/av1/encoder/x86/av1_quantize_ssse3_x86_64.asm")

list(APPEND AOM_AV1_ENCODER_INTRIN_SSE4_1
            "${AOM_ROOT}/av1/encoder/x86/av1_fwd_txfm1d_sse4.c"
            "${AOM_ROOT}/av1/encoder/x86/av1_fwd_txfm2d_sse4.c"
            "${AOM_ROOT}/av1/encoder/x86/av1_highbd_quantize_sse4.c"
            "${AOM_ROOT}/av1/encoder/x86/corner_match_sse4.c"
            "${AOM_ROOT}/av1/encoder/x86/encodetxb_sse4.c"
            "${AOM_ROOT}/av1/encoder/x86/highbd_fwd_txfm_sse4.c"
            "${AOM_ROOT}/av1/encoder/x86/rdopt_sse4.c"
            "${AOM_ROOT}/av1/encoder/x86/temporal_filter_constants.h"
            "${AOM_ROOT}/av1/encoder/x86/temporal_filter_sse4.c"
            "${AOM_ROOT}/av1/encoder/x86/highbd_temporal_filter_sse4.c"
            "${AOM_ROOT}/av1/encoder/x86/pickrst_sse4.c")

list(APPEND AOM_AV1_ENCODER_INTRIN_AVX2
            "${AOM_ROOT}/av1/encoder/x86/av1_quantize_avx2.c"
            "${AOM_ROOT}/av1/encoder/x86/av1_highbd_quantize_avx2.c"
            "${AOM_ROOT}/av1/encoder/x86/corner_match_avx2.c"
            "${AOM_ROOT}/av1/encoder/x86/error_intrin_avx2.c"
            "${AOM_ROOT}/av1/encoder/x86/highbd_block_error_intrin_avx2.c"
            "${AOM_ROOT}/av1/encoder/x86/av1_fwd_txfm_avx2.h"
            "${AOM_ROOT}/av1/encoder/x86/av1_fwd_txfm2d_avx2.c"
            "${AOM_ROOT}/av1/encoder/x86/highbd_fwd_txfm_avx2.c"
            "${AOM_ROOT}/av1/encoder/x86/wedge_utils_avx2.c"
            "${AOM_ROOT}/av1/encoder/x86/encodetxb_avx2.c"
            "${AOM_ROOT}/av1/encoder/x86/rdopt_avx2.c"
            "${AOM_ROOT}/av1/encoder/x86/pickrst_avx2.c")

list(APPEND AOM_AV1_ENCODER_INTRIN_NEON
            "${AOM_ROOT}/av1/encoder/arm/neon/quantize_neon.c"
            "${AOM_ROOT}/av1/encoder/arm/neon/av1_error_neon.c")

list(APPEND AOM_AV1_ENCODER_INTRIN_MSA
            "${AOM_ROOT}/av1/encoder/mips/msa/error_msa.c"
            "${AOM_ROOT}/av1/encoder/mips/msa/fdct4x4_msa.c"
            "${AOM_ROOT}/av1/encoder/mips/msa/temporal_filter_msa.c")

list(APPEND AOM_AV1_COMMON_INTRIN_NEON
            "${AOM_ROOT}/av1/common/arm/av1_txfm_neon.c"
            "${AOM_ROOT}/av1/common/arm/cfl_neon.c"
            "${AOM_ROOT}/av1/common/arm/convolve_neon.c"
            "${AOM_ROOT}/av1/common/arm/convolve_neon.h"
            "${AOM_ROOT}/av1/common/arm/jnt_convolve_neon.c"
            "${AOM_ROOT}/av1/common/arm/mem_neon.h"
            "${AOM_ROOT}/av1/common/arm/transpose_neon.h"
            "${AOM_ROOT}/av1/common/arm/blend_a64_hmask_neon.c"
            "${AOM_ROOT}/av1/common/arm/blend_a64_vmask_neon.c"
            "${AOM_ROOT}/av1/common/arm/reconinter_neon.c"
            "${AOM_ROOT}/av1/common/arm/wiener_convolve_neon.c"
            "${AOM_ROOT}/av1/common/arm/selfguided_neon.c"
            "${AOM_ROOT}/av1/common/arm/av1_inv_txfm_neon.c"
            "${AOM_ROOT}/av1/common/arm/av1_inv_txfm_neon.h"
            "${AOM_ROOT}/av1/common/arm/warp_plane_neon.c"
            "${AOM_ROOT}/av1/common/cdef_block_neon.c")

list(APPEND AOM_AV1_ENCODER_INTRIN_SSE4_2
            "${AOM_ROOT}/av1/encoder/x86/hash_sse42.c")

list(APPEND AOM_AV1_COMMON_INTRIN_VSX "${AOM_ROOT}/av1/common/ppc/cfl_ppc.c")

if(CONFIG_ACCOUNTING)
  list(APPEND AOM_AV1_DECODER_SOURCES "${AOM_ROOT}/av1/decoder/accounting.c"
              "${AOM_ROOT}/av1/decoder/accounting.h")
endif()

if(CONFIG_INSPECTION)
  list(APPEND AOM_AV1_DECODER_SOURCES "${AOM_ROOT}/av1/decoder/inspection.c"
              "${AOM_ROOT}/av1/decoder/inspection.h")
endif()

if(CONFIG_INTERNAL_STATS)
  list(APPEND AOM_AV1_ENCODER_SOURCES "${AOM_ROOT}/av1/encoder/blockiness.c")
endif()

if(CONFIG_CNN_RESTORATION OR CONFIG_LOOP_RESTORE_CNN)
  list(APPEND AOM_AV1_COMMON_SOURCES
              "${AOM_ROOT}/av1/common/cnn_tflite.cc"
              "${AOM_ROOT}/av1/common/cnn_tflite.h"
              "${AOM_ROOT}/av1/tflite_models/inter_frame_model/uv_qp68_107.cc"
              "${AOM_ROOT}/av1/tflite_models/inter_frame_model/uv_qp68_107.h"
              "${AOM_ROOT}/av1/tflite_models/inter_frame_model/uv_qp108_147.cc"
              "${AOM_ROOT}/av1/tflite_models/inter_frame_model/uv_qp108_147.h"
              "${AOM_ROOT}/av1/tflite_models/inter_frame_model/uv_qp148_191.cc"
              "${AOM_ROOT}/av1/tflite_models/inter_frame_model/uv_qp148_191.h"
              "${AOM_ROOT}/av1/tflite_models/inter_frame_model/uv_qp192_231.cc"
              "${AOM_ROOT}/av1/tflite_models/inter_frame_model/uv_qp192_231.h"
              "${AOM_ROOT}/av1/tflite_models/inter_frame_model/uv_qp232_255.cc"
              "${AOM_ROOT}/av1/tflite_models/inter_frame_model/uv_qp232_255.h"
              "${AOM_ROOT}/av1/tflite_models/inter_frame_model/qp68_107.cc"
              "${AOM_ROOT}/av1/tflite_models/inter_frame_model/qp68_107.h"
              "${AOM_ROOT}/av1/tflite_models/inter_frame_model/qp108_147.cc"
              "${AOM_ROOT}/av1/tflite_models/inter_frame_model/qp108_147.h"
              "${AOM_ROOT}/av1/tflite_models/inter_frame_model/qp148_191.cc"
              "${AOM_ROOT}/av1/tflite_models/inter_frame_model/qp148_191.h"
              "${AOM_ROOT}/av1/tflite_models/inter_frame_model/qp192_231.cc"
              "${AOM_ROOT}/av1/tflite_models/inter_frame_model/qp192_231.h"
              "${AOM_ROOT}/av1/tflite_models/inter_frame_model/qp232_255.cc"
              "${AOM_ROOT}/av1/tflite_models/inter_frame_model/qp232_255.h"
              "${AOM_ROOT}/av1/tflite_models/intra_frame_model/uv_qp22.cc"
              "${AOM_ROOT}/av1/tflite_models/intra_frame_model/uv_qp22.h"
              "${AOM_ROOT}/av1/tflite_models/intra_frame_model/uv_qp32.cc"
              "${AOM_ROOT}/av1/tflite_models/intra_frame_model/uv_qp32.h"
              "${AOM_ROOT}/av1/tflite_models/intra_frame_model/uv_qp43.cc"
              "${AOM_ROOT}/av1/tflite_models/intra_frame_model/uv_qp43.h"
              "${AOM_ROOT}/av1/tflite_models/intra_frame_model/uv_qp53.cc"
              "${AOM_ROOT}/av1/tflite_models/intra_frame_model/uv_qp53.h"
              "${AOM_ROOT}/av1/tflite_models/intra_frame_model/uv_qp63.cc"
              "${AOM_ROOT}/av1/tflite_models/intra_frame_model/uv_qp63.h"
              "${AOM_ROOT}/av1/tflite_models/intra_frame_model/qp22.cc"
              "${AOM_ROOT}/av1/tflite_models/intra_frame_model/qp22.h"
              "${AOM_ROOT}/av1/tflite_models/intra_frame_model/qp32.cc"
              "${AOM_ROOT}/av1/tflite_models/intra_frame_model/qp32.h"
              "${AOM_ROOT}/av1/tflite_models/intra_frame_model/qp43.cc"
              "${AOM_ROOT}/av1/tflite_models/intra_frame_model/qp43.h"
              "${AOM_ROOT}/av1/tflite_models/intra_frame_model/qp53.cc"
              "${AOM_ROOT}/av1/tflite_models/intra_frame_model/qp53.h"
              "${AOM_ROOT}/av1/tflite_models/intra_frame_model/qp63.cc"
              "${AOM_ROOT}/av1/tflite_models/intra_frame_model/qp63.h"
              "${AOM_ROOT}/av1/tflite_models/op_registrations.cc"
              "${AOM_ROOT}/av1/tflite_models/op_registrations.h")
endif()

if(CONFIG_CNN_CRLC_GUIDED)
  list(APPEND AOM_AV1_COMMON_SOURCES
              "${AOM_ROOT}/av1/tflite_models/crlc_model/qp12_crlc.cc"
              "${AOM_ROOT}/av1/tflite_models/crlc_model/qp12_crlc.h"
              "${AOM_ROOT}/av1/tflite_models/crlc_model/qp22_crlc.cc"
              "${AOM_ROOT}/av1/tflite_models/crlc_model/qp22_crlc.h"
              "${AOM_ROOT}/av1/tflite_models/crlc_model/qp28_crlc.cc"
              "${AOM_ROOT}/av1/tflite_models/crlc_model/qp28_crlc.h"
              "${AOM_ROOT}/av1/tflite_models/crlc_model/qp33_crlc.cc"
              "${AOM_ROOT}/av1/tflite_models/crlc_model/qp33_crlc.h"
              "${AOM_ROOT}/av1/tflite_models/crlc_model/qp43_crlc.cc"
              "${AOM_ROOT}/av1/tflite_models/crlc_model/qp43_crlc.h"
              "${AOM_ROOT}/av1/tflite_models/crlc_model/qp53_crlc.cc"
              "${AOM_ROOT}/av1/tflite_models/crlc_model/qp53_crlc.h"
              "${AOM_ROOT}/av1/tflite_models/crlc_model/qp63_crlc.cc"
              "${AOM_ROOT}/av1/tflite_models/crlc_model/qp63_crlc.h")
endif()

if(CONFIG_NN_RECON)
  list(APPEND AOM_AV1_COMMON_SOURCES "${AOM_ROOT}/av1/common/cnn_tflite.cc"
              "${AOM_ROOT}/av1/common/cnn_tflite.h"
              "${AOM_ROOT}/av1/tflite_models/intra_txfm_recon_model/tx16x16.cc"
              "${AOM_ROOT}/av1/tflite_models/intra_txfm_recon_model/tx16x16.h"
              "${AOM_ROOT}/av1/tflite_models/op_registrations.cc"
              "${AOM_ROOT}/av1/tflite_models/op_registrations.h")
endif()

if(CONFIG_REALTIME_ONLY)
  list(REMOVE_ITEM AOM_AV1_ENCODER_SOURCES
                   "${AOM_ROOT}/av1/encoder/firstpass.c"
                   "${AOM_ROOT}/av1/encoder/firstpass.h"
                   "${AOM_ROOT}/av1/encoder/misc_model_weights.h"
                   "${AOM_ROOT}/av1/encoder/pass2_strategy.c"
                   "${AOM_ROOT}/av1/encoder/mbgraph.c"
                   "${AOM_ROOT}/av1/encoder/mbgraph.h"
                   "${AOM_ROOT}/av1/encoder/partition_model_weights.h"
                   "${AOM_ROOT}/av1/encoder/temporal_filter.c"
                   "${AOM_ROOT}/av1/encoder/temporal_filter.h"
                   "${AOM_ROOT}/av1/encoder/temporal_filter_constants.h"
                   "${AOM_ROOT}/av1/encoder/x86/temporal_filter_sse4.c"
                   "${AOM_ROOT}/av1/encoder/x86/highbd_temporal_filter_sse4.c")
endif()

# Setup AV1 common/decoder/encoder targets. The libaom target must exist before
# this function is called.
function(setup_av1_targets)
  add_library(aom_av1_common OBJECT ${AOM_AV1_COMMON_SOURCES})
  list(APPEND AOM_LIB_TARGETS aom_av1_common)
  target_sources(aom PRIVATE $<TARGET_OBJECTS:aom_av1_common>)

  if(CONFIG_AV1_DECODER)
    add_library(aom_av1_decoder OBJECT ${AOM_AV1_DECODER_SOURCES})
    set(AOM_LIB_TARGETS ${AOM_LIB_TARGETS} aom_av1_decoder)
    target_sources(aom PRIVATE $<TARGET_OBJECTS:aom_av1_decoder>)
  endif()

  if(CONFIG_AV1_ENCODER)
    add_library(aom_av1_encoder OBJECT ${AOM_AV1_ENCODER_SOURCES})
    set(AOM_LIB_TARGETS ${AOM_LIB_TARGETS} aom_av1_encoder)
    target_sources(aom PRIVATE $<TARGET_OBJECTS:aom_av1_encoder>)
  endif()

  if(HAVE_SSE2)
    require_compiler_flag_nomsvc("-msse2" NO)
    add_intrinsics_object_library("-msse2" "sse2" "aom_av1_common"
                                  "AOM_AV1_COMMON_INTRIN_SSE2" "aom")
    if(CONFIG_AV1_DECODER)
      if(AOM_AV1_DECODER_ASM_SSE2)
        add_asm_library("aom_av1_decoder_sse2" "AOM_AV1_DECODER_ASM_SSE2" "aom")
      endif()

      if(AOM_AV1_DECODER_INTRIN_SSE2)
        add_intrinsics_object_library("-msse2" "sse2" "aom_av1_decoder"
                                      "AOM_AV1_DECODER_INTRIN_SSE2" "aom")
      endif()
    endif()

    if(CONFIG_AV1_ENCODER)
      add_asm_library("aom_av1_encoder_sse2" "AOM_AV1_ENCODER_ASM_SSE2" "aom")
      add_intrinsics_object_library("-msse2" "sse2" "aom_av1_encoder"
                                    "AOM_AV1_ENCODER_INTRIN_SSE2" "aom")
    endif()
  endif()

  if(HAVE_SSE3)
    require_compiler_flag_nomsvc("-msse3" NO)
    if(CONFIG_AV1_ENCODER)
      add_intrinsics_object_library("-msse3" "sse3" "aom_av1_encoder"
                                    "AOM_AV1_ENCODER_INTRIN_SSE3" "aom")
    endif()
  endif()

  if(HAVE_SSSE3)
    require_compiler_flag_nomsvc("-mssse3" NO)
    add_intrinsics_object_library("-mssse3" "ssse3" "aom_av1_common"
                                  "AOM_AV1_COMMON_INTRIN_SSSE3" "aom")

    if(CONFIG_AV1_DECODER)
      if(AOM_AV1_DECODER_INTRIN_SSSE3)
        add_intrinsics_object_library("-mssse3" "ssse3" "aom_av1_decoder"
                                      "AOM_AV1_DECODER_INTRIN_SSSE3" "aom")
      endif()
    endif()
  endif()

  if(HAVE_SSE4_1)
    require_compiler_flag_nomsvc("-msse4.1" NO)
    add_intrinsics_object_library("-msse4.1" "sse4" "aom_av1_common"
                                  "AOM_AV1_COMMON_INTRIN_SSE4_1" "aom")

    if(CONFIG_AV1_ENCODER)
      if("${AOM_TARGET_CPU}" STREQUAL "x86_64")
        add_asm_library("aom_av1_encoder_ssse3"
                        "AOM_AV1_ENCODER_ASM_SSSE3_X86_64" "aom")
      endif()

      if(AOM_AV1_ENCODER_INTRIN_SSE4_1)
        add_intrinsics_object_library("-msse4.1" "sse4" "aom_av1_encoder"
                                      "AOM_AV1_ENCODER_INTRIN_SSE4_1" "aom")
      endif()
    endif()
  endif()

  if(HAVE_SSE4_2)
    require_compiler_flag_nomsvc("-msse4.2" NO)
    if(CONFIG_AV1_ENCODER)
      if(AOM_AV1_ENCODER_INTRIN_SSE4_2)
        add_intrinsics_object_library("-msse4.2" "sse42" "aom_av1_encoder"
                                      "AOM_AV1_ENCODER_INTRIN_SSE4_2" "aom")
      endif()
    endif()
  endif()

  if(HAVE_AVX2)
    require_compiler_flag_nomsvc("-mavx2" NO)
    add_intrinsics_object_library("-mavx2" "avx2" "aom_av1_common"
                                  "AOM_AV1_COMMON_INTRIN_AVX2" "aom")

    if(CONFIG_AV1_ENCODER)
      add_intrinsics_object_library("-mavx2" "avx2" "aom_av1_encoder"
                                    "AOM_AV1_ENCODER_INTRIN_AVX2" "aom")
    endif()
  endif()

  if(HAVE_NEON)
    if(AOM_AV1_COMMON_INTRIN_NEON)
      add_intrinsics_object_library("${AOM_NEON_INTRIN_FLAG}" "neon"
                                    "aom_av1_common"
                                    "AOM_AV1_COMMON_INTRIN_NEON" "aom")
    endif()

    if(AOM_AV1_ENCODER_INTRIN_NEON)
      add_intrinsics_object_library("${AOM_NEON_INTRIN_FLAG}" "neon"
                                    "aom_av1_encoder"
                                    "AOM_AV1_ENCODER_INTRIN_NEON" "aom")
    endif()
  endif()

  if(HAVE_VSX)
    if(AOM_AV1_COMMON_INTRIN_VSX)
      add_intrinsics_object_library("-mvsx -maltivec" "vsx" "aom_av1_common"
                                    "AOM_AV1_COMMON_INTRIN_VSX" "aom")
    endif()
  endif()

  if(HAVE_MSA)
    add_intrinsics_object_library("" "msa" "aom_av1_encoder"
                                  "AOM_AV1_ENCODER_INTRIN_MSA" "aom")
  endif()

  # Pass the new lib targets up to the parent scope instance of
  # $AOM_LIB_TARGETS.
  set(AOM_LIB_TARGETS ${AOM_LIB_TARGETS} PARENT_SCOPE)
endfunction()
