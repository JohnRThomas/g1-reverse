/* Full reconstruction fuel_gauge_update @ 0x10b18. */
#include <stdint.h>
#include <stdbool.h>
typedef uint8_t undefined1; typedef uint16_t undefined2;
typedef uint32_t undefined4; typedef uint64_t undefined8;
typedef uint8_t byte; typedef int64_t longlong; typedef uint64_t ulonglong; typedef uint32_t uint;
#define NAN(x) __builtin_isnan((x))
#define DAT_00010be4 0.0f
#define DAT_00010be8 1000.0f
#define DAT_00010bec ((int64_t *)0x20004790u)
#define DAT_00010bf0 0x000a3d37u
#define DAT_00010bf4 100.0f
#define DAT_00010f40 0xd2f1a9fcu
#define DAT_00010f44 0x3fc0624du
#define DAT_00010f48 ((int *)0x2000230cu)
#define DAT_00010f4c ((int *)0x20007554u)
#define DAT_00010f50 0x000a3e08u
#define DAT_00010f54 0x000a3d62u
#define DAT_00010f58 100.0f
#define DAT_00010f5c ((int *)0x20007b70u)
#define DAT_00010f60 ((float *)0x20007b74u)
#define DAT_00010f64 0x000a3d83u
#define DAT_00010f68 150.0f
#define DAT_00010f6c 93.5f
#define DAT_00010f70 94.0f
#define DAT_00010f74 94.5f
#define DAT_00010f78 95.0f
#define DAT_00010f7c 200.0f
#define DAT_00010f80 ((uint8_t *)0x20018da2u)
#define DAT_00010f84 0x408f4000u
#define DAT_00010f88 1000.0f
#define DAT_00010f8c 60.0f
#define DAT_00010f90 120.0f
#define DAT_00010f94 (-50.0f)
#define DAT_00010f98 0x000a3daeu
#define DAT_00010f9c 0x0001d4bfu
#define DAT_00010fa0 ((uint8_t *)0x20018d90u)
#define DAT_00010fa4 0.0f
extern uint32_t DEBUG_PRINT(uintptr_t,...);
extern uint64_t FUN_0000d58c(uint32_t,...); extern uint64_t FUN_0000d848(float);
extern uint64_t FUN_0000d8f8(uint32_t,...); extern uint8_t FUN_0000dea8(uint32_t,...);
/* ITERATION 39 DEFECT FIX (2 of 2) -- the 64-bit->float conversion had BOTH
 * its argument and its return register wrong.  Shipped:
 *     00010b7a  subs r0, r0, r2       ; lVar16 low
 *     00010b7c  sbc.w r1, r1, r3      ; lVar16 high
 *     00010b80  cmp.w r0, #0x3e8
 *     00010b84  sbcs r3, r1, #0       ; signed 64-bit  lVar16 < 1000
 *     00010b88  blt.w #0x10fbe
 *     00010b8c  bl   #0xe128          ; __floatdisf(r0:r1)  == __aeabi_l2f
 *     00010b90  vldr s16, [sp, #0x18]
 *     00010b94  vmov s3, r0           ; <<< the RESULT COMES BACK IN r0
 *     00010b9e  vdiv.f32 s3, s3, s18  ; / 1000.0  -> seconds since last sample
 * The reconstruction called it with NO argument and declared it `float
 * __floatdisf(void)`.  Under the hard-float ABI the caller then read the
 * result out of s0, which __aeabi_l2f never writes, and Ghidra's r0-clobbering
 * comparison idiom meant r0:r1 no longer held lVar16 at the call either.
 * Measured consequence: the elapsed-time argument reaching
 * battery_model_state_update was 0.0 for every sample (the shipped run carries
 * 1.363, 1.257, 1.260 ... s), the EKF divided by it, its covariance block went
 * to NaN and the reported state of charge stuck at 0 -- which is the other
 * half of the `device_info[0xfc0] > 0x1d` gate failure of iteration 39.
 * `__floatdisf` is an alias of `__aeabi_l2f` (both at 0xced4 in our ELF), a
 * SOFT-float helper: it takes r0:r1 and returns raw float bits in r0, so the
 * declaration below uses the project's raw-bits convention (the same one
 * battery_model_state_update already uses for __extendsfdf2). */
extern uint32_t FUN_0000e128(int64_t); /* soft-float: r0:r1 in, raw float bits out in r0 */ extern float FUN_0000e340(float,float,float,float,uint32_t);
extern uint32_t FUN_000167a8(void); extern uint32_t FUN_00019c70(uintptr_t,...);
extern uint32_t FUN_000232b8(void); extern uint32_t FUN_00027448(uintptr_t,...);
extern int FUN_0002e988(uint32_t,float*,float*,float*); extern int FUN_00030cac(void);
extern void FUN_000330c4(void); extern void FUN_000330d8(void);
extern uint32_t FUN_00074844(uintptr_t,...); extern uint32_t FUN_0007cbfe(uintptr_t,...);
extern int64_t FUN_0007ceda(void); extern uint32_t FUN_0007cefc(void);
extern uint32_t send_event_status(uintptr_t,...); extern uint32_t sync_to_slave(uintptr_t,...);

