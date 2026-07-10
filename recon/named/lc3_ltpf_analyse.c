/* named: lc3_ltpf_analyse */
/* Reconstructed lc3_ltpf_analyse @ 0x6ab80  (parity: 60/60 trials, PROVEN) */
#include <stdint.h>
#pragma GCC diagnostic warning "-Wint-conversion"
#pragma GCC diagnostic warning "-Wimplicit-int"
#pragma GCC diagnostic warning "-Wimplicit-function-declaration"
#pragma GCC diagnostic warning "-Wint-to-pointer-cast"
#pragma GCC diagnostic warning "-Wpointer-to-int-cast"
#pragma GCC diagnostic warning "-Wincompatible-pointer-types"
#pragma GCC diagnostic warning "-Wdiscarded-qualifiers"
typedef uint8_t undefined1; typedef uint8_t byte; typedef uint8_t undefined; typedef uint8_t uchar;
typedef uint16_t undefined2; typedef uint16_t ushort; typedef uint16_t wchar_t;
typedef uint32_t undefined4; typedef uint32_t uint;
typedef long long code(int,...);
typedef uint64_t undefined8; typedef uint64_t ulonglong;
typedef int64_t longlong; typedef int32_t int32; typedef unsigned int uint3;
static inline int CARRY4(uint a, uint b){return (a+b)<a;}
static inline int CARRY1(uint a, uint b){return ((a&0xff)+(b&0xff))>0xff;}
static inline int CARRY2(uint a, uint b){return ((a&0xffff)+(b&0xffff))>0xffff;}
static inline int SBORROW4(int a,int b){int r=(int)((uint)a-(uint)b);return (((a^b)&(a^r))<0);}
static inline int SBORROW1(int a,int b){signed char r=(signed char)(a-b);return ((((signed char)a^(signed char)b)&((signed char)a^r))<0);}
static inline int SBORROW2(int a,int b){short r=(short)(a-b);return ((((short)a^(short)b)&((short)a^r))<0);}
#define CONCAT11(a,b) ((ushort)(((ushort)(uint8_t)(a)<<8)|(uint8_t)(b)))
#define CONCAT22(a,b) ((uint)(((uint)(ushort)(a)<<16)|(ushort)(b)))
#define CONCAT44(a,b) ((ulonglong)(((ulonglong)(uint)(a)<<32)|(uint)(b)))
#define CONCAT13(a,b) ((uint)(((uint)(uint8_t)(a)<<24)|((uint)(b)&0xffffff)))
#define CONCAT31(a,b) ((uint)(((uint)(a)<<8)|(uint8_t)(b)))
#define CONCAT12(a,b) ((uint)(((uint)(uint8_t)(a)<<16)|(ushort)(b)))
#define CONCAT21(a,b) ((uint)(((uint)(ushort)(a)<<8)|(uint8_t)(b)))
#define CONCAT111(a,b,c) ((uint)(((uint)(uint8_t)(a)<<16)|((uint)(uint8_t)(b)<<8)|(uint8_t)(c)))
#define CONCAT411(a,b,c) ((ulonglong)(((ulonglong)(uint)(a)<<16)|((uint)(uint8_t)(b)<<8)|(uint8_t)(c)))
#define SUB84(x,o) ((uint)((ulonglong)(x)>>((o)*8)))
#define SUB82(x,o) ((ushort)((ulonglong)(x)>>((o)*8)))
#define SUB81(x,o) ((uint8_t)((ulonglong)(x)>>((o)*8)))
#define SUB41(x,o) ((uint8_t)((uint)(x)>>((o)*8)))
#define SUB42(x,o) ((ushort)((uint)(x)>>((o)*8)))
#define SUB21(x,o) ((uint8_t)((ushort)(x)>>((o)*8)))
#define SUBF(v,o,s) ((ulonglong)((ulonglong)(v)>>((o)*8)) & ((s)>=8?~0ULL:((1ULL<<((s)*8))-1)))
#define NAN (__builtin_nanf(""))
#define INFINITY (__builtin_inff())

