/* Reconstructed FUN_000753ec @ 0x753ec  (parity: 300/300 trials, PROVEN) */
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"
static inline unsigned read_basepri(void){return __get_BASEPRI();}
static inline void write_basepri(unsigned v){__set_BASEPRI(v);}
static inline void write_basepri_max(unsigned v){__set_BASEPRI_MAX(v);}
static inline void isb_sy(void){__ISB();}

extern int FUN_00072040(unsigned,...);
extern int FUN_0007205c(unsigned,...);
extern int FUN_00072078(unsigned,...);
extern int FUN_0007e2ec(int,...);
extern int FUN_0007e2fa(int,...);

void FUN_000753ec(int param_1, int param_2, unsigned param_3)
{
  unsigned uVar4 = 0x2000b4a0UL;
  int iVar3 = param_2 * 0x14 + param_1;
  int iVar7;
  int *piVar6;
  int uVar5 = 0;

  for (;;) {
    if (param_2 == 0) return;

    *(volatile int*)(iVar3 - 0xc) = 0;
    unsigned char sw = (*(volatile unsigned char*)(iVar3 - 7)) & 0x3f;

    switch (sw) {
      case 0:
        goto switchD;
      case 1:
        if (*(volatile int*)(iVar3 - 4) == 0) {
          FUN_0007e2fa(0x99cbd, 0xf87b7, 0xf871d, 0xbe);
          FUN_0007e2fa(0xf87d4);
          uVar5 = 0xbe;
          goto LAB;
        }
        break;
      case 2:
        if (*(volatile int*)(iVar3 - 4) == 0) {
          FUN_0007e2fa(0x99cbd, 0xf875b, 0xf871d, 0xb6);
          FUN_0007e2fa(0xf8775);
          uVar5 = 0xb6;
          goto LAB;
        }
        break;
      case 4:
        if (*(volatile int*)(iVar3 - 4) == 0) {
          FUN_0007e2fa(0x99cbd, 0xf878a, 0xf871d, 0xba);
          FUN_0007e2fa(0xf87a6);
          uVar5 = 0xba;
          goto LAB;
        }
        break;
      case 8:
        if (*(volatile int*)(iVar3 - 4) == 0) {
          FUN_0007e2fa(0x99cbd, 0xf87eb, 0xf871d, 0xc2);
          FUN_0007e2fa(0xf8806);
          uVar5 = 0xc2;
          goto LAB;
        }
        break;
      default:
        FUN_0007e2fa(0x99cbd, 0xf7a30, 0xf871d, 0xcf);
        FUN_0007e2fa(0xf881f);
        uVar5 = 0xcf;
        goto LAB;
    }

    iVar7 = *(volatile int*)(iVar3 - 0x14);
    if (iVar7 != 0) {
      piVar6 = *(volatile int**)(iVar3 - 0x10);
      *piVar6 = iVar7;
      *(volatile int*)(iVar7 + 4) = (int)(long)piVar6;
      *(volatile int*)(iVar3 - 0x14) = 0;
      *(volatile int*)(iVar3 - 0x10) = 0;
    }

  switchD:
    iVar7 = FUN_0007205c(uVar4);
    if (iVar7 == 0) {
      FUN_0007e2fa(0x99cbd, 0xf08f4, 0xf08c7, 0xf0);
      FUN_0007e2fa(0xf090b, 0x2000b4a0UL);
      uVar5 = 0xf0;
      goto LAB;
    }

    write_basepri(param_3);
    isb_sy();

    param_3 = read_basepri();
    write_basepri_max(0x20);
    isb_sy();

    iVar7 = FUN_00072040(uVar4);
    param_2 = param_2 - 1;
    if (iVar7 == 0) {
      FUN_0007e2fa(0x99cbd, 0xf0920, 0xf08c7, 0x72);
      FUN_0007e2fa(0xf0935, 0x2000b4a0UL);
      uVar5 = 0x72;
      goto LAB;
    }
    FUN_00072078(uVar4);
    iVar3 = iVar3 - 0x14;
  }

LAB:
  FUN_0007e2ec(uVar4, uVar5);
}
