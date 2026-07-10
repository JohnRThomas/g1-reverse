/* Reconstructed try_to_save_file @ 0x23634  (parity: 200/200 trials, PROVEN) */
typedef unsigned int uint;
typedef unsigned char byte;
typedef unsigned int undefined4;

extern void DEBUG_PRINT(undefined4 fmt, ...);
extern int FUN_000167a8(void);
extern void FUN_00019c70(void);
extern void FUN_00022834(uint a, uint b, ...);
extern void FUN_000235a4(void *a);
extern undefined4 FUN_0002360c(uint a, uint b, uint c);
extern void FUN_00086c04(void *dst, void *src, uint n);
extern void FUN_00086c1e(void *dst, void *src, uint n, uint m);
extern void update_persist_task_status(uint a, int b, int c);

void try_to_save_file(int param_1)
{
  const unsigned long BUF = 0x2007EF08UL;
  volatile byte *f4 = (volatile byte*)(BUF+4);
  volatile byte *f3 = (volatile byte*)(BUF+5);
  volatile byte *f2 = (volatile byte*)(BUF+6);
  volatile byte *f1 = (volatile byte*)(BUF+7);
  volatile byte *f0 = (volatile byte*)(BUF+8);
  volatile byte *l2c = (volatile byte*)(BUF+0xcc);

  volatile uint *DAT_818 = (volatile uint*)0x200079dcUL;
  volatile int  *DAT_81c = (volatile int*)0x200079d4UL;
  volatile uint *DAT_820 = (volatile uint*)0x200079d8UL;
  volatile undefined4 *DAT_828 = (volatile undefined4*)0x200079e0UL;
  volatile int *DAT_82c = (volatile int*)0x2000230cUL;
  volatile int *DAT_830 = (volatile int*)0x20007554UL;

  uint uVar8, uVar9, uVar10;
  int iVar6, iVar7;
  undefined4 uVar5;

  FUN_000235a4((void*)(BUF+4));
  uVar9 = (uint)(*l2c);

  if (uVar9 < 0x15 && *f4 == 0x0d && *f3 == 0x0e) {
    if (*DAT_81c == 0x1c0000 && 0x1fffff < (int)*DAT_818) {
      return;
    }
    if (*DAT_820 < 0x1000) {
      FUN_00022834(*DAT_818, 0x20017062u);
      uVar5 = FUN_0002360c(*DAT_828, 0x20017062u, *DAT_820);
      iVar7 = *DAT_82c;
      *DAT_828 = uVar5;
      if (iVar7 < 1) return;
      if (*DAT_830 != 0) { FUN_00019c70(); return; }
      DEBUG_PRINT(0x0009e88bu, 0x0009e8e5u, uVar5);
      return;
    }
    goto LAB_save;
  }

  uVar10 = *DAT_818;
  if (uVar10 == 0) {
    uint local_f8;
    local_f8 = ((uint)(*f3) << 24) | ((uint)(*f2) << 16) | ((uint)(*f1) << 8) | (uint)(*f0);
    *DAT_818 = local_f8;
    uVar5 = FUN_0002360c(*DAT_828, (uint)(BUF+5), 4);
    *DAT_828 = uVar5;
    if (local_f8 == 0x1c0000) {
      *DAT_81c = 0x1c0000;
      iVar6 = FUN_000167a8();
      *(volatile byte*)(long)(*(int*)(long)(iVar6+0x100c)) = 0xc;
      iVar6 = FUN_000167a8();
      if (*(int*)(long)(*(int*)(long)(iVar6+0x1054)) != 0x10) {
        if (*(char*)(long)(*(int*)(long)(param_1+0x100c)+7) == 0) {
          *(volatile byte*)(long)(*(int*)(long)(param_1+0x100c)+7) = 10;
        }
        uVar5 = FUN_000167a8();
        update_persist_task_status(uVar5, 0x10, 2);
      }
    }
    uVar10 = *DAT_820;
    FUN_00086c04(0, 0, uVar9 - 5);
    iVar7 = *DAT_81c;
    uVar9 = (uVar10 - 5) + uVar9;
    *DAT_820 = uVar9;
    if (iVar7 == 0x1c0000) {
      uVar10 = *DAT_818;
      goto LAB_237ec;
    }
  } else {
    uVar8 = *DAT_820;
    FUN_00086c04(0, 0, uVar9 - 1);
    iVar7 = *DAT_81c;
    uVar9 = (uVar8 - 1) + uVar9;
    *DAT_820 = uVar9;
    if (iVar7 == 0x1c0000) {
LAB_237ec:
      if (0x1fffff < uVar10) {
        return;
      }
    }
  }
  if (uVar9 < 0x1000) {
    return;
  }
LAB_save:
  FUN_00022834(*DAT_818, 0x20017062u, 0x1000u);
  uVar5 = FUN_0002360c(*DAT_828, 0x20017062u, 0x1000u);
  iVar7 = *DAT_82c;
  *DAT_828 = uVar5;
  if (0 < iVar7) {
    if (*DAT_830 == 0) {
      DEBUG_PRINT(0x0009e873u, 0x0009e8e5u, uVar5);
    } else {
      FUN_00019c70();
    }
  }
  iVar7 = 0x20018062;
  *DAT_818 = *DAT_818 + 0x1000;
  uVar9 = *DAT_820;
  FUN_00086c1e((void*)(long)(iVar7-0x1000), (void*)(long)iVar7, uVar9-0x1000, 0x1400u);
  *DAT_820 = uVar9-0x1000;
  return;
}