extern long long FUN_00069468__impl(int, ...);
#define lc3_ltpf_interpolate(...) FUN_00069468__impl(0, ##__VA_ARGS__)
extern long long FUN_0006954c__impl(int, ...);
#define lc3_ltpf_resample(...) FUN_0006954c__impl(0, ##__VA_ARGS__)
extern long long FUN_000698d0__impl(int, ...);
#define FUN_000698d0(...) FUN_000698d0__impl(0, ##__VA_ARGS__)
extern long long FUN_00086c44__impl(int, ...);
#define memmove(...) FUN_00086c44__impl(0, ##__VA_ARGS__)
extern long long __builtin_isnan__impl(int, ...);
#define __builtin_isnan(...) __builtin_isnan__impl(0, ##__VA_ARGS__)
extern long long __builtin_sqrt__impl(int, ...);
#define __builtin_sqrt(...) __builtin_sqrt__impl(0, ##__VA_ARGS__)

#define DAT_0006acb4 (0x8c938UL)
#define DAT_0006acb8 (0x0UL)
#define DAT_0006acbc (0x0UL) /* unknown lit */
#define DAT_0006acc0 (0x0UL) /* unknown lit */
#define DAT_0006acc4 (0x0UL) /* unknown lit */
#define DAT_0006acc8 (0x0UL) /* unknown lit */
#define DAT_0006accc (0x0UL) /* unknown lit */
#define DAT_0006acd0 (0x0UL) /* unknown lit */
#define DAT_0006b32c (0xbdcccccdUL)
#define DAT_0006b330 (0x3b33ed5fUL)
#define DAT_0006b334 (0xbb3c6322UL)
#define DAT_0006b338 (0x3b96ada0UL)
#define DAT_0006b33c (0x3f5146f0UL)
#define DAT_0006b340 (0xbd9a8088UL)
#define DAT_0006b344 (0x3ea90db1UL)
#define DAT_0006b348 (0xbdd8c080UL)
#define DAT_0006b34c (0x3ceaf73aUL)
#define DAT_0006b350 (0xbb44b0a3UL)
#define DAT_0006b354 (0x3cf1b20fUL)
#define DAT_0006b358 (0x3f1a71acUL)
#define DAT_0006b35c (0xbe056eaeUL)
#define DAT_0006b360 (0x3f70a3d7UL)


/* WARNING: Type propagation algorithm not settling */

int lc3_ltpf_analyse(int param_1,int param_2,char *param_3,undefined4 param_4,char *param_5)

