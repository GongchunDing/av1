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

#ifndef AOM_AV1_ENCODER_ENC_ENUMS_H_
#define AOM_AV1_ENCODER_ENC_ENUMS_H_

#ifdef __cplusplus
extern "C" {
#endif

// This enumerator type needs to be kept aligned with the mode order in
// const MODE_DEFINITION av1_mode_order[MAX_MODES] used in the rd code.

#if CONFIG_NEW_INTER_MODES
enum {
  THR_NEARMV,
  THR_NEARL2,
  THR_NEARL3,
  THR_NEARB,
  THR_NEARA2,
  THR_NEARA,
  THR_NEARG,

  THR_NEWMV,
  THR_NEWL2,
  THR_NEWL3,
  THR_NEWB,
  THR_NEWA2,
  THR_NEWA,
  THR_NEWG,

  THR_GLOBALMV,
  THR_GLOBALL2,
  THR_GLOBALL3,
  THR_GLOBALB,
  THR_GLOBALA2,
  THR_GLOBALG,
  THR_GLOBALA,

  THR_COMP_NEAR_NEARLA,
  THR_COMP_NEAR_NEARL2A,
  THR_COMP_NEAR_NEARL3A,
  THR_COMP_NEAR_NEARGA,
  THR_COMP_NEAR_NEARLB,
  THR_COMP_NEAR_NEARL2B,
  THR_COMP_NEAR_NEARL3B,
  THR_COMP_NEAR_NEARGB,
  THR_COMP_NEAR_NEARLA2,
  THR_COMP_NEAR_NEARL2A2,
  THR_COMP_NEAR_NEARL3A2,
  THR_COMP_NEAR_NEARGA2,
  THR_COMP_NEAR_NEARLL2,
  THR_COMP_NEAR_NEARLL3,
  THR_COMP_NEAR_NEARLG,
  THR_COMP_NEAR_NEARBA,

  THR_COMP_NEW_NEARLA,
  THR_COMP_NEAR_NEWLA,
  THR_COMP_NEW_NEWLA,
  THR_COMP_GLOBAL_GLOBALLA,
#if CONFIG_OPTFLOW_REFINEMENT
  THR_COMP_NEAR_NEAR_OPTFLOWLA,
  THR_COMP_NEAR_NEW_OPTFLOWLA,
  THR_COMP_NEW_NEAR_OPTFLOWLA,
  THR_COMP_GLOBAL_GLOBAL_OPTFLOWLA,
  THR_COMP_NEW_NEW_OPTFLOWLA,
#endif  // CONFIG_OPTFLOW_REFINEMENT

  THR_COMP_NEW_NEARL2A,
  THR_COMP_NEAR_NEWL2A,
  THR_COMP_NEW_NEWL2A,
  THR_COMP_GLOBAL_GLOBALL2A,
#if CONFIG_OPTFLOW_REFINEMENT
  THR_COMP_NEAR_NEAR_OPTFLOWL2A,
  THR_COMP_NEAR_NEW_OPTFLOWL2A,
  THR_COMP_NEW_NEAR_OPTFLOWL2A,
  THR_COMP_GLOBAL_GLOBAL_OPTFLOWL2A,
  THR_COMP_NEW_NEW_OPTFLOWL2A,
#endif  // CONFIG_OPTFLOW_REFINEMENT

  THR_COMP_NEW_NEARL3A,
  THR_COMP_NEAR_NEWL3A,
  THR_COMP_NEW_NEWL3A,
  THR_COMP_GLOBAL_GLOBALL3A,
#if CONFIG_OPTFLOW_REFINEMENT
  THR_COMP_NEAR_NEAR_OPTFLOWL3A,
  THR_COMP_NEAR_NEW_OPTFLOWL3A,
  THR_COMP_NEW_NEAR_OPTFLOWL3A,
  THR_COMP_GLOBAL_GLOBAL_OPTFLOWL3A,
  THR_COMP_NEW_NEW_OPTFLOWL3A,
#endif  // CONFIG_OPTFLOW_REFINEMENT

  THR_COMP_NEW_NEARGA,
  THR_COMP_NEAR_NEWGA,
  THR_COMP_NEW_NEWGA,
  THR_COMP_GLOBAL_GLOBALGA,
#if CONFIG_OPTFLOW_REFINEMENT
  THR_COMP_NEAR_NEAR_OPTFLOWGA,
  THR_COMP_NEAR_NEW_OPTFLOWGA,
  THR_COMP_NEW_NEAR_OPTFLOWGA,
  THR_COMP_GLOBAL_GLOBAL_OPTFLOWGA,
  THR_COMP_NEW_NEW_OPTFLOWGA,
#endif  // CONFIG_OPTFLOW_REFINEMENT

  THR_COMP_NEW_NEARLB,
  THR_COMP_NEAR_NEWLB,
  THR_COMP_NEW_NEWLB,
  THR_COMP_GLOBAL_GLOBALLB,
#if CONFIG_OPTFLOW_REFINEMENT
  THR_COMP_NEAR_NEAR_OPTFLOWLB,
  THR_COMP_NEAR_NEW_OPTFLOWLB,
  THR_COMP_NEW_NEAR_OPTFLOWLB,
  THR_COMP_GLOBAL_GLOBAL_OPTFLOWLB,
  THR_COMP_NEW_NEW_OPTFLOWLB,
#endif  // CONFIG_OPTFLOW_REFINEMENT

  THR_COMP_NEW_NEARL2B,
  THR_COMP_NEAR_NEWL2B,
  THR_COMP_NEW_NEWL2B,
  THR_COMP_GLOBAL_GLOBALL2B,
#if CONFIG_OPTFLOW_REFINEMENT
  THR_COMP_NEAR_NEAR_OPTFLOWL2B,
  THR_COMP_NEAR_NEW_OPTFLOWL2B,
  THR_COMP_NEW_NEAR_OPTFLOWL2B,
  THR_COMP_GLOBAL_GLOBAL_OPTFLOWL2B,
  THR_COMP_NEW_NEW_OPTFLOWL2B,
#endif  // CONFIG_OPTFLOW_REFINEMENT

  THR_COMP_NEW_NEARL3B,
  THR_COMP_NEAR_NEWL3B,
  THR_COMP_NEW_NEWL3B,
  THR_COMP_GLOBAL_GLOBALL3B,
#if CONFIG_OPTFLOW_REFINEMENT
  THR_COMP_NEAR_NEAR_OPTFLOWL3B,
  THR_COMP_NEAR_NEW_OPTFLOWL3B,
  THR_COMP_NEW_NEAR_OPTFLOWL3B,
  THR_COMP_GLOBAL_GLOBAL_OPTFLOWL3B,
  THR_COMP_NEW_NEW_OPTFLOWL3B,
#endif  // CONFIG_OPTFLOW_REFINEMENT

  THR_COMP_NEW_NEARGB,
  THR_COMP_NEAR_NEWGB,
  THR_COMP_NEW_NEWGB,
  THR_COMP_GLOBAL_GLOBALGB,
#if CONFIG_OPTFLOW_REFINEMENT
  THR_COMP_NEAR_NEAR_OPTFLOWGB,
  THR_COMP_NEAR_NEW_OPTFLOWGB,
  THR_COMP_NEW_NEAR_OPTFLOWGB,
  THR_COMP_GLOBAL_GLOBAL_OPTFLOWGB,
  THR_COMP_NEW_NEW_OPTFLOWGB,
#endif  // CONFIG_OPTFLOW_REFINEMENT

  THR_COMP_NEW_NEARLA2,
  THR_COMP_NEAR_NEWLA2,
  THR_COMP_NEW_NEWLA2,
  THR_COMP_GLOBAL_GLOBALLA2,
#if CONFIG_OPTFLOW_REFINEMENT
  THR_COMP_NEAR_NEAR_OPTFLOWLA2,
  THR_COMP_NEAR_NEW_OPTFLOWLA2,
  THR_COMP_NEW_NEAR_OPTFLOWLA2,
  THR_COMP_GLOBAL_GLOBAL_OPTFLOWLA2,
  THR_COMP_NEW_NEW_OPTFLOWLA2,
#endif  // CONFIG_OPTFLOW_REFINEMENT

  THR_COMP_NEW_NEARL2A2,
  THR_COMP_NEAR_NEWL2A2,
  THR_COMP_NEW_NEWL2A2,
  THR_COMP_GLOBAL_GLOBALL2A2,
#if CONFIG_OPTFLOW_REFINEMENT
  THR_COMP_NEAR_NEAR_OPTFLOWL2A2,
  THR_COMP_NEAR_NEW_OPTFLOWL2A2,
  THR_COMP_NEW_NEAR_OPTFLOWL2A2,
  THR_COMP_GLOBAL_GLOBAL_OPTFLOWL2A2,
  THR_COMP_NEW_NEW_OPTFLOWL2A2,
#endif  // CONFIG_OPTFLOW_REFINEMENT

  THR_COMP_NEW_NEARL3A2,
  THR_COMP_NEAR_NEWL3A2,
  THR_COMP_NEW_NEWL3A2,
  THR_COMP_GLOBAL_GLOBALL3A2,
#if CONFIG_OPTFLOW_REFINEMENT
  THR_COMP_NEAR_NEAR_OPTFLOWL3A2,
  THR_COMP_NEAR_NEW_OPTFLOWL3A2,
  THR_COMP_NEW_NEAR_OPTFLOWL3A2,
  THR_COMP_GLOBAL_GLOBAL_OPTFLOWL3A2,
  THR_COMP_NEW_NEW_OPTFLOWL3A2,
#endif  // CONFIG_OPTFLOW_REFINEMENT

  THR_COMP_NEW_NEARGA2,
  THR_COMP_NEAR_NEWGA2,
  THR_COMP_NEW_NEWGA2,
  THR_COMP_GLOBAL_GLOBALGA2,
#if CONFIG_OPTFLOW_REFINEMENT
  THR_COMP_NEAR_NEAR_OPTFLOWGA2,
  THR_COMP_NEAR_NEW_OPTFLOWGA2,
  THR_COMP_NEW_NEAR_OPTFLOWGA2,
  THR_COMP_GLOBAL_GLOBAL_OPTFLOWGA2,
  THR_COMP_NEW_NEW_OPTFLOWGA2,
#endif  // CONFIG_OPTFLOW_REFINEMENT

  THR_COMP_NEW_NEARLL2,
  THR_COMP_NEAR_NEWLL2,
  THR_COMP_NEW_NEWLL2,
  THR_COMP_GLOBAL_GLOBALLL2,
#if CONFIG_OPTFLOW_REFINEMENT
  THR_COMP_NEAR_NEAR_OPTFLOWLL2,
  THR_COMP_NEAR_NEW_OPTFLOWLL2,
  THR_COMP_NEW_NEAR_OPTFLOWLL2,
  THR_COMP_GLOBAL_GLOBAL_OPTFLOWLL2,
  THR_COMP_NEW_NEW_OPTFLOWLL2,
#endif  // CONFIG_OPTFLOW_REFINEMENT

  THR_COMP_NEW_NEARLL3,
  THR_COMP_NEAR_NEWLL3,
  THR_COMP_NEW_NEWLL3,
  THR_COMP_GLOBAL_GLOBALLL3,
#if CONFIG_OPTFLOW_REFINEMENT
  THR_COMP_NEAR_NEAR_OPTFLOWLL3,
  THR_COMP_NEAR_NEW_OPTFLOWLL3,
  THR_COMP_NEW_NEAR_OPTFLOWLL3,
  THR_COMP_GLOBAL_GLOBAL_OPTFLOWLL3,
  THR_COMP_NEW_NEW_OPTFLOWLL3,
#endif  // CONFIG_OPTFLOW_REFINEMENT

  THR_COMP_NEW_NEARLG,
  THR_COMP_NEAR_NEWLG,
  THR_COMP_NEW_NEWLG,
  THR_COMP_GLOBAL_GLOBALLG,
#if CONFIG_OPTFLOW_REFINEMENT
  THR_COMP_NEAR_NEAR_OPTFLOWLG,
  THR_COMP_NEAR_NEW_OPTFLOWLG,
  THR_COMP_NEW_NEAR_OPTFLOWLG,
  THR_COMP_GLOBAL_GLOBAL_OPTFLOWLG,
  THR_COMP_NEW_NEW_OPTFLOWLG,
#endif  // CONFIG_OPTFLOW_REFINEMENT

  THR_COMP_NEW_NEARBA,
  THR_COMP_NEAR_NEWBA,
  THR_COMP_NEW_NEWBA,
  THR_COMP_GLOBAL_GLOBALBA,
#if CONFIG_OPTFLOW_REFINEMENT
  THR_COMP_NEAR_NEAR_OPTFLOWBA,
  THR_COMP_NEAR_NEW_OPTFLOWBA,
  THR_COMP_NEW_NEAR_OPTFLOWBA,
  THR_COMP_GLOBAL_GLOBAL_OPTFLOWBA,
  THR_COMP_NEW_NEW_OPTFLOWBA,
#endif  // CONFIG_OPTFLOW_REFINEMENT

  THR_DC,
  THR_PAETH,
  THR_SMOOTH,
  THR_SMOOTH_V,
  THR_SMOOTH_H,
  THR_H_PRED,
  THR_V_PRED,
  THR_D135_PRED,
  THR_D203_PRED,
  THR_D157_PRED,
  THR_D67_PRED,
  THR_D113_PRED,
  THR_D45_PRED,

  MAX_MODES,

  LAST_SINGLE_REF_MODES = THR_GLOBALG,
  MAX_SINGLE_REF_MODES = LAST_SINGLE_REF_MODES + 1,
  LAST_COMP_REF_MODES = THR_COMP_GLOBAL_GLOBALBA,
  MAX_COMP_REF_MODES = LAST_COMP_REF_MODES + 1
} UENUM1BYTE(THR_MODES);
#else
enum {
  THR_NEARESTMV,
  THR_NEARESTL2,
  THR_NEARESTL3,
  THR_NEARESTB,
  THR_NEARESTA2,
  THR_NEARESTA,
  THR_NEARESTG,

  THR_NEWMV,
  THR_NEWL2,
  THR_NEWL3,
  THR_NEWB,
  THR_NEWA2,
  THR_NEWA,
  THR_NEWG,

  THR_NEARMV,
  THR_NEARL2,
  THR_NEARL3,
  THR_NEARB,
  THR_NEARA2,
  THR_NEARA,
  THR_NEARG,

  THR_GLOBALMV,
  THR_GLOBALL2,
  THR_GLOBALL3,
  THR_GLOBALB,
  THR_GLOBALA2,
  THR_GLOBALG,
  THR_GLOBALA,
  LAST_SINGLE_REF_MODES = THR_GLOBALA,

  THR_COMP_NEAREST_NEARESTLA,
  THR_COMP_NEAREST_NEARESTL2A,
  THR_COMP_NEAREST_NEARESTL3A,
  THR_COMP_NEAREST_NEARESTGA,
  THR_COMP_NEAREST_NEARESTLB,
  THR_COMP_NEAREST_NEARESTL2B,
  THR_COMP_NEAREST_NEARESTL3B,
  THR_COMP_NEAREST_NEARESTGB,
  THR_COMP_NEAREST_NEARESTLA2,
  THR_COMP_NEAREST_NEARESTL2A2,
  THR_COMP_NEAREST_NEARESTL3A2,
  THR_COMP_NEAREST_NEARESTGA2,
  THR_COMP_NEAREST_NEARESTLL2,
  THR_COMP_NEAREST_NEARESTLL3,
  THR_COMP_NEAREST_NEARESTLG,
  THR_COMP_NEAREST_NEARESTBA,

  THR_COMP_NEAR_NEARLA,
  THR_COMP_NEW_NEARESTLA,
  THR_COMP_NEAREST_NEWLA,
  THR_COMP_NEW_NEARLA,
  THR_COMP_NEAR_NEWLA,
  THR_COMP_NEW_NEWLA,
  THR_COMP_GLOBAL_GLOBALLA,

  THR_COMP_NEAR_NEARL2A,
  THR_COMP_NEW_NEARESTL2A,
  THR_COMP_NEAREST_NEWL2A,
  THR_COMP_NEW_NEARL2A,
  THR_COMP_NEAR_NEWL2A,
  THR_COMP_NEW_NEWL2A,
  THR_COMP_GLOBAL_GLOBALL2A,

  THR_COMP_NEAR_NEARL3A,
  THR_COMP_NEW_NEARESTL3A,
  THR_COMP_NEAREST_NEWL3A,
  THR_COMP_NEW_NEARL3A,
  THR_COMP_NEAR_NEWL3A,
  THR_COMP_NEW_NEWL3A,
  THR_COMP_GLOBAL_GLOBALL3A,

  THR_COMP_NEAR_NEARGA,
  THR_COMP_NEW_NEARESTGA,
  THR_COMP_NEAREST_NEWGA,
  THR_COMP_NEW_NEARGA,
  THR_COMP_NEAR_NEWGA,
  THR_COMP_NEW_NEWGA,
  THR_COMP_GLOBAL_GLOBALGA,

  THR_COMP_NEAR_NEARLB,
  THR_COMP_NEW_NEARESTLB,
  THR_COMP_NEAREST_NEWLB,
  THR_COMP_NEW_NEARLB,
  THR_COMP_NEAR_NEWLB,
  THR_COMP_NEW_NEWLB,
  THR_COMP_GLOBAL_GLOBALLB,

  THR_COMP_NEAR_NEARL2B,
  THR_COMP_NEW_NEARESTL2B,
  THR_COMP_NEAREST_NEWL2B,
  THR_COMP_NEW_NEARL2B,
  THR_COMP_NEAR_NEWL2B,
  THR_COMP_NEW_NEWL2B,
  THR_COMP_GLOBAL_GLOBALL2B,

  THR_COMP_NEAR_NEARL3B,
  THR_COMP_NEW_NEARESTL3B,
  THR_COMP_NEAREST_NEWL3B,
  THR_COMP_NEW_NEARL3B,
  THR_COMP_NEAR_NEWL3B,
  THR_COMP_NEW_NEWL3B,
  THR_COMP_GLOBAL_GLOBALL3B,

  THR_COMP_NEAR_NEARGB,
  THR_COMP_NEW_NEARESTGB,
  THR_COMP_NEAREST_NEWGB,
  THR_COMP_NEW_NEARGB,
  THR_COMP_NEAR_NEWGB,
  THR_COMP_NEW_NEWGB,
  THR_COMP_GLOBAL_GLOBALGB,

  THR_COMP_NEAR_NEARLA2,
  THR_COMP_NEW_NEARESTLA2,
  THR_COMP_NEAREST_NEWLA2,
  THR_COMP_NEW_NEARLA2,
  THR_COMP_NEAR_NEWLA2,
  THR_COMP_NEW_NEWLA2,
  THR_COMP_GLOBAL_GLOBALLA2,

  THR_COMP_NEAR_NEARL2A2,
  THR_COMP_NEW_NEARESTL2A2,
  THR_COMP_NEAREST_NEWL2A2,
  THR_COMP_NEW_NEARL2A2,
  THR_COMP_NEAR_NEWL2A2,
  THR_COMP_NEW_NEWL2A2,
  THR_COMP_GLOBAL_GLOBALL2A2,

  THR_COMP_NEAR_NEARL3A2,
  THR_COMP_NEW_NEARESTL3A2,
  THR_COMP_NEAREST_NEWL3A2,
  THR_COMP_NEW_NEARL3A2,
  THR_COMP_NEAR_NEWL3A2,
  THR_COMP_NEW_NEWL3A2,
  THR_COMP_GLOBAL_GLOBALL3A2,

  THR_COMP_NEAR_NEARGA2,
  THR_COMP_NEW_NEARESTGA2,
  THR_COMP_NEAREST_NEWGA2,
  THR_COMP_NEW_NEARGA2,
  THR_COMP_NEAR_NEWGA2,
  THR_COMP_NEW_NEWGA2,
  THR_COMP_GLOBAL_GLOBALGA2,

  THR_COMP_NEAR_NEARLL2,
  THR_COMP_NEW_NEARESTLL2,
  THR_COMP_NEAREST_NEWLL2,
  THR_COMP_NEW_NEARLL2,
  THR_COMP_NEAR_NEWLL2,
  THR_COMP_NEW_NEWLL2,
  THR_COMP_GLOBAL_GLOBALLL2,

  THR_COMP_NEAR_NEARLL3,
  THR_COMP_NEW_NEARESTLL3,
  THR_COMP_NEAREST_NEWLL3,
  THR_COMP_NEW_NEARLL3,
  THR_COMP_NEAR_NEWLL3,
  THR_COMP_NEW_NEWLL3,
  THR_COMP_GLOBAL_GLOBALLL3,

  THR_COMP_NEAR_NEARLG,
  THR_COMP_NEW_NEARESTLG,
  THR_COMP_NEAREST_NEWLG,
  THR_COMP_NEW_NEARLG,
  THR_COMP_NEAR_NEWLG,
  THR_COMP_NEW_NEWLG,
  THR_COMP_GLOBAL_GLOBALLG,

  THR_COMP_NEAR_NEARBA,
  THR_COMP_NEW_NEARESTBA,
  THR_COMP_NEAREST_NEWBA,
  THR_COMP_NEW_NEARBA,
  THR_COMP_NEAR_NEWBA,
  THR_COMP_NEW_NEWBA,
  THR_COMP_GLOBAL_GLOBALBA,

  THR_DC,
  THR_PAETH,
  THR_SMOOTH,
  THR_SMOOTH_V,
  THR_SMOOTH_H,
  THR_H_PRED,
  THR_V_PRED,
  THR_D135_PRED,
  THR_D203_PRED,
  THR_D157_PRED,
  THR_D67_PRED,
  THR_D113_PRED,
  THR_D45_PRED,

  MAX_MODES,

  MAX_SINGLE_REF_MODES = LAST_SINGLE_REF_MODES + 1,
  LAST_COMP_REF_MODES = THR_DC - 1,
  MAX_COMP_REF_MODES = LAST_COMP_REF_MODES + 1
} UENUM2BYTE(THR_MODES);
#endif  // CONFIG_NEW_INTER_MODES

enum {
  THR_LAST,
  THR_LAST2,
  THR_LAST3,
  THR_BWDR,
  THR_ALTR2,
  THR_GOLD,
  THR_ALTR,

  THR_COMP_LA,
  THR_COMP_L2A,
  THR_COMP_L3A,
  THR_COMP_GA,

  THR_COMP_LB,
  THR_COMP_L2B,
  THR_COMP_L3B,
  THR_COMP_GB,

  THR_COMP_LA2,
  THR_COMP_L2A2,
  THR_COMP_L3A2,
  THR_COMP_GA2,

  THR_INTRA,

  MAX_REFS
} UENUM1BYTE(THR_MODES_SUB8X8);

enum {
  NO_AQ = 0,
  VARIANCE_AQ = 1,
  COMPLEXITY_AQ = 2,
  CYCLIC_REFRESH_AQ = 3,
  AQ_MODE_COUNT  // This should always be the last member of the enum
} UENUM1BYTE(AQ_MODE);

#ifdef __cplusplus
}  // extern "C"
#endif

#endif  // AOM_AV1_ENCODER_ENC_ENUMS_H_