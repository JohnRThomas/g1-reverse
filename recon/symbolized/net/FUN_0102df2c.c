#include "g1_net_symbols.h"
/* net-core FUN_0102df2c @ 0x102df2c  (parity 300 trials PROVEN) */

typedef unsigned char undefined1;
typedef unsigned int undefined4;
typedef long long longlong;
typedef unsigned long long ulonglong;

extern int FUN_0102df04(void);
extern void FUN_0102de50(unsigned int a, int b);
extern longlong thunk_FUN_01038284(void);
extern void FUN_0102cf00(unsigned int a, int b);
extern void FUN_01039bbe(void *a, void *b, int c);
extern void FUN_01039bb0(void *a, int b);
extern int FUN_01039dd0(unsigned int *p);

#define DAT_flag   (*(volatile unsigned char *)((unsigned long)&g_net_tick_handler_enable_flag) /*=0x21004fac*/)
#define DAT_sem    (*(volatile unsigned int  *)((unsigned long)&g_net_tick_pending_cnt) /*=0x21004668*/)
#define DAT_pend   (*(volatile int  *)((unsigned long)&g_net_tick_correction_pending) /*=0x21004664*/)
#define DAT_tick0  (*(volatile unsigned int *)((unsigned long)&g_net_uptime_ms_lo) /*=0x21002788*/)
#define DAT_tick1  (*(volatile unsigned int *)((unsigned long)&g_net_uptime_ms_hi) /*=0x2100278c*/)
#define DAT_p28    ((unsigned int *)((unsigned long)&g_net_periodic_work_obj) /*=0x2100086c*/)
#define DAT_465c   (*(volatile unsigned int *)((unsigned long)&g_net_periodic_work_ptr) /*=0x2100465c*/)
#define STR_A      ((void*)((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/)
#define STR_B      ((void*)((unsigned long)&rodata_103d5d7) /*=0x103d5d7*/)

int FUN_0102df2c(void)
{
  int r5;
  unsigned int node;
  unsigned int connPtr;
  unsigned int handlerPtr;
  void (*fn)(unsigned int, int);
  ulonglong up;
  unsigned int lo;
  unsigned int hi;
  unsigned int uVar4;
  unsigned int delta_lo;
  unsigned int delta_hi;
  unsigned int borrow2;

  if (DAT_flag == 0) {
    return 0;
  }

  r5 = FUN_0102df04();
  if (r5 != 0) {
    DAT_sem = DAT_sem - 1;

    node = ((unsigned long)&rodata_103c0ec) /*=0x103c0ec*/;
    for (;;) {
      if (node > ((unsigned long)&rodata_103c0fc) /*=0x103c0fc*/) {
        FUN_01039bbe(STR_A, STR_B, 0x1c5);
        FUN_01039bb0(STR_B, 0x1c5);
        for(;;) {}
      }
      if (node == ((unsigned long)&rodata_103c0fc) /*=0x103c0fc*/) break;
      connPtr = *(unsigned int *)(node + 4);
      if (*(unsigned char *)(connPtr + 5) != 0) {
        handlerPtr = *(unsigned int *)node;
        fn = *(void (**)(unsigned int, int))handlerPtr;
        fn(node, r5);
      }
      node += 0x10;
    }
    FUN_0102cf00(DAT_465c, r5);
  }

  if (0 < DAT_pend) {
    up = (ulonglong)thunk_FUN_01038284();
    up = up * 1000;
    lo = (unsigned int)up;
    hi = (unsigned int)(up >> 32);
    uVar4 = (lo >> 15) | (hi << 17);
    delta_lo = uVar4 - DAT_tick0;
    delta_hi = (hi >> 15) - DAT_tick1 - (unsigned int)(uVar4 < DAT_tick0);
    borrow2 = (delta_lo < 1001) ? 1u : 0u;
    if (!(delta_hi == 0 && delta_lo < 1001)) {
      FUN_0102de50(DAT_tick1, (int)(delta_hi - borrow2));
    }
  }

  {
    unsigned int t0 = DAT_tick0;
    unsigned int t1 = DAT_tick1;
    unsigned int nt0 = t0 + 1000;
    unsigned int nt1 = t1 + (nt0 < t0);
    DAT_tick0 = nt0;
    DAT_tick1 = nt1;
  }

  return FUN_01039dd0(DAT_p28);
}
