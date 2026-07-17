#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0102ca80 @ 0x0102ca80
 * public-name: FUN_0102ca80
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103d394                           @ 0x0103d394
 *   rodata_103d3b6                           @ 0x0103d3b6
 */
/* net-core FUN_0102ca80 @ 0x102ca80  (parity 300 trials PROVEN) */
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"
static inline int isCurrentModePrivileged(void){return (__get_CONTROL()&1)==0;}
static inline int getBasePriority(void){return (int)__get_BASEPRI();}
static inline void setBasePriority(int p){__set_BASEPRI((unsigned)p);}
static inline void InstructionSynchronizationBarrier(int x){(void)x;__ISB();}

extern int FUN_01039b16(void);
extern int FUN_0103610c(int);
extern void FUN_01036144(int);
extern void FUN_0102c6f8(int, int, unsigned int);
extern int FUN_01036128(int);
extern void FUN_01039b36(int, int, int, int);
extern void FUN_01039bb0(unsigned int, unsigned int);
extern void FUN_01039bbe(unsigned int, unsigned int, unsigned int);

#define DAT_0102cb78 ((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/
#define DAT_0102cb7c ((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/
#define DAT_0102cb80 ((unsigned long)&rodata_103d394) /*=0x103d394*/

unsigned int FUN_0102ca80(unsigned int *param_1, unsigned int *param_2)
{
  unsigned short uVar1;
  int bVar2;
  unsigned int uVar3;
  int iVar4;
  int iVar5;
  unsigned int uVar7;
  unsigned int uVar9;
  int puVar8i;

  uVar3 = (unsigned int)FUN_01039b16();
  if ((int)uVar3 < 0) {
    return uVar3;
  }
  puVar8i = (int)param_1 + 0x14;
  uVar9 = 0;
  bVar2 = isCurrentModePrivileged();
  if (bVar2) {
    uVar9 = getBasePriority();
  }
  bVar2 = isCurrentModePrivileged();
  if (bVar2) {
    uVar3 = getBasePriority();
    if (uVar3 == 0 || 0x40 < uVar3) {
      setBasePriority(0x40);
    }
  }
  InstructionSynchronizationBarrier(0xf);
  iVar4 = FUN_0103610c(puVar8i);
  if (iVar4 == 0) {
    FUN_01039bbe(DAT_0102cb7c, DAT_0102cb78, 0x72);
    FUN_01039bb0(DAT_0102cb78, 0x72);
    __builtin_unreachable();
  }
  FUN_01036144(puVar8i);
  uVar1 = *(unsigned short *)((char *)param_1 + 0x1c);
  uVar3 = uVar1 & 7;
  if (*(short *)((char *)param_1 + 0x1e) == -1) {
    uVar7 = 0xfffffff5;
    iVar4 = 0;
  } else {
    uVar7 = uVar3;
    if (uVar3 != 2) {
      switch (uVar3) {
      case 0:
      case 4:
      case 6:
        *param_2 = 0;
        if (param_1[1] == 0) {
          *param_1 = (unsigned int)(unsigned long)param_2;
          param_1[1] = (unsigned int)(unsigned long)param_2;
        } else {
          *(unsigned int *)(unsigned long)param_1[1] = (unsigned int)(unsigned long)param_2;
          param_1[1] = (unsigned int)(unsigned long)param_2;
        }
        if ((uVar1 & 7) == 0) {
          FUN_0102c6f8((int)(long)param_1, 2, uVar9);
          return uVar3;
        }
        break;
      case 1:
        uVar7 = 0xfffffffb;
        break;
      case 5:
        uVar7 = 0xffffff7a;
        break;
      default:
        FUN_01039bbe(DAT_0102cb7c, DAT_0102cb80, 0x1c8);
        FUN_01039bb0(DAT_0102cb80, 0x1c8);
        __builtin_unreachable();
      }
      iVar4 = 0;
    } else {
      *(short *)((char *)param_1 + 0x1e) = *(short *)((char *)param_1 + 0x1e) + 1;
    }
  }
  iVar5 = FUN_01036128(puVar8i);
  if (iVar5 != 0) {
    bVar2 = isCurrentModePrivileged();
    if (bVar2) {
      setBasePriority((int)uVar9);
    }
    InstructionSynchronizationBarrier(0xf);
    if (iVar4 != 0) {
      FUN_01039b36((int)(long)param_1, (int)(long)param_2, (int)uVar3, 0);
    }
    return uVar7;
  }
  FUN_01039bbe(DAT_0102cb7c, DAT_0102cb78, 0xf0);
  FUN_01039bb0(DAT_0102cb78, 0xf0);
  __builtin_unreachable();
}
