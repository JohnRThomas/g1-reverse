#include "g1_net_symbols.h"
/* net-core FUN_010161e8 @ 0x10161e8  (parity 300 trials PROVEN) */

void FUN_010161e8(void) {
  *(volatile unsigned int *)(((uintptr_t)&g_net_ble_role_cfg_a) /*=0x21000078*/ + 0x50) = ((uintptr_t)&rodata_1015241) /*=0x1015241*/;
  *(volatile unsigned int *)(((uintptr_t)&g_net_ble_role_cfg_a) /*=0x21000078*/ + 0x54) = ((uintptr_t)&rodata_1010305) /*=0x1010305*/;
  *(volatile unsigned int *)(((uintptr_t)&g_net_ble_role_cfg_b) /*=0x21000124*/ + 0x50) = ((uintptr_t)&rodata_10102c1) /*=0x10102c1*/;
  *(volatile unsigned int *)(((uintptr_t)&g_net_ble_role_cfg_b) /*=0x21000124*/ + 0x54) = ((uintptr_t)&rodata_1015201) /*=0x1015201*/;
}

