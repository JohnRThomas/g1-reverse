/* Reconstructed touch_key_thread @ 0x2a0d8  (parity: 1/1 trials, PROVEN) */
#include <stdint.h>

extern void DEBUG_PRINT(uint32_t a, ...);
extern uintptr_t FUN_000167a8(void);
extern void FUN_00019c70(uint32_t a, uint32_t b, uint32_t c, ...);
extern void FUN_0002a0c0(void);
extern void FUN_00030af0(void);
extern void FUN_0007cb8e(int32_t);
extern void FUN_0007d0aa(void *a);
extern int32_t FUN_00086690(void);
extern void thunk_FUN_00072908(void *a);
extern void FUN_0002316c(void *a, int32_t b);
extern void FUN_0007c058(int32_t a);
extern void FUN_00017a28(void);
extern void FUN_00017a34(void);
extern uint32_t FUN_0004c0a8(int32_t a);

void touch_key_thread(char *param_1)
{
  volatile int32_t *piVar1;
  volatile int32_t *piVar2;
  int32_t iVar3;
  int32_t iVar4;
  int32_t iVar5;
  uint32_t format_string;
  uint32_t uVar6;
  int32_t iVar7;
  int32_t iVar8;
  int32_t iVar9;
  int32_t iVar10;
  int32_t iVar11;
  int32_t iVar12;
  int32_t iVar13;

  iVar10 = 0;
  iVar9 = 0;
  iVar7 = 0;
  iVar11 = 0;
  iVar12 = 0;
LAB_0002a0e8:
  do {
    while ((thunk_FUN_00072908(param_1 + 0xb0), *(char *)(param_1 + 1) == '\x01' ||
            ((iVar3 = (int32_t)FUN_000167a8(), *(char *)(iVar3 + 1) == '\b')))) {
      FUN_0007cb8e(5000);
    }
    if (*(volatile int32_t *)0x20006a00UL != 0) {
      FUN_00030af0();
      *(volatile int32_t *)0x20006a00UL = 0;
    }
  } while (-1 < (int32_t)((uint32_t)*(uint16_t *)(param_1 + 0x105c) << 0x1f));
  if (*(volatile uint8_t *)0x20019dacUL == 1) {
    iVar3 = FUN_00086690();
    FUN_0007d0aa(param_1 + 0x1078);
    if (10000 < iVar3 - iVar11) {
      iVar9 = 0;
      iVar7 = iVar9;
    }
    iVar8 = iVar7 + 1;
    *(volatile uint8_t *)0x20019dacUL = 0;
  }
  else {
    iVar8 = iVar7;
    iVar3 = iVar11;
    if (*(volatile uint8_t *)0x20019dacUL == 2) {
      iVar9 = FUN_00086690();
      *(volatile uint8_t *)0x20019dacUL = 0;
      *(volatile uint8_t *)0x20018d89UL = 0;
    }
  }
  iVar4 = FUN_00086690();
  iVar5 = FUN_00086690();
  piVar2 = (volatile int32_t *)0x20007554UL;
  piVar1 = (volatile int32_t *)0x2000230cUL;
  iVar5 = iVar5 - iVar9;
  iVar13 = iVar9 - iVar3;
  iVar7 = iVar8;
  iVar11 = iVar3;
  if (iVar8 != 1) goto LAB_0002a2c0;
  iVar4 = iVar4 - iVar3;
  if (iVar10 != 0) {
    if (iVar9 == 0) {
LAB_0002a222:
      if (iVar12 == 0) {
        iVar7 = 0x23;
      }
      else {
        iVar7 = 3;
      }
      if (iVar7 * 30000 < iVar4) {
        if (0 < *piVar1) {
          if (*piVar2 == 0) {
            DEBUG_PRINT(0xa1626, 0xa1a76, iVar12);
          }
          else {
            FUN_00019c70(0,0,0);
          }
        }
        iVar10 = 0;
        *(volatile int32_t *)0x20007b18UL = 6;
        FUN_0002a0c0();
        iVar7 = 0;
        iVar12 = iVar10;
        goto LAB_0002a0e8;
      }
      if (iVar3 < 0) goto LAB_0002a24e;
    }
    else {
      iVar7 = iVar10;
      if (iVar9 <= iVar3) goto LAB_0002a0e8;
LAB_0002a24e:
      if (10000 < iVar5) {
        if (15000 < iVar13) {
          iVar10 = 1;
          goto LAB_0002a260;
        }
        goto LAB_0002a174;
      }
    }
    iVar10 = 1;
    iVar7 = iVar8;
    goto LAB_0002a0e8;
  }
  if (iVar9 == 0) {
    FUN_0007d0aa(param_1 + 0x1078);
    if (((int32_t)0xffffb1e1 <= *(int32_t *)(param_1 + 0x1078)) &&
        (*(int32_t *)(param_1 + 0x1078) < 20000)) {
      iVar7 = 0;
      goto LAB_0002a0e8;
    }
    if (15000 < iVar4) {
      if (0 < *piVar1) {
        if (*piVar2 == 0) {
          DEBUG_PRINT(0xa15d6, 0xa1a76, iVar4);
        }
        else {
          FUN_00019c70(0,0,0);
        }
      }
      *(volatile int32_t *)0x20007b18UL = 4;
      FUN_0002a0c0();
      goto LAB_0002a222;
    }
    if (-1 < iVar3) {
      iVar10 = 0;
      goto LAB_0002a0e8;
    }
  }
  else if (iVar9 <= iVar3) goto LAB_0002a0e8;
  if (10000 < iVar5) {
    if (15000 < iVar13) goto LAB_0002a260;
LAB_0002a174:
    if (0 < *piVar1) {
      if (*piVar2 == 0) {
        DEBUG_PRINT(0xa172a, 0xa1a76, *(uint32_t *)(param_1 + 0x1078));
      }
      else {
        FUN_00019c70(0,0,0);
      }
    }
    uVar6 = 1;
    goto LAB_0002a282;
  }
  goto LAB_0002a0e8;
LAB_0002a2c0:
  if (((iVar8 == 0) || (iVar9 <= iVar3)) || (iVar5 < 0x2711)) goto LAB_0002a0e8;
  if (15000 < iVar13) {
LAB_0002a260:
    if (iVar13 <= (int32_t)0x11940) {
      if (0 < *piVar1) {
        if (*piVar2 == 0) {
          DEBUG_PRINT(0xa1626, 0xa1a76);
        }
        else {
          FUN_00019c70(0,0,0);
        }
      }
      iVar9 = 0;
      iVar7 = iVar8;
      iVar12 = 1;
      goto LAB_0002a0e8;
    }
    if (0 < *piVar1) {
      if (*piVar2 == 0) {
        DEBUG_PRINT(0xa1681, 0xa1a76);
      }
      else {
        FUN_00019c70(0,0,0);
      }
    }
    uVar6 = 5;
    goto LAB_0002a282;
  }
  switch (iVar8) {
  case 2:
    if (0 < *piVar1) {
      if (*piVar2 == 0) {
        DEBUG_PRINT(0xa177f, 0xa1a76);
      }
      else {
        FUN_00019c70(0,0,0);
      }
    }
    uVar6 = 2;
    goto LAB_0002a282;
  case 3:
    if (0 < *piVar1) {
      if (*piVar2 == 0) {
        DEBUG_PRINT(0xa17d1, 0xa1a76);
      }
      else {
        FUN_00019c70(0,0,0);
      }
    }
    uVar6 = 3;
LAB_0002a282:
    *(volatile int32_t *)0x20007b18UL = uVar6;
    FUN_0002a0c0();
    break;
  case 5:
    goto code_r0x0002a410;
  case 10:
    FUN_0002316c(param_1, 1);
    break;
  case 0xf:
    FUN_0007c058(10);
    if (0 < *(volatile int32_t *)0x2000230cUL) {
      if (*(volatile int32_t *)0x20007554UL == 0) {
        DEBUG_PRINT(0xa1823, 0xa1a76, 0xf);
      }
      else {
        FUN_00019c70(0,0,0);
      }
    }
  }
  iVar10 = 0;
  iVar7 = iVar10;
  goto LAB_0002a0e8;
code_r0x0002a410:
  if (0 < *(volatile int32_t *)0x2000230cUL) {
    format_string = 0xa184b;
    if (*(volatile int32_t *)0x20007554UL == 0) goto code_r0x0002a476;
    FUN_00019c70(0xa184b, 0xa1a76, 5);
  }
  do {
    FUN_00017a28();
    if (0 < *(volatile int32_t *)0x2000230cUL) {
      if (*(volatile int32_t *)0x20007554UL == 0) {
        DEBUG_PRINT(0xa1868, 0xa1a76);
      }
      else {
        FUN_00019c70(0,0,0);
      }
    }
    FUN_00017a34();
    if (0 < *(volatile int32_t *)0x2000230cUL) {
      if (*(volatile int32_t *)0x20007554UL == 0) {
        DEBUG_PRINT(0xa187e, 0xa1a76);
      }
      else {
        FUN_00019c70(0,0,0);
      }
      if (0 < *(volatile int32_t *)0x2000230cUL) {
        if (*(volatile int32_t *)0x20007554UL == 0) {
          DEBUG_PRINT(0xa0c6c, 0xa1a76, 5);
        }
        else {
          FUN_00019c70(0,0,0);
        }
      }
    }
    FUN_0007cb8e(500);
    format_string = FUN_0004c0a8(1);
code_r0x0002a476:
    DEBUG_PRINT(format_string);
  } while (1);
}

