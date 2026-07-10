#include "g1_app_symbols.h"
/* named: bt_conn_auth_info_cb_register */
/* Reconstructed bt_conn_auth_info_cb_register @ 0x57330  (parity: 300/300 trials, PROVEN) */

unsigned int bt_conn_auth_info_cb_register(int param_1)
{
  if (param_1 != 0) {
    *(volatile int *)(param_1 + 0xc) = 0;
    param_1 = param_1 + 0xc;
    if (*(volatile int *)((uintptr_t)&auth_info_cbs) /*=0x2000ad24*/ == 0) {
      *(volatile int *)((uintptr_t)&g_bt_conn_auth_info_cb_list) /*=0x2000ad20*/ = param_1;
      *(volatile int *)((uintptr_t)&auth_info_cbs) /*=0x2000ad24*/ = param_1;
    } else {
      *(volatile int *)(*(volatile int *)((uintptr_t)&auth_info_cbs) /*=0x2000ad24*/) = param_1;
      *(volatile int *)((uintptr_t)&auth_info_cbs) /*=0x2000ad24*/ = param_1;
    }
    return 0;
  }
  return 0xffffffea;
}

