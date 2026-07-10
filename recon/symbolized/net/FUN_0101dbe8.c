#include "g1_net_symbols.h"
/* net-core FUN_0101dbe8 @ 0x101dbe8  (parity 300 trials PROVEN) */

void FUN_0101dbe8(void) {
  *(volatile unsigned int *)(((uintptr_t)&g_net_link_ctx_a_vtable) /*=0x21000354*/ + 0x50) = ((uintptr_t)&rodata_10103bd) /*=0x10103bd*/;
  *(volatile unsigned int *)(((uintptr_t)&g_net_link_ctx_a_vtable) /*=0x21000354*/ + 0x54) = ((uintptr_t)&rodata_1010305) /*=0x1010305*/;
  *(volatile unsigned int *)(((uintptr_t)&g_net_link_ctx_b_vtable) /*=0x21000400*/ + 0x50) = ((uintptr_t)&rodata_10102c1) /*=0x10102c1*/;
  *(volatile unsigned int *)(((uintptr_t)&g_net_link_ctx_b_vtable) /*=0x21000400*/ + 0x54) = ((uintptr_t)&rodata_101cae5) /*=0x101cae5*/;
}

