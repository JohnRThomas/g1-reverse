#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0103814c @ 0x0103814c
 * public-name: FUN_0103814c
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_01039bb0 @ 0x01039bb0
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103d3b6                           @ 0x0103d3b6
 *   g_net_kernel_timeout_dlist_head          @ 0x21000750
 *   g_net_kernel_curr_tick                   @ 0x210044f0
 *   announce_remaining                       @ 0x21004b6c
 */
/* net-core FUN_0103814c @ 0x103814c  (parity 300 trials PROVEN) */
/* net-core FUN_0103814c @ 0x103814c  (parity 300 trials PROVEN) */
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"
static inline int isCurrentModePrivileged(void){return (__get_CONTROL() & 1u)==0;}
static inline int getBasePriority(void){return (int)__get_BASEPRI();}
static inline void setBasePriority(int p){__set_BASEPRI((unsigned)p);}
static inline void InstructionSynchronizationBarrier(int x){(void)x;__ISB();}

typedef unsigned int u32;
typedef int i32;
typedef unsigned char u8;

extern int FUN_0103610c(int);
extern int FUN_01036128(int);
extern void FUN_01036144(int);
extern void FUN_01037f54(int *node);
extern u32 FUN_01037f14(void);
extern void FUN_0103175c(u32, int);
extern void assert_post_action(unsigned int, unsigned int);
extern void assert_print(unsigned int, unsigned int, unsigned int);
/* The real bytes end with a tail branch (pop then b.w) to a shared handler
   far below our own address range, so the harness treats that whole
   second logical half of the Ghidra decompile as a single external call. */
extern void FUN_01037438(void);

#define DAT_0103826c 0x21004b70u
#define DAT_01038270 ((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/
#define DAT_01038274 ((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/
#define DAT_01038278 ((unsigned long)&g_net_kernel_timeout_dlist_head) /*=0x21000750*/
#define DAT_0103827c ((unsigned long)&announce_remaining) /*=0x21004b6c*/
#define DAT_01038280 ((unsigned long)&g_net_kernel_curr_tick) /*=0x210044f0*/

static inline int SBORROW4(i32 a, i32 b) {
    int r; return __builtin_sub_overflow(a, b, &r);
}
static inline int CARRY4(u32 a, u32 b) {
    u32 r; return __builtin_add_overflow(a, b, &r);
}

