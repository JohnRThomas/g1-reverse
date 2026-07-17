/* readable reconstruction; identity: FUN_010388c8 @ 0x010388c8
 * public-name: FUN_010388c8
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103d3b6                           @ 0x0103d3b6
 */
/* net-core FUN_010388c8 @ 0x10388c8  (parity 300 trials PROVEN) */
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"
static inline unsigned int getBasePriority(void){return __get_BASEPRI();}
static inline void setBasePriority(unsigned p){__set_BASEPRI(p);}
static inline void isb(void){__ISB();}

#define C_0103894c 0x21004b78
#define C_01038950 0x0103d3b6
#define C_01038954 0x0103d2a7

extern int FUN_0103610c(int);
extern void FUN_01036144(int);
extern int FUN_01036128(int);
extern void assert_print(int, int, unsigned int);
extern void FUN_01039bb0(int, unsigned int);
extern int FUN_0103b442(int *item, unsigned int state);
extern void FUN_01037130(int, unsigned int);

int FUN_010388c8(int *param_1, int param_2)
{
  unsigned int r6;
  int r0;
  int r1;
  unsigned int r2;
  int *piVar4;
  int iVar3;
  int *piVar5;
  int uVar6;

  r6 = getBasePriority();
  setBasePriority(0x40);
  isb();
  r0 = FUN_0103610c(C_0103894c);
  if (r0 != 0) goto L8f8;

  r1 = C_01038950;
  r2 = 0x72;
  assert_print(C_01038954, r1, r2);
  r1 = 0x72;

L8f2:
  r0 = C_01038950;
  FUN_01039bb0(r0, (unsigned int)r1);
  goto L8f8;

L8f8:
  FUN_01036144(C_0103894c);
  piVar4 = (int *)*param_1;
  param_1[3] = param_2;
  param_1[2] = 1;
  if (param_1 == piVar4) {
    r0 = FUN_01036128(C_0103894c);
    if (r0 == 0) {
      r1 = C_01038950;
      r2 = 0xf0;
      assert_print(C_01038954, r1, r2);
      r1 = 0xf0;
      goto L8f2;
    }
    setBasePriority(r6);
    isb();
    return 0;
  } else {
    iVar3 = *piVar4;
    piVar5 = (int *)piVar4[1];
    *piVar5 = iVar3;
    *(int **)(iVar3 + 4) = piVar5;
    *piVar4 = 0;
    piVar4[1] = 0;
    uVar6 = FUN_0103b442(piVar4, 1);
    FUN_01037130(C_0103894c, r6);
    return uVar6;
  }
}
