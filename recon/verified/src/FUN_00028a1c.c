/* Reconstructed FUN_00028a1c @ 0x28a1c  (parity: 4/4 trials, PROVEN) */
#include <stdint.h>

extern void DEBUG_PRINT(uint32_t a, ...);
extern uintptr_t FUN_000167a8(void);
extern void FUN_00030af0(void);
extern void FUN_00032fd0(int32_t);
extern int64_t FUN_00032fdc(void);
extern void FUN_0007cb8e(int32_t);
extern void FUN_0007d0aa(void *a);
extern int32_t FUN_00086690(void);
extern void thunk_FUN_00072908(void *a, int32_t b, int32_t c, int32_t d, int32_t e, int32_t f, uint32_t g);
extern void FUN_0002893c(void);
extern void on_triple_click(void);
extern void FUN_00028964(void);
extern uint32_t FUN_0004c0a8(int32_t a);
extern void FUN_00019c70(uint32_t a, uint32_t b, uint32_t c, ...);

void FUN_00028a1c(char *param_1, int32_t param_2, uint32_t param_3)
{
  volatile uint8_t *pcVar2;
  volatile int32_t *piVar1;
  int32_t iVar3;
  int32_t iVar4;
  uint32_t uVar5;
  int32_t iVar6;
  int32_t iVar7;
  int32_t iVar8;
  int32_t iVar9;
  int64_t uVar10;
  int32_t iVar11;

  pcVar2 = (volatile uint8_t *)0x20019dacUL;
  piVar1 = (volatile int32_t *)0x20006a00UL;
  iVar6 = 0;
  iVar8 = 0;
  iVar7 = 0;
  iVar9 = 0;
  iVar11 = (int32_t)(intptr_t)param_1;
LAB_00028a32:
  do {
    while (1) {
      uVar10 = FUN_00032fdc();
      if ((int32_t)uVar10 == 1) {
        return;
      }
      thunk_FUN_00072908(param_1 + 0xb0, (int32_t)((uint64_t)uVar10 >> 32), 0x4000, 0, iVar11, param_2,
                          param_3);
      if ((*(char *)(param_1 + 1) != '\x01') &&
          (iVar3 = (int32_t)FUN_000167a8(), *(char *)(iVar3 + 1) != '\b')) break;
      FUN_0007cb8e(5000);
    }
  } while (-1 < (int32_t)((uint32_t)*(uint16_t *)(param_1 + 0x105c) << 0x1f));
  if (*piVar1 != 0) {
    FUN_00086690();
    FUN_00030af0();
    FUN_00086690();
    *piVar1 = 0;
  }
  if (*pcVar2 == '\x01') {
    iVar3 = FUN_00086690();
    FUN_0007d0aa(param_1 + 0x1078);
    if (30000 < iVar3 - iVar9) {
      iVar8 = 0;
      iVar6 = iVar8;
    }
    iVar6 = iVar6 + 1;
    *pcVar2 = 0;
  }
  else {
    iVar3 = iVar9;
    if (*pcVar2 == '\x02') {
      iVar8 = FUN_00086690();
      *pcVar2 = 0;
    }
  }
  param_2 = FUN_00086690();
  iVar4 = FUN_00086690();
  iVar9 = iVar3;
  if (iVar6 != 1) goto LAB_00028b3a;
  if (iVar7 == 0) {
    if ((iVar8 == 0) && (30000 < param_2 - iVar3)) {
      DEBUG_PRINT(0xa0b33);
      param_2 = iVar4;
      goto LAB_00028aae;
    }
  }
  else {
LAB_00028aae:
    iVar7 = 1;
  }
  goto LAB_00028ab0;
LAB_00028b3a:
  if (iVar6 == 0) goto LAB_00028a32;
LAB_00028ab0:
  if ((iVar8 <= iVar3) || (iVar4 - iVar8 < 0x2711)) goto LAB_00028a32;
  if (0x249f0 < iVar8 - iVar3) {
    DEBUG_PRINT(0xa0b7c);
    FUN_0007d0aa(param_1 + 0x1078);
code_r0x00028ad6:
    DEBUG_PRINT(0xa6990, *(uint32_t *)(param_1 + 0x1078));
    goto LAB_00028b4e;
  }
  uVar5 = 0xa0bc5;
  if (0x15f90 < iVar8 - iVar3) {
code_r0x00028b4a:
    DEBUG_PRINT(uVar5);
  }
  else {
    switch (iVar6) {
    case 1:
      uVar5 = 0xa0c0f;
      if (iVar7 == 0) {
        DEBUG_PRINT(0xa0c21);
        goto code_r0x00028ad6;
      }
      goto code_r0x00028b4a;
    case 2:
      FUN_0002893c();
      break;
    case 3:
      on_triple_click();
      break;
    case 4:
      if (0 < *(volatile int32_t *)0x2000230cUL) {
        uVar5 = 0xa0c6c;
        if (*(volatile int32_t *)0x20007554UL == 0) goto code_r0x00028ba2;
        FUN_00019c70(0xa0c6c, 0xa1a58, 4);
      }
      do {
        FUN_0007cb8e(500);
        uVar5 = FUN_0004c0a8(1);
code_r0x00028ba2:
        DEBUG_PRINT(uVar5);
      } while (1);
    default:
      FUN_00028964();
      FUN_00032fd0(1);
    }
  }
LAB_00028b4e:
  iVar6 = 0;
  iVar7 = iVar6;
  goto LAB_00028a32;
}