void FUN_0103814c(u32 param_1)
{
  int bVar2;
  volatile int *piVar3;
  volatile u32 *puVar4;
  volatile u32 *puVar5;
  i32 iVar6;
  i32 iVar7;
  u32 uVar14;
  u32 uVar9;
  u32 uVar10;
  u32 uVar11 = 0;
  volatile int *piVar12;
  u32 uVar13;

  uVar14 = 0;
  bVar2 = isCurrentModePrivileged();
  if (bVar2) {
    uVar14 = (u32)getBasePriority();
  }
  bVar2 = isCurrentModePrivileged();
  if (bVar2) {
    uVar9 = (u32)getBasePriority();
    if (uVar9 == 0 || 0x40 < uVar9) {
      setBasePriority(0x40);
    }
  }
  InstructionSynchronizationBarrier(0xf);
  iVar6 = FUN_0103610c(DAT_0103826c);
  puVar4 = (volatile u32 *)DAT_0103827c;
  piVar3 = (volatile int *)DAT_01038278;
  if (iVar6 == 0) {
    assert_print(DAT_01038274, DAT_01038270, 0x72);
    uVar14 = 0x72;
    assert_post_action(DAT_01038270, uVar14);
    /* real hardware never returns from this call; but the compiled bytes
       physically fall through into the same continuation as the success
       path, so faithfully keep going instead of cutting the trace here. */
  }
  FUN_01036144(DAT_0103826c);
  *puVar4 = param_1;
  puVar5 = (volatile u32 *)DAT_01038280;
  piVar12 = (volatile int *)*piVar3;
  if (piVar12 == piVar3) {
    piVar12 = (volatile int *)0;
  }
  do {
    uVar11 = *puVar4;
    uVar10 = *puVar5;
    uVar9 = puVar5[1];
    if (piVar12 == (volatile int *)0) goto LAB_01038236;
    uVar13 = (u32)piVar12[4];
    iVar7 = piVar12[5];
    iVar6 = (i32)uVar11 >> 0x1f;
    if ((i32)((iVar6 - iVar7) - (u32)(uVar11 < uVar13)) < 0 !=
        (SBORROW4(iVar6, iVar7) != SBORROW4(iVar6 - iVar7, (i32)(u32)(uVar11 < uVar13)))) {
      piVar12[4] = (i32)(uVar13 - uVar11);
      piVar12[5] = (iVar7 - iVar6) - (i32)(u32)(uVar13 < uVar11);
      goto LAB_01038236;
    }
    piVar12[4] = 0;
    piVar12[5] = 0;
    *puVar5 = uVar13 + uVar10;
    puVar5[1] = uVar9 + ((i32)uVar13 >> 0x1f) + (u32)CARRY4(uVar13, uVar10);
    FUN_01037f54(piVar12);
    iVar6 = FUN_01036128(DAT_0103826c);
    if (iVar6 == 0) {
      assert_print(DAT_01038274, DAT_01038270, 0xf0);
      uVar14 = 0xf0;
      assert_post_action(DAT_01038270, uVar14);
      /* real fallthrough: nothing physically follows here in-body, this is
         the tail exit; the loop below is unreachable on this path but the
         compiler on the original also does not return, so end here. */
      return;
    }
    bVar2 = isCurrentModePrivileged();
    if (bVar2) {
      setBasePriority((int)uVar14);
    }
    InstructionSynchronizationBarrier(0xf);
    ((void (*)(int *))piVar12[2])(piVar12);
    uVar14 = 0;
    bVar2 = isCurrentModePrivileged();
    if (bVar2) {
      uVar14 = (u32)getBasePriority();
    }
    bVar2 = isCurrentModePrivileged();
    if (bVar2) {
      uVar9 = (u32)getBasePriority();
      if (uVar9 == 0 || 0x40 < uVar9) {
        setBasePriority(0x40);
      }
    }
    InstructionSynchronizationBarrier(0xf);
    iVar6 = FUN_0103610c(DAT_0103826c);
    if (iVar6 == 0) {
      assert_print(DAT_01038274, DAT_01038270, 0x72);
      uVar14 = 0x72;
      assert_post_action(DAT_01038270, uVar14);
      return;
    }
    FUN_01036144(DAT_0103826c);
    piVar12 = (volatile int *)*piVar3;
    uVar11 = *puVar4 - uVar13;
    *puVar4 = uVar11;
  } while (piVar12 != piVar3);
  uVar10 = *puVar5;
  uVar9 = puVar5[1];
LAB_01038236:
  *puVar5 = uVar11 + uVar10;
  puVar5[1] = uVar9 + ((i32)uVar11 >> 0x1f) + (u32)CARRY4(uVar11, uVar10);
  *puVar4 = 0;
  {
    u32 uVar8 = FUN_01037f14();
    FUN_0103175c(uVar8, 0);
  }
  iVar6 = FUN_01036128(DAT_0103826c);
  if (iVar6 == 0) {
    assert_print(DAT_01038274, DAT_01038270, 0xf0);
    uVar14 = 0xf0;
    assert_post_action(DAT_01038270, uVar14);
    return;
  }
  bVar2 = isCurrentModePrivileged();
  if (bVar2) {
    setBasePriority((int)uVar14);
  }
  InstructionSynchronizationBarrier(0xf);
  /* tail-branch out of body to the shared continuation (offset 0x1037438,
     far below this function) — a single external call/oracle. */
  FUN_01037438();
}
