#include "g1_net_symbols.h"
/* net-core FUN_0102afbc @ 0x102afbc  (parity 300 trials PROVEN) */
extern void FUN_0102fcec(int);
extern void FUN_01035fa0(int, int, int, int, int, int, int, int, int);
extern void FUN_0103b156(int, int);
extern int FUN_0102d558(int);
extern int FUN_0102d5b4(int, int, int);
extern void FUN_01039722(int, ...);

#define C_0102b058 ((uintptr_t)&g_net_subsys_b_ctx) /*=0x2100095c*/
#define C_0102b05c ((uintptr_t)&rodata_102b5ad) /*=0x102b5ad*/
#define C_0102b060 ((uintptr_t)&g_net_heap_a_buf) /*=0x21006cc0*/
#define C_0102b064 ((uintptr_t)&g_net_heap_a_meta) /*=0x21001da0*/
#define C_0102b068 " xpsr:  0x%08x" /*=0x103d088*/
#define C_0102b06c ((uintptr_t)&rodata_102b4f5) /*=0x102b4f5*/
#define C_0102b070 ((uintptr_t)&g_net_heap_b_buf) /*=0x21006480*/
#define C_0102b074 ((uintptr_t)&g_net_heap_b_meta) /*=0x21001d08*/
#define C_0102b078 ((uintptr_t)&rodata_103d095) /*=0x103d095*/
#define C_0102b07c ((uintptr_t)&rodata_103bfac) /*=0x103bfac*/
#define P_0102b080 ((uintptr_t)&g_zephyr_log_level) /*=0x21000580*/
#define C_0102b084 "struction address (r15/pc): 0x%08x" /*=0x103d0a2*/
#define C_0102b088 ((uintptr_t)&g_net_init_cfg_a) /*=0x21004608*/
#define C_0102b08c ((uintptr_t)&g_net_heap_b_cfg) /*=0x2100059c*/
#define C_0102b090 "x%08x" /*=0x103d0bf*/

int FUN_0102afbc(void)
{
  int iVar1;

  FUN_0102fcec(C_0102b058);
  FUN_01035fa0(C_0102b064, C_0102b060, 0x600, C_0102b05c, 0, 0, 0, 0xfffffff7, 0);
  FUN_0103b156(C_0102b064, C_0102b068);
  FUN_01035fa0(C_0102b074, C_0102b070, 0x800, C_0102b06c, 0, 0, 0, 0xfffffff7, 0);
  FUN_0103b156(C_0102b074, C_0102b078);
  iVar1 = FUN_0102d558(C_0102b07c);
  if (iVar1 < 0 && iVar1 != -0x78 && 0 < *(volatile int *)P_0102b080) {
    FUN_01039722(C_0102b084, 0);
  }
  iVar1 = FUN_0102d5b4(C_0102b07c, C_0102b088, C_0102b08c);
  if (iVar1 != 0 && 0 < *(volatile int *)P_0102b080) {
    FUN_01039722(C_0102b090, iVar1);
  }
  return 0;
}