int fuel_gauge_update(undefined4 param_1)

{
  bool bVar1;
  bool bVar2;
  float fVar3;
  longlong *plVar4;
  int *piVar5;
  byte *pbVar6;
  undefined1 uVar7;
  int iVar8;
  undefined4 uVar9;
  char *pcVar10;
  undefined4 uVar11;
  byte bVar12;
  int iVar13;
  float fVar14;
  float fVar15;
  longlong lVar16;
  undefined8 uVar17;
  undefined8 uVar18;
  undefined8 uVar19;
  float local_44;
  float local_40;
  float local_3c [2];

  plVar4 = DAT_00010bec;
  fVar3 = DAT_00010be8;
  iVar13 = 0xb;
  fVar15 = DAT_00010be4;
  while (iVar8 = FUN_00030cac(), iVar8 == 0) {
    FUN_000330c4();
    iVar8 = FUN_0002e988(param_1,&local_44,&local_40,local_3c);
    FUN_000330d8();
    if (iVar8 < 0) {
      DEBUG_PRINT(DAT_00010bf0);
      return iVar8;
    }
    lVar16 = FUN_0007ceda();
    lVar16 = lVar16 - *plVar4;
    if ((int)((ulonglong)lVar16 >> 0x20) < (int)(uint)((uint)lVar16 < 1000)) {
      return -1;
    }
    { union { uint32_t u; float f; } g1_l2f; g1_l2f.u = FUN_0000e128(lVar16);
      fVar15 = g1_l2f.f; }
    fVar14 = local_40;
    fVar15 = (float)FUN_0000e340(local_44,local_40,local_3c[0],fVar15 / fVar3,0);
    if ((((fVar14 != 0.0) || (iVar13 = iVar13 + -1, iVar13 == 0)) ||
        (-1 < (int)((uint)(fVar15 < DAT_00010bf4) << 0x1f))) ||
       (fVar15 == 0.0 || fVar15 < 0.0 != NAN(fVar15))) {
      lVar16 = FUN_0007ceda();
      *plVar4 = lVar16;
      goto LAB_00010c00;
    }
    FUN_00074844(0xa4,0);
  }
  if (fVar15 == 0.0 || fVar15 < 0.0 != NAN(fVar15)) {
    return 0;
  }
LAB_00010c00:
  piVar5 = DAT_00010f48;
  if (0 < *DAT_00010f48) {
    uVar17 = FUN_0000d848(local_44);
    uVar11 = (undefined4)((ulonglong)uVar17 >> 0x20);
    uVar18 = FUN_0000d848(local_40);
    uVar19 = FUN_0000d848(local_3c[0]);
    if (*DAT_00010f4c == 0) {
      DEBUG_PRINT(DAT_00010f54,DAT_00010f50,(int)uVar17,uVar11,(int)uVar18,
                  (int)((ulonglong)uVar18 >> 0x20),(int)uVar19,(int)((ulonglong)uVar19 >> 0x20));
    }
    else {
      FUN_00019c70(DAT_00010f54,DAT_00010f50,(int)uVar17,uVar11);
    }
  }
  iVar13 = FUN_0007ceda();
  fVar3 = DAT_00010f58;
  if (((fVar15 == 0.0) || (*DAT_00010f60 == fVar15)) &&
     (fVar15 < DAT_00010f58 != (NAN(fVar15) || NAN(DAT_00010f58)))) {
    if (DAT_00010f9c < (uint)(iVar13 - *DAT_00010f5c)) {
      *DAT_00010fa0 = 1;
    }
  }
  else {
    *DAT_00010f5c = iVar13;
    *DAT_00010f60 = fVar15;
  }
  iVar13 = FUN_0007cefc();
  fVar14 = fVar15;
  if (iVar13 != 0) {
    fVar14 = fVar15 * 1.25;
  }
  if (0 < *piVar5) {
    uVar17 = FUN_0000d848(fVar15);
    uVar11 = (undefined4)((ulonglong)uVar17 >> 0x20);
    uVar18 = FUN_0000d848(fVar14);
    if (*DAT_00010f4c == 0) {
      uVar9 = FUN_000232b8();
      DEBUG_PRINT(DAT_00010f64,DAT_00010f50,(int)uVar17,uVar11,(int)uVar18,
                  (int)((ulonglong)uVar18 >> 0x20),uVar9);
    }
    else {
      uVar9 = FUN_000232b8();
      FUN_00019c70(DAT_00010f64,DAT_00010f50,(int)uVar17,uVar11,uVar18,uVar9);
    }
  }
  fVar15 = DAT_00010fa4;
  if (((((int)((uint)(fVar14 < 0.0) << 0x1f) < 0) ||
       (fVar14 < DAT_00010f68 == (NAN(fVar14) || NAN(DAT_00010f68)))) ||
      (fVar15 = DAT_00010f58, fVar14 < fVar3 == (NAN(fVar14) || NAN(fVar3)))) ||
     (((fVar15 = fVar14, fVar14 < DAT_00010f6c != (NAN(fVar14) || NAN(DAT_00010f6c)) ||
       (-1 < (int)((uint)(fVar14 < DAT_00010f70) << 0x1f))) &&
      ((fVar14 < DAT_00010f74 != (NAN(fVar14) || NAN(DAT_00010f74)) ||
       (-1 < (int)((uint)(fVar14 < DAT_00010f78) << 0x1f))))))) {
    iVar13 = FUN_000167a8();
    uVar7 = 0;
  }
  else {
    iVar13 = FUN_000167a8();
    uVar7 = 1;
  }
  *(undefined1 *)(iVar13 + 0xfc2) = uVar7;
  iVar13 = FUN_000167a8();
  fVar14 = local_44 * fVar3 - DAT_00010f7c;
  *(char *)(iVar13 + 0xfc0) = (0.0 < fVar15) * (char)(int)fVar15;
  iVar13 = FUN_000167a8();
  pbVar6 = DAT_00010f80;
  *(char *)(iVar13 + 0xfc4) = (0.0 < fVar14) * (char)(int)fVar14;
  if (local_40 == 0.0) {
    bVar12 = *pbVar6 + 1;
    if (5 < bVar12) {
      *pbVar6 = 0;
      uVar17 = FUN_0000d848(local_40);
      uVar17 = FUN_0000d58c((int)uVar17,(int)((ulonglong)uVar17 >> 0x20),DAT_00010f40,DAT_00010f44);
      uVar17 = FUN_0000d8f8((int)uVar17,(int)((ulonglong)uVar17 >> 0x20),0,DAT_00010f84);
      iVar13 = FUN_000167a8();
      uVar7 = FUN_0000dea8((int)uVar17,(int)((ulonglong)uVar17 >> 0x20));
      fVar15 = local_40 * DAT_00010f88;
      *(undefined1 *)(iVar13 + 0xfc5) = uVar7;
      iVar13 = FUN_000167a8();
      *(char *)(iVar13 + 0xfc8) = (char)(int)fVar15;
      goto LAB_00010dca;
    }
  }
  else {
    uVar17 = FUN_0000d848(local_40);
    uVar17 = FUN_0000d58c((int)uVar17,(int)((ulonglong)uVar17 >> 0x20),DAT_00010f40,DAT_00010f44);
    uVar17 = FUN_0000d8f8((int)uVar17,(int)((ulonglong)uVar17 >> 0x20),0,DAT_00010f84);
    iVar13 = FUN_000167a8();
    fVar15 = DAT_00010f88;
    uVar7 = FUN_0000dea8((int)uVar17,(int)((ulonglong)uVar17 >> 0x20));
    *(undefined1 *)(iVar13 + 0xfc5) = uVar7;
    iVar13 = FUN_000167a8();
    *(char *)(iVar13 + 0xfc8) = (char)(int)(local_40 * fVar15);
    bVar12 = 0;
  }
  *pbVar6 = bVar12;
LAB_00010dca:
  iVar13 = FUN_000167a8();
  *(char *)(iVar13 + 0xfc6) = (0.0 < local_3c[0]) * (char)(int)local_3c[0];
  iVar13 = FUN_000167a8();
  bVar1 = local_3c[0] < DAT_00010f8c;
  bVar2 = NAN(DAT_00010f8c);
  *(short *)(iVar13 + 0xfca) = (short)(int)(local_3c[0] * fVar3);
  if ((((bVar1 == (NAN(local_3c[0]) || bVar2)) &&
       ((int)((uint)(local_3c[0] < DAT_00010f90) << 0x1f) < 0)) ||
      ((local_3c[0] < DAT_00010f94 == (NAN(local_3c[0]) || NAN(DAT_00010f94)) &&
       (local_3c[0] <= -20.0)))) && (iVar13 = FUN_000167a8(), *(char *)(iVar13 + 0xfea) != '\f')) {
    send_event_status(4);
    pcVar10 = (char *)FUN_000167a8();
    if (*pcVar10 == '\x01') {
      uVar11 = FUN_000167a8();
      sync_to_slave(uVar11,4,0);
      uVar11 = FUN_000167a8();
      FUN_0007cbfe(uVar11,0);
    }
    else {
      uVar11 = FUN_000167a8();
      FUN_00027448(uVar11,7,0);
    }
    iVar13 = FUN_000167a8();
    *(undefined1 *)(iVar13 + 0xfea) = 0xc;
    uVar11 = FUN_000167a8();
    FUN_0007cbfe(uVar11,1);
    if (0 < *piVar5) {
      if (*DAT_00010f4c == 0) {
        DEBUG_PRINT(DAT_00010f98,DAT_00010f50);
      }
      else {
        FUN_00019c70(0);
      }
    }
  }
  return 0;
}
