/* readable reconstruction; identity: FUN_0000c358 @ 0x0000c358
 * public-name: battery_model_state_update
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   battery_model_state_update               <= FUN_0000c358 @ 0x0000c358
 *   __extendsfdf2                            <= FUN_0000d848 @ 0x0000d848
 *   __aeabi_dcmpgt                           <= FUN_0000de18 @ 0x0000de18
 *   curve_table_interp_201pt                 <= FUN_0000e3a0 @ 0x0000e3a0
 *   float_is_nan                             <= FUN_0000e938 @ 0x0000e938
 *   array_max_skip_nan_a                     <= FUN_0000e954 @ 0x0000e954
 *   array_max_skip_nan_b                     <= FUN_0000e9b4 @ 0x0000e9b4
 *   strtod_scan_int_prefix                   <= FUN_0000ea18 @ 0x0000ea18
 *   strtod_has_more_digits                   <= FUN_0000ea4c @ 0x0000ea4c
 *   spline_interp_pair_2out                  <= FUN_0000ea70 @ 0x0000ea70
 *   spline_interp_3pt                        <= FUN_0000eb7c @ 0x0000eb7c
 *   expf                                     <= FUN_00075c90 @ 0x00075c90
 *   sqrtf                                    <= FUN_00075dc8 @ 0x00075dc8
 *   fabsf                                    <= FUN_000868ee @ 0x000868ee
 *   floorf                                   <= FUN_000868fc @ 0x000868fc
 *   fmaxf                                    <= FUN_00086902 @ 0x00086902
 *   fminf                                    <= FUN_0008693c @ 0x0008693c
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   g_spline_nan_sentinel                    @ 0x20002d1c
 */
/* Reconstructed FUN_0000c358 @ 0xc358  (strict reviewed production fixtures)
 * CFG coverage: two finite 48-call/105-event estimator cases plus the
 * param_3 == 0 matrix-copy path (49 calls/106 events) pass strictly.
 */
typedef unsigned char      undefined1;
typedef unsigned int       undefined4;
typedef unsigned long long undefined8;
typedef unsigned int       uint;
typedef unsigned long long ulonglong;
#define NAN(x) __builtin_isnan(x)

/* literal-pool constants */
#define DAT_0000cad0  0.9998999834060669f      /* 0x3f7ff972 */
#define DAT_0000cad4  9.999999747378752e-05f   /* 0x38d1b717 */
#define DAT_0000cad8  3600.0f                  /* 0x45610000 */
#define DAT_0000cae0  (-0.05000000074505806f)  /* 0xbd4ccccd */
#define DAT_0000cae4  1.0499999523162842f      /* 0x3f866666 */
#define DAT_0000caf0  0.0f                     /* 0x00000000 */
#define DAT_0000caf4  100.0f                   /* 0x42c80000 */
#define DAT_0000d230  0.0f
#define DAT_0000d234  (-0.05000000074505806f)
#define DAT_0000d238  1.0499999523162842f
#define DAT_0000d23c  0.0f
#define DAT_0000d57c  0.0f
/* DAT_0000cae8/caec : the 64-bit double literal passed to FUN_0000de18 */
#define DAT_0000cae8  ((int)0xd2f1a9fc)
#define DAT_0000caec  ((int)0x3f70624d)
/* pointer globals (both point at 0x20002d1c) */
#define DAT_0000cadc  ((volatile float *)0x20002d1c)
#define DAT_0000d578  ((volatile float *)0x20002d1c)

extern float array_max_skip_nan_a(float *);
extern float array_max_skip_nan_b(float *);
extern float fminf(float, float);
extern float fmaxf(float, float);
extern void  strtod_scan_int_prefix(undefined1 *, int *, int *);
extern float spline_interp_3pt(float, float *, float *);
extern void  spline_interp_pair_2out(float, float *, float *, float *);
extern float fabsf(float);
extern float expf(float);
extern void memcpy(int, int, int);
extern void memset_bytes(void*, int, int);
extern int   float_is_nan(float);
extern long long __extendsfdf2(unsigned);
extern int   __aeabi_dcmpgt(int, int, int, int);
extern float curve_table_interp_201pt(float, float, float *, float *, float *);
extern int   strtod_has_more_digits(undefined1 *, undefined4 *);
extern float floorf(float);
extern float sqrtf(float);

static inline unsigned float_bits(float x)
{
  union { float f; unsigned u; } v = { x };
  return v.u;
}

#define local_240 auStack_244[1]
#define local_190 (local_1a0 + 4)

