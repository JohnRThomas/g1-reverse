/* readable reconstruction; identity: FUN_0006b3c8 @ 0x0006b3c8
 * public-name: FUN_0006b3c8
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_20002cb8                               @ 0x20002cb8
 *   g_20002cf4                               @ 0x20002cf4
 */
/* Google liblc3 mdct.c fft @ 0x6b3c8, exact owned extent 0x7f0. */
typedef unsigned int uint;
typedef unsigned long long ulonglong;
typedef long long longlong;

#define FB(u) (((union { uint i; float f; }){ .i = (uint)(u) }).f)
#define VST(p) (*(volatile float *)(p))

float * FUN_0006b3c8(int param_1, uint param_2, float *param_3, float *param_4)
{
  float *pfVar1;
  float *pfVar2;
  float *pfVar3;
  float *pfVar4;
  float **ppfVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float *pfVar11;
  float *pfVar12;
  float *pfVar13;
  int iVar14;
  float *pfVar15;
  int iVar16;
  int iVar17;
  float *pfVar18;
  int iVar19;
  int iVar20;
  float *pfVar21;
  int *piVar22;
  int iVar23;
  float *pfVar24;
  float *pfVar25;
  uint uVar26;
  float *pfVar27;
  float *pfVar28;
  float *pfVar29;
  float *pfVar30;
  float *pfVar31;
  uint uVar32;
  float *pfVar33;
  float fVar34;
  float fVar35;
  float fVar36;
  float fVar37;
  float fVar38;
  float fVar39;
  float fVar40;
  float fVar41;
  float fVar42;
  float fVar43;
  float fVar44;
  float *local_a0;
  float *local_9c;
  float *local_98;
  float *local_94;
  uint local_90;
  int local_8c;
  int local_7c;
  uint local_78;
  float *local_60[3];

  fVar10 = FB(0xbf167918);
  fVar9 = FB(0xbf737871);
  fVar8 = FB(0x3f167918);
  fVar7 = FB(0xbf4f1bbd);
  fVar6 = FB(0x3e9e377a);
  fVar37 = FB(0x3f737871);
  local_60[0] = param_4;
  local_60[1] = param_3;
  local_90 = (uint)((ulonglong)0xcccccccdULL * (ulonglong)param_2 >> 0x22);
  pfVar11 = (float *)(param_1 + local_90 * 8);
  pfVar25 = pfVar11 + local_90 * 6;
  pfVar28 = pfVar25 + local_90 * -4;
  pfVar30 = pfVar28 + local_90 * 2;
  pfVar12 = param_4 + 10;
  iVar20 = param_1 + 8;
  do {
    float f38 = *pfVar11 + *pfVar25;
    float f44 = *pfVar28 + *pfVar30;
    float f40 = *pfVar28 - *pfVar30;
    float f36 = pfVar11[1] + pfVar25[1];
    float f41 = pfVar11[1] - pfVar25[1];
    float f43 = pfVar28[1] + pfVar30[1];
    float f42 = *pfVar11 - *pfVar25;
    float f39 = pfVar28[1] - pfVar30[1];
    /* separately-rounded reused products (original emits distinct vmul) */
    float m34  = f41 * fVar37;
    float m41x = f41 * fVar8;
    float m35  = f42 * fVar9;
    float m42x = f42 * fVar10;
    float p447 = f44 * fVar7;
    float p446 = f44 * fVar6;
    float p437 = f43 * fVar7;
    float p436 = f43 * fVar6;
    float g0 = *(float *)(iVar20 + -8);
    float g1 = *(float *)(iVar20 + -4);
    /* fused (single-rounding fma) intermediates */
    float s25  = __builtin_fmaf(f38, fVar6, m34);
    float s23  = __builtin_fmaf(f36, fVar6, m35);
    float s20  = __builtin_fmaf(f38, fVar7, m41x);
    float s19  = __builtin_fmaf(f36, fVar7, m42x);
    float s16  = __builtin_fmaf(f38, fVar6, p447);
    float s1x  = __builtin_fmaf(f36, fVar6, p437);
    float s10b = __builtin_fmaf(f38, fVar7, p446);
    float s11b = __builtin_fmaf(f36, fVar7, p436);
    iVar19 = iVar20 + 8;
    VST(pfVar12 - 10) = g0 + (f38 + f44);
    VST(pfVar12 - 9) = g1 + (f36 + f43);
    VST(pfVar12 - 8) = __builtin_fmaf(f39, fVar8, (g0 + s25) + p447);
    VST(pfVar12 - 7) = __builtin_fmaf(f40, fVar10, (g1 + s23) + p437);
    VST(pfVar12 - 6) = __builtin_fmaf(f39, fVar9, (g0 + s20) + p446);
    VST(pfVar12 - 5) = __builtin_fmaf(f40, fVar37, (g1 + s19) + p436);
    VST(pfVar12 - 4) = __builtin_fmaf(-f39, fVar9, (s10b + g0) - m41x);
    VST(pfVar12 - 3) = __builtin_fmaf(-f40, fVar37, (s11b + g1) - m42x);
    VST(pfVar12 - 2) = __builtin_fmaf(-f39, fVar8, (g0 + s16) - m34);
    pfVar11 = pfVar11 + 2;
    pfVar25 = pfVar25 + 2;
    pfVar28 = pfVar28 + 2;
    pfVar30 = pfVar30 + 2;
    VST(pfVar12 - 1) = __builtin_fmaf(-f40, fVar10, (g1 + s1x) - m35);
    pfVar12 = pfVar12 + 10;
    iVar20 = iVar19;
  } while (param_1 + 8 + local_90 * 8 != iVar19);
  if ((local_90 - 1 & local_90) == 0) {
    local_7c = 0;
    local_78 = 0;
  }
  else {
    local_7c = 0;
    uVar32 = local_90;
    pfVar12 = param_3;
    param_3 = param_4;
    uVar26 = 0;
    piVar22 = (int *)0x20002cf4;
    while( 1 ) {
      param_4 = pfVar12;
      local_78 = uVar26 ^ 1;
      iVar20 = *(int *)*piVar22;
      local_90 = (int)((ulonglong)((longlong)(int)0x55555556 * (longlong)(int)uVar32) >> 0x20) -
                 ((int)uVar32 >> 0x1f);
      pfVar12 = (float *)((int *)*piVar22)[1];
      local_a0 = param_3 + iVar20 * local_90 * 2;
      pfVar11 = pfVar12 + iVar20 * 4;
      local_9c = param_3 + iVar20 * local_90 * 4;
      pfVar25 = param_4 + iVar20 * 2;
      pfVar28 = param_4 + iVar20 * 4;
      if ((2 < (int)uVar32) && (0 < iVar20)) {
        pfVar30 = param_3 + 2;
        local_8c = 0;
        local_98 = param_4;
        local_94 = param_3;
        do {
          pfVar30 = pfVar30 + iVar20 * 2;
          pfVar27 = local_94 + 2;
          pfVar13 = pfVar11;
          pfVar15 = pfVar11 + iVar20 * 4;
          pfVar24 = pfVar12;
          pfVar29 = pfVar28;
          pfVar31 = pfVar25;
          pfVar33 = local_98;
          pfVar18 = local_a0;
          pfVar21 = local_9c;
          do {
            float a0 = *pfVar18, a1 = pfVar18[1];
            float b0 = *pfVar21, b1 = pfVar21[1];
            float c2 = pfVar27[-2], c1 = pfVar27[-1];
            float u0 = pfVar24[0], u1 = pfVar24[1], u2 = pfVar24[2], u3 = pfVar24[3];
            float v0 = pfVar13[0], v1 = pfVar13[1], v2 = pfVar13[2], v3 = pfVar13[3];
            float w0 = pfVar15[0], w1 = pfVar15[1], w2 = pfVar15[2], w3 = pfVar15[3];
            VST(pfVar33) = __builtin_fmaf(-b1, u3,
                             __builtin_fmaf(-a1, u1, c2 + __builtin_fmaf(a0, u0, b0 * u2)));
            VST(pfVar33 + 1) = __builtin_fmaf(b0, u3,
                             __builtin_fmaf(b1, u2, c1 + __builtin_fmaf(a1, u0, a0 * u1)));
            VST(pfVar31) = __builtin_fmaf(-b1, v3,
                             __builtin_fmaf(-a1, v1, c2 + __builtin_fmaf(a0, v0, b0 * v2)));
            VST(pfVar31 + 1) = __builtin_fmaf(b0, v3,
                             __builtin_fmaf(b1, v2, c1 + __builtin_fmaf(a1, v0, a0 * v1)));
            VST(pfVar29) = __builtin_fmaf(-b1, w3,
                             __builtin_fmaf(-a1, w1, c2 + __builtin_fmaf(a0, w0, b0 * w2)));
            pfVar27 = pfVar27 + 2;
            pfVar13 = pfVar13 + 4;
            pfVar15 = pfVar15 + 4;
            pfVar24 = pfVar24 + 4;
            pfVar33 = pfVar33 + 2;
            pfVar31 = pfVar31 + 2;
            VST(pfVar29 + 1) = __builtin_fmaf(b0, w3,
                             __builtin_fmaf(b1, w2, c1 + __builtin_fmaf(a1, w0, a0 * w1)));
            pfVar29 = pfVar29 + 2;
            pfVar18 = pfVar18 + 2;
            pfVar21 = pfVar21 + 2;
          } while (pfVar30 != pfVar27);
          local_94 = local_94 + iVar20 * 2;
          local_8c = local_8c + 1;
          local_a0 = local_a0 + iVar20 * 2;
          local_9c = local_9c + iVar20 * 2;
          pfVar25 = pfVar25 + iVar20 * 6;
          local_98 = local_98 + iVar20 * 6;
          pfVar28 = pfVar28 + iVar20 * 6;
        } while (local_8c < (int)local_90);
      }
      local_7c = local_7c + 1;
      if ((local_90 - 1 & local_90) == 0) break;
      uVar32 = local_90;
      pfVar12 = local_60[uVar26];
      param_3 = param_4;
      uVar26 = local_78;
      piVar22 = piVar22 + 1;
    }
    if ((int)uVar32 < 6) {
      return param_4;
    }
  }
  iVar20 = 0;
  iVar19 = 0x20002cb8 + local_7c * 4;
  while( 1 ) {
    pfVar12 = param_3;
    piVar22 = *(int **)(iVar19 + iVar20 * 4);
    local_90 = (int)local_90 >> 1;
    iVar17 = *piVar22;
    iVar23 = piVar22[1];
    pfVar25 = pfVar12 + iVar17 * 2;
    pfVar11 = param_4 + iVar17 * local_90 * 2;
    if (0 < iVar17) {
      uVar32 = 0;
      pfVar18 = param_4 + 2;
      pfVar30 = pfVar12;
      pfVar28 = pfVar18;
      while( 1 ) {
        pfVar28 = pfVar28 + iVar17 * 2;
        iVar14 = iVar23;
        iVar16 = iVar23 + 4;
        pfVar15 = pfVar25;
        pfVar24 = pfVar30;
        pfVar13 = pfVar11;
        do {
          float pr = *pfVar13;
          float pi = pfVar13[1];
          float wr = *(float *)(iVar16 + -4);
          float wi = *(float *)(iVar14 + 4);
          float are = pfVar18[-2];
          float aim = pfVar18[-1];
          float pwi = pr * wi;              /* separate rounded vmul */
          float t2 = __builtin_fmaf(pi, wr, pwi);
          VST(pfVar24) = __builtin_fmaf(-pi, wi, __builtin_fmaf(pr, wr, are));
          VST(pfVar24 + 1) = aim + t2;
          VST(pfVar15) = __builtin_fmaf(-pr, wr, __builtin_fmaf(pi, wi, are));
          pfVar33 = (float *)(iVar14 + 4);
          pfVar29 = (float *)(iVar16 + -4);
          pfVar31 = pfVar18 + -1;
          pfVar18 = pfVar18 + 2;
          iVar14 = iVar14 + 8;
          iVar16 = iVar16 + 8;
          pfVar24 = pfVar24 + 2;
          VST(pfVar15 + 1) = aim - t2;
          pfVar15 = pfVar15 + 2;
          pfVar13 = pfVar13 + 2;
        } while (pfVar28 != pfVar18);
        uVar32 = uVar32 + 1;
        param_4 = param_4 + iVar17 * 2;
        pfVar11 = pfVar11 + iVar17 * 2;
        pfVar30 = pfVar30 + iVar17 * 4;
        pfVar25 = pfVar25 + iVar17 * 4;
        if (local_90 == uVar32) break;
        pfVar18 = param_4 + 2;
      }
    }
    iVar20 = iVar20 + 3;
    if (local_90 == 1) break;
    ppfVar5 = local_60 + local_78;
    local_78 = local_78 ^ 1;
    param_3 = *ppfVar5;
    param_4 = pfVar12;
  }
  return pfVar12;
}
