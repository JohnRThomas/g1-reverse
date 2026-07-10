#include "g1_app_symbols.h"
/* named: k_mutex_lock */
/* Reconstructed k_mutex_lock @ 0x723b8  (parity: 300/300 trials, PROVEN) */
extern int  z_spin_lock_valid(int);
extern void z_spin_lock_set_owner(int);
extern int  z_spin_unlock_valid(int);
extern int  z_reschedule(int,int);
extern int  FUN_00073f6c(int,int,int);
extern void printk(int,int,int,int,int,int);
extern void assert_post_action(int,int);
extern int  adjust_owner_prio_isra_0(int,int) __asm__("adjust_owner_prio.isra.0");
#define VI(a)  (*(volatile int*)(a))
#define VSC(a) (*(volatile signed char*)(a))

int k_mutex_lock(int *param_1,int param_2,int *param_3,int param_4){
  volatile int *p = param_1;
  int iVar3, iVar4, cVar5, cVar1;
  (void)param_2;
MAIN:
  if (z_spin_lock_valid(((uintptr_t)&sched_spinlock) /*=0x2000b470*/) == 0) {
    printk(0,0,0,0,0,0); printk(0,0,0,0,0,0); assert_post_action(0,0);
    goto MAIN;
  }
  z_spin_lock_set_owner(((uintptr_t)&sched_spinlock) /*=0x2000b470*/);
  if (p[3] == 0) {
    iVar4 = VSC(VI(((uintptr_t)&g_current_thread_ptr) /*=0x2000b450*/) + 0xe);
    goto L7244e;
  }
  if (p[2] == VI(((uintptr_t)&g_current_thread_ptr) /*=0x2000b450*/)) {
    iVar4 = p[4];
    goto L7244e;
  }
  if ((((int)param_3) | param_4) == 0) {
    if (z_spin_unlock_valid(((uintptr_t)&sched_spinlock) /*=0x2000b470*/) != 0) return 0xfffffff0;
    printk(0,0,0,0,0,0); printk(0,0,0,0,0,0); assert_post_action(0,0);
    goto MAIN;
  }
  cVar5 = VSC(VI(((uintptr_t)&g_current_thread_ptr) /*=0x2000b450*/) + 0xe);
  cVar1 = VSC(p[2] + 0xe);
  { int r1 = cVar5;
    if (cVar5 >= cVar1) r1 = cVar1;
    if (r1 < -0x7f) r1 = -0x7f;
    iVar3 = 0;
    if (cVar1 > r1) iVar3 = adjust_owner_prio_isra_0(0,0);
  }
  if (FUN_00073f6c(((uintptr_t)&sched_spinlock) /*=0x2000b470*/,0,(int)param_1) == 0) return 0;
  if (z_spin_lock_valid(((uintptr_t)&sched_spinlock) /*=0x2000b470*/) == 0) {
    printk(0,0,0,0,0,0); printk(0,0,0,0,0,0); assert_post_action(0,0);
    goto MAIN;
  }
  z_spin_lock_set_owner(((uintptr_t)&sched_spinlock) /*=0x2000b470*/);
  if (p[2] != 0) {
    int *piVar7 = (int*)p[0];
    iVar4 = p[4];
    if (param_1 != piVar7 && piVar7 != 0) {
      if (iVar4 >= (int)VSC((int)piVar7 + 0xe)) iVar4 = (int)VSC((int)piVar7 + 0xe);
      if (iVar4 < -0x7f) iVar4 = -0x7f;
    }
    if (adjust_owner_prio_isra_0(p[2], iVar4) != 0) goto L72504;
  }
  if (iVar3 != 0) goto L72504;
  if (z_spin_unlock_valid(((uintptr_t)&sched_spinlock) /*=0x2000b470*/) != 0) return 0xfffffff5;
  printk(0,0,0,0,0,0); printk(0,0,0,0,0,0); assert_post_action(0,0);
  goto MAIN;
L72504:
  z_reschedule(((uintptr_t)&sched_spinlock) /*=0x2000b470*/, 0);
  return 0xfffffff5;
L7244e:
  p[3] = p[3] + 1;
  p[4] = iVar4;
  p[2] = VI(((uintptr_t)&g_current_thread_ptr) /*=0x2000b450*/);
  if (z_spin_unlock_valid(((uintptr_t)&sched_spinlock) /*=0x2000b470*/) != 0) return 0;
  printk(0,0,0,0,0,0); printk(0,0,0,0,0,0); assert_post_action(0,0);
  goto MAIN;
}