void battery_model_state_update(float param_1,float param_2,float param_3,float param_4,float *param_5,
                 float *param_6,float *param_7,float *param_8)
{
  int bVar1;
  int bVar2;
  int bVar3;
  float *pfVar4;
  float *pfVar5;
  float *pfVar6;
  int *piVar7;
  float *pfVar8;
  float *pfVar9;
  float *pfVar10;
  undefined1 *puVar11;
  int *piVar12;
  float *pfVar13;
  float *pfVar15;
  float *pfVar16;
  int iVar17;
  int iVar18;
  float *pfVar19;
  float *pfVar20;
  int iVar21;
  float *pfVar22;
  int *piVar23;
  float *pfVar24;
  float uVar25;
  float uVar26;
  float uVar27;
  float fVar28;
  float fVar29;
  float fVar30;
  float fVar31;
  float fVar32;
  float fVar33;
  float fVar34;
  float fVar35;
  float fVar36;
  float extraout_s12 = 0.0f;
  float fVar37;
  float fVar38;
  float fVar39;
  float fVar40;
  float fVar41;
  float fVar42;
  float fVar43;
  undefined8 uVar44;
  int local_280;
  float *local_27c;
  float *local_278;
  float *local_270;
  int local_26c;
  int local_268;
  undefined1 local_258 [4];
  float local_254 [2];
  undefined4 local_24c;
  int local_248;
  int auStack_244 [2];
  float local_23c [12];
  int aiStack_20c [3];
  float local_200 [8];
  float local_1e0 [4];
  float local_1d0 [6];
  float local_1b8 [6];
  float local_1a0 [8];
  float local_180 [12];
  float local_150 [7];
  float afStack_134 [5];
  float local_120 [16];
  float local_100 [4];
  float local_f0 [4];
  float local_e0 [4];
  float local_d0 [4];
  float local_c0 [4];
  float local_b0 [4];
  float local_a0 [16];
  float fStack_60;
  float *pfVar14;

  fVar41 = param_5[0x5d2];
  if (((*(char *)(param_5 + 0x5d3) != '\x01') && (-1 < (int)((uint)(param_3 < fVar41) << 0x1f))) &&
     (fVar41 = param_5[0x5d1], -1 < (int)((uint)(param_5[0x5d1] < param_3) << 0x1f))) {
    fVar41 = param_3;
  }
  pfVar10 = param_5 + 0x11a;
  uVar25 = array_max_skip_nan_a(pfVar10);
  pfVar9 = param_5 + 0x11b;
  pfVar15 = param_5 + 0x11c;
  uVar26 = array_max_skip_nan_b(pfVar10);
  uVar27 = fminf(fVar41,uVar25);
  fVar28 = (float)fmaxf(uVar27,uVar26);
  local_258[0] = *pfVar10 == fVar28;
  local_258[1] = *pfVar9 == fVar28;
  local_258[2] = *pfVar15 == fVar28;
  strtod_scan_int_prefix(local_258,aiStack_20c,auStack_244);
  local_26c = local_240;
  if (local_240 == 0) {
    local_23c[0] = (float)spline_interp_3pt(fVar28,pfVar10,param_5 + 0x5be);
    local_26c = 1;
  }
  else if (0 < local_240) {
    pfVar8 = local_23c;
    piVar7 = aiStack_20c;
    do {
      piVar12 = piVar7 + 1;
      *pfVar8 = param_5[*piVar7 + 0x5bd];
      pfVar8 = pfVar8 + 1;
      piVar7 = piVar12;
    } while (piVar12 != aiStack_20c + local_240);
  }
  local_278 = local_23c;
  uVar27 = fminf(fVar41,uVar25);
  fVar28 = (float)fmaxf(uVar27,uVar26);
  local_258[0] = *pfVar10 == fVar28;
  local_258[1] = *pfVar9 == fVar28;
  local_258[2] = *pfVar15 == fVar28;
  strtod_scan_int_prefix(local_258,aiStack_20c,auStack_244);
  if (local_240 == 0) {
    spline_interp_pair_2out(fVar28,pfVar10,param_5 + 0x5b2,local_254);
    iVar21 = 2;
    local_1b8[0] = local_254[0];
    local_1b8[1] = local_254[1];
    local_268 = 4;
    iVar18 = iVar21;
LAB_0000c51e:
    local_27c = local_1b8;
    pfVar8 = local_1d0;
    iVar17 = 0;
    do {
      fVar28 = *local_27c;
      local_27c = local_27c + 1;
      fVar28 = (float)fabsf(fVar28);
      iVar17 = iVar17 + 1;
      *pfVar8 = fVar28;
      pfVar8 = pfVar8 + 1;
    } while (iVar17 < iVar21);
    if (0 < iVar18) {
LAB_0000c546:
      local_270 = local_1d0;
      iVar17 = 0;
      do {
        iVar17 = iVar17 + 1;
        *local_270 = -param_4 / *local_270;
        local_270 = local_270 + 1;
      } while (iVar17 < iVar18);
      if (iVar21 < 1) goto LAB_0000c580;
    }
    local_270 = local_1d0;
    iVar18 = 0;
    do {
      fVar28 = (float)expf(*local_270);
      iVar18 = iVar18 + 1;
      *local_270 = fVar28;
      local_270 = local_270 + 1;
    } while (iVar21 != iVar18);
  }
  else {
    iVar21 = local_240 * 2;
    if (0 < local_240) {
      local_268 = local_240 * 4;
      piVar12 = aiStack_20c + local_240;
      piVar7 = aiStack_20c;
      pfVar8 = local_1b8;
      do {
        piVar23 = piVar7 + 1;
        *pfVar8 = param_5[*piVar7 + 0x5b1];
        piVar7 = piVar23;
        pfVar8 = pfVar8 + 1;
      } while (piVar12 != piVar23);
      piVar7 = aiStack_20c;
      pfVar8 = local_1b8 + local_240;
      do {
        piVar23 = piVar7 + 1;
        *pfVar8 = param_5[*piVar7 + 0x5b4];
        piVar7 = piVar23;
        pfVar8 = pfVar8 + 1;
      } while (piVar23 != piVar12);
      iVar18 = iVar21;
      if (0 < iVar21) goto LAB_0000c51e;
      iVar18 = 0x7fffffff;
      goto LAB_0000c546;
    }
    if (0 < iVar21) {
      local_268 = local_240 << 2;
      iVar18 = -0x80000000;
      goto LAB_0000c51e;
    }
    local_268 = local_240 << 2;
  }
LAB_0000c580:
  local_27c = local_1b8;
  uVar27 = fminf(fVar41,uVar25);
  fVar28 = (float)fmaxf(uVar27,uVar26);
  local_258[0] = *pfVar10 == fVar28;
  local_258[1] = *pfVar9 == fVar28;
  local_258[2] = *pfVar15 == fVar28;
  strtod_scan_int_prefix(local_258,aiStack_20c,auStack_244);
  if (local_240 == 0) {
    spline_interp_pair_2out(fVar28,pfVar10,param_5 + 0x5b8,local_254);
    iVar18 = 4;
    fVar28 = local_254[0];
  }
  else {
    fVar28 = local_1b8[0];
    if (local_240 < 1) {
      iVar18 = local_240 << 2;
    }
    else {
      iVar18 = local_240 * 4;
      piVar12 = aiStack_20c + local_240;
      piVar7 = aiStack_20c;
      pfVar8 = local_27c;
      do {
        piVar23 = piVar7 + 1;
        *pfVar8 = param_5[*piVar7 + 0x5b7];
        piVar7 = piVar23;
        pfVar8 = pfVar8 + 1;
      } while (piVar12 != piVar23);
      pfVar8 = local_27c + local_240;
      piVar7 = aiStack_20c;
      do {
        piVar23 = piVar7 + 1;
        *pfVar8 = param_5[*piVar7 + 0x5ba];
        pfVar8 = pfVar8 + 1;
        piVar7 = piVar23;
      } while (piVar12 != piVar23);
    }
  }
  uVar25 = fminf(fVar41,uVar25);
  fVar29 = (float)fmaxf(uVar25,uVar26);
  local_258[0] = *pfVar10 == fVar29;
  local_258[1] = *pfVar9 == fVar29;
  local_258[2] = *pfVar15 == fVar29;
  strtod_scan_int_prefix(local_258,aiStack_20c,auStack_244);
  local_280 = local_240;
  if (local_240 == 0) {
    local_23c[3] = (float)spline_interp_3pt(fVar29,pfVar10,param_5 + 0x5af);
    local_280 = 1;
  }
  else if (0 < local_240) {
    pfVar15 = local_23c + 3;
    piVar7 = aiStack_20c;
    do {
      piVar12 = piVar7 + 1;
      *pfVar15 = param_5[*piVar7 + 0x5ae];
      pfVar15 = pfVar15 + 1;
      piVar7 = piVar12;
    } while (aiStack_20c + local_240 != piVar12);
  }
  fVar43 = *(float *)((int)local_27c + iVar18);
  fVar29 = (float)fabsf(param_1 - param_5[0x17]);
  fVar30 = (float)fabsf(param_5[0x15] - param_2);
  uVar44 = __extendsfdf2(float_bits(fVar30));
  iVar18 = __aeabi_dcmpgt((int)uVar44,(int)((ulonglong)uVar44 >> 0x20),DAT_0000cae8,DAT_0000caec);
  if (iVar18 == 0) {
LAB_0000c72a:
    fVar29 = param_5[0x5da];
  }
  else {
    uVar44 = __extendsfdf2(float_bits(fVar29));
    iVar18 = __aeabi_dcmpgt((int)uVar44,(int)((ulonglong)uVar44 >> 0x20),DAT_0000cae8,DAT_0000caec);
    if ((iVar18 == 0) || (-1 < (int)((uint)(param_3 < 0.0f) << 0x1f))) goto LAB_0000c72a;
    fVar29 = fVar29 / fVar30;
  }
  fVar30 = param_5[0x5dd] * DAT_0000cad0 + fVar29 * DAT_0000cad4;
  fVar42 = param_5[0x5dc] * DAT_0000cad0 + fVar30 * DAT_0000cad4;
  local_23c[6] = -fVar42 + fVar30 * 2.0f;
  if (((int)((uint)(param_5[0x5d2] < param_3) << 0x1f) < 0) || (param_3 < 0.0f == NAN(param_3))) {
    memcpy(local_23c + 6,local_23c + 3,local_280 << 2);
  }
  else {
    local_280 = 1;
  }
  memset_bytes(local_120,0,0x40);
  fVar36 = local_23c[0];
  fVar39 = DAT_0000caf0;
  local_200[0] = 0.0f;
  local_200[1] = 0.0f;
  local_200[2] = 0.0f;
  local_200[3] = 0.0f;
  iVar18 = (int)param_5[0x5d5] + -1;
  local_120[(int)param_5[0x5d5] + iVar18 * 4 + -1] = 1.0f;
  if (0 < local_26c) {
    pfVar15 = local_278;
    do {
      *pfVar15 = *pfVar15 * DAT_0000cad8;
      pfVar15 = pfVar15 + 1;
    } while (local_278 + local_26c != pfVar15);
  }
  fVar40 = param_5[1];
  fVar35 = param_5[0x15];
  fVar37 = *param_5;
  fVar38 = *(float *)((int)local_1d0 + local_268);
  local_200[iVar18] = -param_4 / local_23c[0];
  iVar18 = (int)fVar37 + -1;
  local_120[(int)fVar37 + iVar18 * 4 + -1] = local_1d0[0];
  iVar21 = (int)fVar40 + -1;
  local_120[(int)fVar40 + iVar21 * 4 + -1] = fVar38;
  local_200[iVar18] = 1.0f - local_1d0[0];
  local_200[iVar21] = 1.0f - fVar38;
  local_200[7] = fVar38;
  fVar35 = (float)expf(-((fVar35 * DAT_0000caf0 * param_4) / local_23c[0]));
  local_1a0[0] = local_200[0];
  local_1a0[1] = local_200[1];
  local_190[0] = local_200[0] * fVar39;
  local_190[1] = local_200[1] * fVar39;
  local_1a0[2] = local_200[2];
  local_1a0[3] = local_200[3];
  local_190[2] = local_200[2] * fVar39;
  local_190[3] = local_200[3] * fVar39;
  fVar37 = param_5[0x15];
  local_120[((int)param_5[0x5d4] - 1) * 5] = fVar35;
  iVar18 = float_is_nan(fVar37);
  if (iVar18 == 0) {
    fVar37 = param_5[0x15];
    if (fVar37 < 0.0f) {
      fVar39 = -1.0f;
    }
    else if (fVar37 != 0.0f) {
      fVar39 = 1.0f;
    }
  }
  else {
    fVar37 = param_5[0x15];
    fVar39 = *DAT_0000cadc;
  }
  iVar21 = (int)param_5[0x5d4];
  fVar38 = param_5[0x5d6];
  fVar40 = param_5[0x5d7];
  fVar34 = param_5[0x5d9];
  local_190[iVar21 + -1] = fVar35 - 1.0f;
  pfVar15 = local_120;
  pfVar9 = local_a0;
  iVar18 = 0;
  local_200[iVar21 + -1] =
       -(((param_4 * DAT_0000caf0) / fVar36) * fVar35) * (param_5[iVar21 + 0x5d5] * fVar39 + 1.0f);
  fVar36 = param_5[0x5d8];
  pfVar22 = local_1e0;
  pfVar19 = param_5 + 0x10;
  pfVar10 = pfVar15;
  pfVar8 = local_e0;
  pfVar20 = local_1a0;
  pfVar24 = pfVar9;
  do {
    fVar35 = pfVar10[4];
    fVar32 = pfVar10[8];
    fVar33 = pfVar10[0xc];
    fVar31 = *pfVar10;
    pfVar10 = pfVar10 + 1;
    {
      float matrix_sum = fVar40 * fVar35 + fVar31 * fVar38 +
                         fVar32 * fVar36 + fVar33 * fVar34;
      float state_sum = fVar39 * pfVar20[4] + *pfVar20 * fVar37;
      *pfVar22 = matrix_sum + state_sum;
    }
    pfVar22 = pfVar22 + 1;
    pfVar13 = param_5;
    pfVar16 = pfVar8;
    do {
      pfVar14 = pfVar13 + 3;
      pfVar4 = pfVar13 + 2;
      pfVar5 = pfVar13 + 4;
      pfVar6 = pfVar13 + 5;
      pfVar13 = pfVar13 + 4;
      *pfVar16 = fVar35 * *pfVar14 + fVar31 * *pfVar4 + fVar32 * *pfVar5 + fVar33 * *pfVar6;
      pfVar16 = pfVar16 + 4;
    } while (pfVar19 != pfVar13);
    fVar35 = *pfVar8;
    fVar31 = pfVar8[4];
    fVar32 = pfVar8[8];
    fVar33 = pfVar8[0xc];
    pfVar13 = local_120;
    pfVar16 = pfVar24;
    do {
      pfVar14 = pfVar13 + 1;
      *pfVar16 = fVar31 * pfVar13[4] + *pfVar13 * fVar35 + fVar32 * pfVar13[8] +
                 fVar33 * pfVar13[0xc];
      pfVar16 = pfVar16 + 4;
      pfVar13 = pfVar14;
    } while (local_120 + 4 != pfVar14);
    iVar18 = iVar18 + 1;
    pfVar24 = pfVar24 + 1;
    pfVar8 = pfVar8 + 1;
    pfVar20 = pfVar20 + 1;
  } while (iVar18 != 4);
  uVar25 = fmaxf(-1.0f,local_1e0[iVar21 + -1]);
  fVar36 = param_5[0x5d4];
  fVar39 = (float)fminf(1.0f,uVar25);
  fVar35 = param_5[0x5d5];
  local_1e0[(int)fVar36 + -1] = fVar39;
  uVar25 = fmaxf(DAT_0000cae0,local_1e0[(int)fVar35 + -1]);
  fVar36 = param_5[0x5d5];
  fVar39 = (float)fminf(DAT_0000cae4,uVar25);
  fVar35 = param_5[0x13];
  pfVar20 = local_200;
  local_1e0[(int)fVar36 + -1] = fVar39;
  pfVar10 = pfVar20;
  pfVar8 = local_120;
  do {
    fVar39 = *pfVar10;
    pfVar10 = pfVar10 + 1;
    *pfVar8 = fVar35 * local_200[0] * fVar39;
    pfVar8[1] = fVar39 * fVar35 * local_200[1];
    pfVar8[2] = fVar39 * fVar35 * local_200[2];
    pfVar8[3] = fVar39 * fVar35 * local_200[3];
    pfVar8 = pfVar8 + 4;
  } while (local_200 + 4 != pfVar10);
  pfVar10 = param_5 + 2;
  do {
    fVar36 = *pfVar9;
    pfVar9 = pfVar9 + 1;
    fVar39 = *pfVar15;
    pfVar15 = pfVar15 + 1;
    *pfVar10 = fVar36 + fVar39;
    pfVar10 = pfVar10 + 1;
  } while (local_a0 + 16 != pfVar9);
  fVar36 = param_5[0x119];
  pfVar15 = local_1e0 + (int)param_5[0x5d5];
  fVar39 = param_5[0x51];
  fVar35 = local_1e0[(int)param_5[0x5d5] + -1];
  fVar37 = param_5[0x52] - fVar39;
  if (fVar39 < fVar35 == (NAN(fVar39) || NAN(fVar35))) {
    iVar18 = (uint)(fVar39 < fVar35) << 0x1f;
    if (fVar35 < fVar36 == (NAN(fVar35) || NAN(fVar36))) {
      if (iVar18 < 0) {
        iVar18 = (uint)(fVar35 < fVar36) << 0x1f;
        if (iVar18 < 0) {
          pfVar15 = (float *)0x1;
        }
        if (-1 < iVar18) {
          pfVar15 = (float *)0x0;
        }
      }
      else {
LAB_0000d2aa:
        pfVar15 = (float *)0x0;
      }
LAB_0000d2ac:
      fVar38 = (((param_5[0x328] + param_5[0x25f] * fVar41) -
                (param_5[0x327] + param_5[0x25e] * fVar41)) * (fVar35 - fVar36)) / fVar37 +
               param_5[0x328] + param_5[0x25f] * fVar41;
    }
    else {
      if (iVar18 < 0) {
        iVar18 = (uint)(fVar35 < fVar36) << 0x1f;
        if (iVar18 < 0) {
          pfVar15 = (float *)0x1;
        }
        if (-1 < iVar18) {
          pfVar15 = (float *)0x0;
        }
      }
      else {
        pfVar15 = (float *)0x0;
      }
      fVar38 = ((fVar35 - fVar39) *
               ((param_5[0x261] + param_5[0x198] * fVar41) -
               (param_5[0x260] + param_5[0x197] * fVar41))) / fVar37 + param_5[0x260] +
               param_5[0x197] * fVar41;
    }
    if (pfVar15 != (float *)0x0) {
LAB_0000cc1a:
      fVar39 = (float)floorf((fVar35 - fVar39) / fVar37);
      fVar36 = (local_1e0[(int)param_5[0x5d5] + -1] - param_5[0x51]) / fVar37 - fVar39;
      fVar38 = fVar36 * param_5[(int)(fVar39 + 2.0f) + 0x25f] +
               param_5[(int)(fVar39 + 1.0f) + 0x25f] * (1.0f - fVar36) +
               fVar41 * (fVar36 * param_5[(int)(fVar39 + 2.0f) + 0x196] +
                        param_5[(int)(fVar39 + 1.0f) + 0x196] * (1.0f - fVar36));
    }
  }
  else {
    if ((fVar39 < fVar35) && ((int)((uint)(fVar35 < fVar36) << 0x1f) < 0)) {
      if (fVar35 == fVar36) {
        pfVar15 = (float *)0x1;
        goto LAB_0000d2ac;
      }
      goto LAB_0000cc1a;
    }
    fVar38 = DAT_0000d23c;
    if (fVar35 < fVar36 == (NAN(fVar35) || NAN(fVar36))) goto LAB_0000d2aa;
  }
  iVar18 = float_is_nan(fVar35);
  fVar39 = DAT_0000caf0;
  fVar36 = local_1e0[(int)param_5[1] + -1];
  fVar37 = local_1e0[(int)*param_5 + -1];
  if (0 < local_280) {
    pfVar15 = local_23c + 6;
    pfVar10 = pfVar15 + local_280;
    pfVar9 = local_278;
    do {
      fVar40 = *pfVar15;
      pfVar15 = pfVar15 + 1;
      *pfVar9 = (iVar18 == 0 ? fVar38 : DAT_0000caf0)
                + -fVar36 * fVar43 + -fVar37 * fVar28 + -fVar40 * param_2;
      pfVar9 = pfVar9 + 1;
    } while (pfVar10 != pfVar15);
  }
  fVar38 = param_5[0x5d5];
  local_200[0] = DAT_0000caf0;
  local_200[1] = DAT_0000caf0;
  local_200[2] = DAT_0000caf0;
  local_200[3] = DAT_0000caf0;
  fVar36 = (float)curve_table_interp_201pt(fVar35,fVar41,param_5 + 0x51,param_5 + 0x329,param_5 + 0x3f2);
  fVar35 = *param_5;
  fVar40 = param_5[1];
  fVar37 = param_5[0x5d4];
  local_200[(int)fVar38 + -1] = fVar36;
  local_200[(int)fVar37 + -1] = fVar39;
  local_200[(int)fVar35 + -1] = -fVar28;
  local_200[(int)fVar40 + -1] = -fVar43;
  pfVar15 = param_5;
  do {
    pfVar9 = pfVar15 + 3;
    pfVar10 = pfVar15 + 2;
    pfVar8 = pfVar15 + 4;
    pfVar24 = pfVar15 + 5;
    fVar28 = *pfVar20;
    pfVar20 = pfVar20 + 1;
    pfVar15 = pfVar15 + 4;
    fVar39 = fVar39 + (local_200[1] * *pfVar9 + local_200[0] * *pfVar10 + local_200[2] * *pfVar8 +
                      local_200[3] * *pfVar24) * fVar28;
  } while (pfVar19 != pfVar15);
  pfVar15 = local_200 + 4;
  fVar39 = fVar39 + param_5[0x12];
  pfVar9 = pfVar15;
  pfVar10 = param_5 + 2;
  do {
    pfVar8 = pfVar10 + 1;
    *pfVar9 = (local_200[1] * pfVar10[4] + local_200[0] * *pfVar10 + local_200[2] * pfVar10[8] +
              local_200[3] * pfVar10[0xc]) / fVar39;
    pfVar9 = pfVar9 + 1;
    pfVar10 = pfVar8;
  } while (param_5 + 6 != pfVar8);
  fVar28 = fVar39 * DAT_0000caf4;
  if (local_280 < 1) {
    local_24c = 1;
    local_248 = local_280;
    iVar18 = strtod_has_more_digits(local_258,&local_24c);
    if (iVar18 != 0) {
      local_200[4] = DAT_0000d57c;
      local_200[5] = DAT_0000d57c;
      local_200[6] = DAT_0000d57c;
      local_200[7] = DAT_0000d57c;
    }
  }
  else {
    pfVar9 = local_23c + 3;
    pfVar8 = local_278 + local_280;
    pfVar10 = pfVar9;
    do {
      fVar43 = *local_278;
      local_278 = local_278 + 1;
      *pfVar10 = param_1 - fVar43;
      pfVar10 = pfVar10 + 1;
    } while (pfVar8 != local_278);
    pfVar10 = local_23c + 9;
    pfVar8 = pfVar10;
    do {
      fVar43 = *pfVar9;
      pfVar9 = pfVar9 + 1;
      *pfVar8 = local_23c[3] * fVar43;
      pfVar8 = pfVar8 + 1;
    } while (local_23c + local_280 + 3 != pfVar9);
    local_24c = 1;
    local_248 = local_280;
    pfVar9 = pfVar10 + local_280;
    puVar11 = local_258;
    do {
      fVar43 = *pfVar10;
      pfVar10 = pfVar10 + 1;
      *puVar11 = fVar43 != fVar28 && fVar43 < fVar28 == (NAN(fVar43) || NAN(fVar28));
      puVar11 = puVar11 + 1;
    } while (pfVar9 != pfVar10);
    iVar18 = strtod_has_more_digits(local_258,&local_24c);
    if (iVar18 != 0) {
      local_200[4] = DAT_0000d230;
      local_200[5] = DAT_0000d230;
      local_200[6] = DAT_0000d230;
      local_200[7] = DAT_0000d230;
    }
    pfVar9 = local_23c + 3;
    pfVar8 = pfVar9 + local_280;
    pfVar10 = local_150;
    do {
      fVar43 = *pfVar9;
      pfVar9 = pfVar9 + 1;
      *pfVar10 = local_200[4] * fVar43;
      pfVar10[1] = local_200[5] * fVar43;
      pfVar10[2] = local_200[6] * fVar43;
      pfVar10[3] = local_200[7] * fVar43;
      pfVar10 = pfVar10 + 4;
    } while (pfVar8 != pfVar9);
    pfVar9 = local_180;
    pfVar10 = local_150;
    do {
      fVar43 = *pfVar10;
      fVar36 = pfVar10[1];
      fVar35 = pfVar10[2];
      fVar37 = pfVar10[3];
      pfVar10 = pfVar10 + 4;
      *pfVar9 = fVar43 + local_1e0[0];
      pfVar9[1] = fVar36 + local_1e0[1];
      pfVar9[2] = fVar35 + local_1e0[2];
      pfVar9[3] = fVar37 + local_1e0[3];
      pfVar9 = pfVar9 + 4;
    } while (local_150 + local_280 * 4 != pfVar10);
    pfVar9 = local_150;
    pfVar10 = local_180;
    do {
      pfVar8 = pfVar10 + 4;
      *pfVar9 = *pfVar10;
      pfVar9[1] = pfVar10[1];
      pfVar9[2] = pfVar10[2];
      pfVar9[3] = pfVar10[3];
      pfVar9 = pfVar9 + 4;
      pfVar10 = pfVar8;
    } while (local_180 + local_280 * 4 != pfVar8);
  }
  fVar37 = local_200[7];
  fVar35 = local_200[6];
  fVar36 = local_200[5];
  fVar43 = local_200[4];
  uVar25 = fmaxf(-1.0f,local_150[(int)param_5[0x5d4] + -1]);
  fVar40 = param_5[0x5d4];
  fVar38 = (float)fminf(1.0f,uVar25);
  fVar34 = param_5[0x5d5];
  local_150[(int)fVar40 + -1] = fVar38;
  uVar25 = fmaxf(DAT_0000d234,local_150[(int)fVar34 + -1]);
  fVar40 = param_5[0x5d5];
  fVar38 = (float)fminf(DAT_0000d238,uVar25);
  local_150[(int)fVar40 + -1] = fVar38;
  pfVar9 = param_5;
  do {
    fVar38 = *pfVar15;
    pfVar15 = pfVar15 + 1;
    pfVar10 = pfVar9 + 4;
    pfVar9[2] = pfVar9[2] + fVar38 * -(fVar43 * fVar39);
    pfVar9[3] = pfVar9[3] + -fVar38 * fVar39 * fVar36;
    *pfVar10 = pfVar9[4] + -fVar38 * fVar39 * fVar35;
    pfVar9[5] = pfVar9[5] + -fVar38 * fVar39 * fVar37;
    pfVar9 = pfVar10;
  } while (pfVar19 != pfVar10);
  local_24c = 1;
  local_248 = local_280;
  if (0 < local_280) {
    pfVar15 = local_23c + 9;
    pfVar9 = pfVar15 + local_280;
    puVar11 = local_258;
    do {
      fVar43 = *pfVar15;
      pfVar15 = pfVar15 + 1;
      *puVar11 = fVar43 != fVar28 && fVar43 < fVar28 == (NAN(fVar43) || NAN(fVar28));
      puVar11 = puVar11 + 1;
    } while (pfVar9 != pfVar15);
  }
  iVar18 = strtod_has_more_digits(local_258,&local_24c);
  if (iVar18 == 0) {
    iVar18 = (int)param_5[0x5d5] + -1;
  }
  else {
    iVar18 = (int)param_5[0x5d5] + -1;
    iVar21 = (int)param_5[0x5d5] + iVar18 * 4;
    param_5[iVar21 + 1] = param_5[iVar21 + 1] * param_5[0x14];
  }
  param_5[0x15] = param_2;
  param_5[0x5d6] = local_150[0];
  param_5[0x5d7] = local_150[1];
  param_5[0x5d8] = local_150[2];
  param_5[0x5d9] = local_150[3];
  *param_6 = local_150[iVar18];
  fVar28 = (float)sqrtf(param_5[(int)param_5[0x5d5] * 5 + -3]);
  *param_7 = fVar28 * 3.0f;
  param_5[0x17] = param_1;
  param_5[0x5db] = local_23c[6];
  param_5[0x5da] = fVar29;
  param_5[0x5dc] = fVar42;
  param_5[0x5dd] = fVar30;
  iVar18 = float_is_nan(param_5[0x4b]);
  if (iVar18 != 0) goto LAB_0000d162;
  iVar18 = float_is_nan(param_2);
  if (iVar18 == 0) {
    if (param_2 < 0.0f) {
      fVar28 = -1.0f;
    }
    else {
      fVar28 = DAT_0000d57c;
      if (param_2 != 0.0f) {
        fVar28 = 1.0f;
      }
    }
    iVar18 = float_is_nan(param_5[0x4b]);
    if (iVar18 == 0) goto LAB_0000d4ac;
LAB_0000d34a:
    fVar29 = fVar28 * *DAT_0000d578;
  }
  else {
    fVar28 = *DAT_0000d578;
    iVar18 = float_is_nan(param_5[0x4b]);
    if (iVar18 != 0) goto LAB_0000d34a;
LAB_0000d4ac:
    if (param_5[0x4b] < DAT_0000d57c) {
      fVar29 = -fVar28;
    }
    else {
      fVar29 = fVar28;
      if (param_5[0x4b] == DAT_0000d57c) {
        fVar29 = fVar28 * DAT_0000d57c;
      }
    }
  }
  if (fVar29 == -1.0f) {
    fVar29 = *DAT_0000d578;
    pfVar15 = param_5 + 0x18;
    do {
      pfVar9 = pfVar15 + 1;
      *pfVar15 = fVar29;
      pfVar15[0x19] = fVar29;
      pfVar15 = pfVar9;
    } while (pfVar9 != param_5 + 0x31);
    param_5[0x4f] = 0.0f;
    param_5[0x4e] = 0.0f;
    if (fVar28 == -1.0f) {
      param_5[0x50] = local_150[(int)param_5[0x5d5] + -1];
    }
    else {
      param_5[0x50] = fVar29;
    }
  }
LAB_0000d162:
  fVar28 = (float)fabsf(param_2);
  fVar29 = (float)fabsf(param_5[0x4b]);
  fVar29 = fVar29 * 5.0f;
  bVar1 = fVar28 < fVar29;
  bVar2 = fVar28 == fVar29;
  bVar3 = NAN(fVar28) || NAN(fVar29);
  fVar28 = extraout_s12;
  if (!bVar2 && bVar1 == bVar3) {
    fVar28 = DAT_0000d230;
  }
  fVar29 = fVar28;
  if (bVar2 || bVar1 != bVar3) {
    fVar29 = param_5[0x4f];
  }
  param_5[0x4f] = param_4 + fVar29;
  fVar30 = param_5[0x4a] + 1.0f;
  fVar29 = local_150[(int)param_5[0x5d5] + -1];
  iVar18 = (int)param_5[0x4a];
  if (bVar2 || bVar1 != bVar3) {
    fVar28 = param_5[0x4e];
  }
  fVar43 = fVar29 - param_5[0x4d];
  param_5[0x4b] = param_2;
  param_5[0x4c] = fVar41;
  param_5[0x4d] = fVar29;
  param_5[0x4e] = fVar43 + fVar28;
  param_5[iVar18 + 0x17] = fVar43;
  param_5[iVar18 + 0x30] = param_4;
  bVar1 = fVar30 < 25.0f == NAN(fVar30);
  param_5[0x4a] = (fVar30 != 25.0f && bVar1) ? 1.0f : fVar30;
  param_8[2] = fVar37;
  param_8[3] = fVar41;
  *param_8 = local_23c[0];
  param_8[1] = local_23c[6];
  return;
}
