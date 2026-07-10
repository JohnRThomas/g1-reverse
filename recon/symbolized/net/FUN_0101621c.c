#include "g1_net_symbols.h"
/* net-core FUN_0101621c @ 0x101621c  (parity 300 trials PROVEN) */

void FUN_0101621c(void) {
  *(volatile unsigned int *)(((uintptr_t)&g_net_ble_role_cfg_a) /*=0x21000078*/ + 0x58) = ((uintptr_t)&rodata_102a1bf) /*=0x102a1bf*/;
  *(volatile unsigned int *)(((uintptr_t)&g_net_ble_role_cfg_a) /*=0x21000078*/ + 0x60) = ((uintptr_t)&rodata_1020195) /*=0x1020195*/;
  *(volatile unsigned int *)(((uintptr_t)&g_net_ble_role_cfg_b) /*=0x21000124*/ + 0x58) = ((uintptr_t)&rodata_1029ef9) /*=0x1029ef9*/;
  *(volatile unsigned int *)(((uintptr_t)&g_net_ble_role_cfg_b) /*=0x21000124*/ + 0x5c) = ((uintptr_t)&rodata_1015091) /*=0x1015091*/;
}