{
  bool bVar1;
  bool bVar2;
  short *psVar3;
  short *psVar4;
  short *psVar5;
  short sVar6;
  longlong lVar7;
  longlong lVar8;
  longlong lVar9;
  int iVar10;
  int iVar11;
  float *pfVar12;
  short *psVar13;
  undefined4 uVar14;
  float fVar15;
  char cVar16;
  int iVar17;
  undefined1 *puVar18;
  int iVar19;
  char *pcVar20;
  int iVar21;
  char *pcVar22;
  uint uVar23;
  int iVar24;
  undefined1 *puVar25;
  float fVar26;
  float fVar27;
  float fVar28;
  float fVar29;
  float fVar30;
  float fVar31;
  float fVar32;
  float fVar33;
  float fVar34;
  float fVar35;
  float fVar36;
  int aiStack_98 [2];
  undefined1 auStack_90 [4];
  undefined1 *local_8c;
  int local_88;
  undefined1 *local_84;
  float local_80;
  float local_7c [3];
  float afStack_70 [17];
  
  local_88 = param_1;
  if (param_1 == 0) {
    memmove(param_3 + 0x20,param_3 + 0xe0,0x240);
    pcVar22 = param_3 + 0x260;
    (**(code **)(DAT_0006acb4 + param_2 * 4))(param_3 + 0x10,param_4,pcVar22,0x60);
    local_7c[0] = 6.72623e-44;
    iVar10 = 0x60;
    local_84 = (undefined1 *)0xc0;
    iVar21 = 6;
    iVar19 = 0x104;
    iVar17 = -0x58;
    local_80 = 1.34525e-43;
  }
  else {
    memmove(param_3 + 0x20,param_3 + 0x120,0x200);
    pcVar22 = param_3 + 0x220;
    (**(code **)(DAT_0006acb4 + param_2 * 4))(param_3 + 0x10,param_4,pcVar22,0x80);
    iVar10 = 0x80;
    local_7c[0] = 8.96831e-44;
    iVar21 = 8;
    local_84 = (undefined1 *)0x100;
    iVar19 = 0xe4;
    iVar17 = -0x30;
    local_80 = 1.79366e-43;
  }
  pcVar22 = pcVar22 + iVar17;
  iVar10 = memmove(param_3 + 800,param_3 + 800 + iVar10,iVar19);
  psVar13 = (short *)(pcVar22 + -2);
  for (pcVar20 = (char *)(iVar10 + iVar19); pcVar20 < param_3 + 0x484; pcVar20 = pcVar20 + 2) {
    psVar3 = psVar13 + 1;
    psVar4 = psVar13 + -1;
    sVar6 = *psVar13;
    psVar5 = psVar13 + -2;
    psVar13 = psVar13 + 2;
    *(short *)pcVar20 =
         (short)((uint)(((int)*psVar5 + (int)*psVar13) * 0x1fa9 +
                       sVar6 * 0x482d + ((int)*psVar4 + (int)*psVar3) * 0x3c40) >> 0x10);
  }
  iVar10 = FUN_000698d0(param_3,(char *)(iVar10 + iVar19),local_7c[0],local_7c + 1);
  fVar35 = local_80;
  if (iVar10 == 0) {
    fVar35 = DAT_0006acb8;
    if (*param_3 == '\0') {
      cVar16 = '\0';
      uVar23 = 0;
    }
    else {
      cVar16 = '\0';
      uVar23 = 0;
    }
    goto LAB_0006ac4e;
  }
  iVar17 = ((int)local_7c[1] + -2) * 2;
  local_7c[0] = (float)iVar17;
  if (iVar17 < 0x20) {
    local_7c[0] = 4.48416e-44;
  }
  iVar24 = iVar17 + 8;
  iVar19 = (int)local_7c[0];
  if (iVar24 < 0xe5) {
    iVar19 = iVar24 - (int)local_7c[0];
  }
  if (iVar24 != 0xe4 && iVar17 + -0xdc < 0 == SBORROW4(iVar24,0xe4)) {
    iVar19 = 0xe4 - iVar19;
  }
  iVar17 = -(int)local_84;
  iVar24 = (int)local_84 * -2;
  iVar11 = 4 - (int)local_7c[0];
  local_8c = auStack_90 + iVar24;
  local_84 = (undefined1 *)aiStack_98;
  *(int *)((int)aiStack_98 + iVar24) = iVar19 + 9;
  lc3_ltpf_resample(pcVar22,pcVar22 + iVar11 * 2,fVar35,local_7c + 2);
  fVar35 = local_80;
  if (iVar19 < 1) {
    iVar19 = 0x10;
  }
  else {
    iVar24 = 0;
    iVar11 = 1;
    pfVar12 = afStack_70 + 4;
    do {
      fVar33 = *pfVar12;
      pfVar12 = pfVar12 + 1;
      bVar1 = fVar33 != afStack_70[3];
      if (bVar1 && fVar33 < afStack_70[3] == (__builtin_isnan(fVar33) || __builtin_isnan(afStack_70[3]))) {
        iVar24 = iVar11;
      }
      iVar11 = iVar11 + 1;
      bVar2 = fVar33 < afStack_70[3] == (__builtin_isnan(fVar33) || __builtin_isnan(afStack_70[3]));
      afStack_70[3] =
           (float)((uint)(bVar1 && bVar2) * (int)fVar33 +
                  (uint)(!bVar1 || !bVar2) * (int)afStack_70[3]);
    } while (iVar19 + 1 != iVar11);
    local_7c[0] = (float)((int)local_7c[0] + iVar24);
    iVar19 = (iVar24 + 4) * 4;
  }
  fVar28 = *(float *)((int)local_7c + iVar19);
  fVar27 = *(float *)((int)&local_80 + iVar19);
  fVar29 = *(float *)((int)local_7c + iVar19 + 4U);
  fVar33 = *(float *)((int)afStack_70 + iVar19 + -4);
  fVar30 = *(float *)((int)afStack_70 + iVar19);
  fVar31 = *(float *)((int)afStack_70 + iVar19 + 4);
  fVar32 = *(float *)((int)afStack_70 + iVar19 + 8);
  fVar34 = fVar28 * DAT_0006acbc + fVar27 * DAT_0006acc0 + fVar29 * DAT_0006acc4 +
           fVar33 * DAT_0006acc8 + fVar30 * DAT_0006acc4 + fVar31 * DAT_0006acbc +
           fVar32 * DAT_0006acc0;
  if ((int)local_7c[0] < 0x7f) {
    fVar26 = *(float *)((int)afStack_70 + iVar19 + 0xc);
    fVar36 = fVar27 * DAT_0006b330 + fVar26 * DAT_0006b334 + fVar28 * DAT_0006b338 +
             fVar29 * DAT_0006b340 + fVar33 * DAT_0006b33c + fVar30 * DAT_0006b344 +
             fVar31 * DAT_0006b348 + fVar32 * DAT_0006b34c;
    iVar24 = (uint)(fVar34 < fVar36) << 0x1f;
    fVar15 = local_7c[0];
    if (-1 < iVar24) {
      fVar15 = 0.0;
      fVar36 = fVar34;
    }
    if (iVar24 < 0) {
      fVar15 = 1.4013e-45;
    }
    if ((local_7c[0] != 4.48416e-44) &&
       (fVar34 = fVar33 * DAT_0006b33c + *(float *)((int)&local_84 + iVar19) * DAT_0006b334 +
                 fVar27 * DAT_0006b34c + fVar28 * DAT_0006b348 + fVar29 * DAT_0006b344 +
                 fVar30 * DAT_0006b340 + fVar31 * DAT_0006b338 + fVar32 * DAT_0006b330,
       fVar34 != fVar36 && fVar34 < fVar36 == (__builtin_isnan(fVar34) || __builtin_isnan(fVar36)))) {
      fVar15 = -NAN;
      fVar36 = fVar34;
    }
LAB_0006b168:
    fVar34 = (fVar27 + fVar26) * DAT_0006b350 + fVar28 * DAT_0006b354 + fVar29 * DAT_0006b35c +
             fVar33 * DAT_0006b358 + fVar30 * DAT_0006b358 + fVar31 * DAT_0006b35c +
             fVar32 * DAT_0006b354;
    iVar24 = (uint)(fVar36 < fVar34) << 0x1f;
    if (-1 < iVar24) {
      fVar34 = fVar36;
    }
    if (iVar24 < 0) {
      fVar15 = 2.8026e-45;
    }
    if (local_7c[0] == 4.48416e-44) {
LAB_0006b21c:
      fVar36 = fVar27 * DAT_0006b334 + fVar26 * DAT_0006b330 + fVar28 * DAT_0006b34c +
               fVar29 * DAT_0006b348 + fVar33 * DAT_0006b344 + fVar30 * DAT_0006b33c +
               fVar31 * DAT_0006b340 + fVar32 * DAT_0006b338;
      iVar24 = (uint)(fVar34 < fVar36) << 0x1f;
      if (-1 < iVar24) {
        fVar36 = fVar34;
      }
      if (iVar24 < 0) {
        fVar15 = 4.2039e-45;
      }
      if ((local_7c[0] != 4.48416e-44) &&
         ((int)((uint)(fVar36 < fVar33 * DAT_0006b344 +
                                *(float *)((int)&local_84 + iVar19) * DAT_0006b330 +
                                fVar27 * DAT_0006b338 + fVar28 * DAT_0006b340 +
                                fVar29 * DAT_0006b33c + fVar30 * DAT_0006b348 +
                                fVar31 * DAT_0006b34c + fVar32 * DAT_0006b334) << 0x1f) < 0)) {
        fVar15 = -NAN;
      }
    }
    else {
      fVar36 = fVar33 * DAT_0006b358 + *(float *)((int)&local_84 + iVar19) * DAT_0006b350 +
               fVar27 * DAT_0006b354 + fVar28 * DAT_0006b35c + fVar29 * DAT_0006b358 +
               fVar30 * DAT_0006b35c + fVar31 * DAT_0006b354 + fVar32 * DAT_0006b350;
      if (fVar36 != fVar34 && fVar36 < fVar34 == (__builtin_isnan(fVar36) || __builtin_isnan(fVar34))) {
        fVar15 = -NAN;
        fVar34 = fVar36;
      }
      if ((int)local_7c[0] < 0x7f) goto LAB_0006b21c;
    }
    local_7c[0] = (float)((int)local_7c[0] + ((int)fVar15 >> 0x1f));
    iVar19 = ((int)fVar15 >> 0x1d & 4U) + (int)fVar15;
    uVar23 = iVar19 + (int)local_7c[0] * 4;
    if ((int)local_7c[0] < 0x7f) {
      iVar19 = uVar23 - 0x80;
    }
    else {
      if (0x9c < (int)local_7c[0]) goto LAB_0006adce;
      iVar19 = (iVar19 >> 1) + (int)local_7c[0] * 2 + 0x7e;
    }
  }
  else {
    if ((int)local_7c[0] < 0x9d) {
      fVar26 = *(float *)((int)afStack_70 + iVar19 + 0xc);
      fVar15 = 0.0;
      fVar36 = fVar34;
      goto LAB_0006b168;
    }
    uVar23 = (int)local_7c[0] << 2;
LAB_0006adce:
    iVar19 = (int)local_7c[0] + 0x11b;
  }
  *(int *)(param_5 + 4) = iVar19;
  lc3_ltpf_interpolate(pcVar22,local_80,0,auStack_90 + iVar17);
  puVar18 = local_8c;
  lc3_ltpf_interpolate(pcVar22 + ((int)uVar23 >> 2) * -2,fVar35,uVar23 & 3,local_8c);
  iVar17 = (int)afStack_70 + iVar17;
  iVar24 = 0;
  lVar7 = 0;
  iVar19 = iVar17;
  puVar25 = puVar18 + 0x20;
  do {
    iVar24 = iVar24 + 1;
    lVar7 = (longlong)((int)*(short *)(iVar19 + -2) * (int)*(short *)(puVar25 + -2)) +
            (longlong)((int)*(short *)(iVar19 + -4) * (int)*(short *)(puVar25 + -4)) +
            (longlong)((int)*(short *)(iVar19 + -6) * (int)*(short *)(puVar25 + -6)) +
            (longlong)((int)*(short *)(iVar19 + -8) * (int)*(short *)(puVar25 + -8)) +
            (longlong)((int)*(short *)(iVar19 + -10) * (int)*(short *)(puVar25 + -10)) +
            (longlong)((int)*(short *)(iVar19 + -0xc) * (int)*(short *)(puVar25 + -0xc)) +
            (longlong)((int)*(short *)(iVar19 + -0xe) * (int)*(short *)(puVar25 + -0xe)) +
            (longlong)((int)*(short *)(iVar19 + -0x10) * (int)*(short *)(puVar25 + -0x10)) +
            (longlong)((int)*(short *)(iVar19 + -0x12) * (int)*(short *)(puVar25 + -0x12)) +
            (longlong)((int)*(short *)(iVar19 + -0x14) * (int)*(short *)(puVar25 + -0x14)) +
            (longlong)((int)*(short *)(iVar19 + -0x16) * (int)*(short *)(puVar25 + -0x16)) +
            (longlong)((int)*(short *)(iVar19 + -0x18) * (int)*(short *)(puVar25 + -0x18)) +
            (longlong)((int)*(short *)(iVar19 + -0x1a) * (int)*(short *)(puVar25 + -0x1a)) +
            (longlong)((int)*(short *)(iVar19 + -0x1c) * (int)*(short *)(puVar25 + -0x1c)) +
            (longlong)((int)*(short *)(iVar19 + -0x1e) * (int)*(short *)(puVar25 + -0x1e)) +
            (int)*(short *)(iVar19 + -0x20) * (int)*(short *)(puVar25 + -0x20) + lVar7;
    iVar19 = iVar19 + 0x20;
    puVar25 = puVar25 + 0x20;
  } while (iVar24 < iVar21);
  iVar19 = 0;
  lVar8 = 0;
  do {
    iVar19 = iVar19 + 1;
    lVar8 = (longlong)((int)*(short *)(iVar17 + -2) * (int)*(short *)(iVar17 + -2)) +
            (longlong)((int)*(short *)(iVar17 + -4) * (int)*(short *)(iVar17 + -4)) +
            (longlong)((int)*(short *)(iVar17 + -6) * (int)*(short *)(iVar17 + -6)) +
            (longlong)((int)*(short *)(iVar17 + -8) * (int)*(short *)(iVar17 + -8)) +
            (longlong)((int)*(short *)(iVar17 + -10) * (int)*(short *)(iVar17 + -10)) +
            (longlong)((int)*(short *)(iVar17 + -0xc) * (int)*(short *)(iVar17 + -0xc)) +
            (longlong)((int)*(short *)(iVar17 + -0xe) * (int)*(short *)(iVar17 + -0xe)) +
            (longlong)((int)*(short *)(iVar17 + -0x10) * (int)*(short *)(iVar17 + -0x10)) +
            (longlong)((int)*(short *)(iVar17 + -0x12) * (int)*(short *)(iVar17 + -0x12)) +
            (longlong)((int)*(short *)(iVar17 + -0x14) * (int)*(short *)(iVar17 + -0x14)) +
            (longlong)((int)*(short *)(iVar17 + -0x16) * (int)*(short *)(iVar17 + -0x16)) +
            (longlong)((int)*(short *)(iVar17 + -0x18) * (int)*(short *)(iVar17 + -0x18)) +
            (longlong)((int)*(short *)(iVar17 + -0x1a) * (int)*(short *)(iVar17 + -0x1a)) +
            (longlong)((int)*(short *)(iVar17 + -0x1c) * (int)*(short *)(iVar17 + -0x1c)) +
            (longlong)((int)*(short *)(iVar17 + -0x1e) * (int)*(short *)(iVar17 + -0x1e)) +
            (int)*(short *)(iVar17 + -0x20) * (int)*(short *)(iVar17 + -0x20) + lVar8;
    iVar17 = iVar17 + 0x20;
  } while (iVar19 < iVar21);
  iVar17 = 0;
  lVar9 = 0;
  puVar18 = puVar18 + 0x20;
  do {
    iVar17 = iVar17 + 1;
    lVar9 = (longlong)((int)*(short *)(puVar18 + -2) * (int)*(short *)(puVar18 + -2)) +
            (longlong)((int)*(short *)(puVar18 + -4) * (int)*(short *)(puVar18 + -4)) +
            (longlong)((int)*(short *)(puVar18 + -6) * (int)*(short *)(puVar18 + -6)) +
            (longlong)((int)*(short *)(puVar18 + -8) * (int)*(short *)(puVar18 + -8)) +
            (longlong)((int)*(short *)(puVar18 + -10) * (int)*(short *)(puVar18 + -10)) +
            (longlong)((int)*(short *)(puVar18 + -0xc) * (int)*(short *)(puVar18 + -0xc)) +
            (longlong)((int)*(short *)(puVar18 + -0xe) * (int)*(short *)(puVar18 + -0xe)) +
            (longlong)((int)*(short *)(puVar18 + -0x10) * (int)*(short *)(puVar18 + -0x10)) +
            (longlong)((int)*(short *)(puVar18 + -0x12) * (int)*(short *)(puVar18 + -0x12)) +
            (longlong)((int)*(short *)(puVar18 + -0x14) * (int)*(short *)(puVar18 + -0x14)) +
            (longlong)((int)*(short *)(puVar18 + -0x16) * (int)*(short *)(puVar18 + -0x16)) +
            (longlong)((int)*(short *)(puVar18 + -0x18) * (int)*(short *)(puVar18 + -0x18)) +
            (longlong)((int)*(short *)(puVar18 + -0x1a) * (int)*(short *)(puVar18 + -0x1a)) +
            (longlong)((int)*(short *)(puVar18 + -0x1c) * (int)*(short *)(puVar18 + -0x1c)) +
            (longlong)((int)*(short *)(puVar18 + -0x1e) * (int)*(short *)(puVar18 + -0x1e)) +
            (int)*(short *)(puVar18 + -0x20) * (int)*(short *)(puVar18 + -0x20) + lVar9;
    puVar18 = puVar18 + 0x20;
  } while (iVar17 < iVar21);
  cVar16 = *param_3;
  fVar35 = (float)(longlong)
                  (int)((uint)(lVar7 + 0x20) >> 6 |
                       (int)((ulonglong)(lVar7 + 0x20) >> 0x20) * 0x4000000) /
           __builtin_sqrt((float)(longlong)
                       (int)((uint)(lVar9 + 0x20) >> 6 |
                            (int)((ulonglong)(lVar9 + 0x20) >> 0x20) * 0x4000000) *
                (float)(longlong)
                       (int)((uint)(lVar8 + 0x20) >> 6 |
                            (int)((ulonglong)(lVar8 + 0x20) >> 0x20) * 0x4000000));
  if (cVar16 == '\0') {
    if (((local_88 == 1) ||
        (fVar33 = *(float *)(param_3 + 0xc),
        fVar33 != DAT_0006b360 && fVar33 < DAT_0006b360 == (__builtin_isnan(fVar33) || __builtin_isnan(DAT_0006b360)))) &&
       (fVar33 = *(float *)(param_3 + 8),
       fVar33 != DAT_0006b360 && fVar33 < DAT_0006b360 == (__builtin_isnan(fVar33) || __builtin_isnan(DAT_0006b360)))) {
      cVar16 = fVar35 != DAT_0006b360 && fVar35 < DAT_0006b360 == (__builtin_isnan(fVar35) || __builtin_isnan(DAT_0006b360))
      ;
    }
  }
  else if (fVar35 == DAT_0006accc || fVar35 < DAT_0006accc != (__builtin_isnan(fVar35) || __builtin_isnan(DAT_0006accc))) {
    if (fVar35 != DAT_0006acd0 && fVar35 < DAT_0006acd0 == (__builtin_isnan(fVar35) || __builtin_isnan(DAT_0006acd0))) {
      iVar17 = *(int *)(param_3 + 4);
      if (iVar17 < (int)uVar23) {
        iVar17 = uVar23 - iVar17;
      }
      else {
        iVar17 = iVar17 - uVar23;
      }
      if (iVar17 < 8) {
        fVar33 = fVar35 - *(float *)(param_3 + 8);
        cVar16 = fVar33 != DAT_0006b32c &&
                 fVar33 < DAT_0006b32c == (__builtin_isnan(fVar33) || __builtin_isnan(DAT_0006b32c));
        goto LAB_0006ac4e;
      }
    }
    cVar16 = '\0';
  }
LAB_0006ac4e:
  *param_5 = cVar16;
  uVar14 = *(undefined4 *)(param_3 + 8);
  *param_3 = cVar16;
  *(float *)(param_3 + 8) = fVar35;
  *(uint *)(param_3 + 4) = uVar23;
  *(undefined4 *)(param_3 + 0xc) = uVar14;
  return iVar10;
}


