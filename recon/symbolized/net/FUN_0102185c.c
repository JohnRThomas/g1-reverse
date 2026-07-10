#include "g1_net_symbols.h"
/* net-core FUN_0102185c @ 0x102185c  (parity 300 trials PROVEN) */
/* net-core FUN_0102185c @ 0x102185c  (parity 300 trials PROVEN) */
/* net-core FUN_0102185c @ 0x102185c  (parity 300 trials PROVEN) */

static volatile int *const P_10218a8 = (volatile int *)((uintptr_t)&g_net_res_reg_handle) /*=0x210016bc*/;
static volatile int *const P_10218ac = (volatile int *)((uintptr_t)&g_net_res_reg_key) /*=0x210016b4*/;
static volatile unsigned short *const P_10218b0 = (volatile unsigned short *)((uintptr_t)&g_net_res_reg_param16) /*=0x210016c0*/;
extern void FUN_01008d00(int,int);
extern int FUN_01027a4a(int);
void FUN_0102185c(int param_1, unsigned short param_2)
{
  if (*P_10218a8 == 0) {
    *P_10218ac = param_1;
    int iVar1 = FUN_01027a4a(*P_10218ac);
    *P_10218a8 = iVar1;
    if (*P_10218a8 == 0) {
      FUN_01008d00(0x84, 0x22);
    }
    *P_10218b0 = param_2;
  }
}



