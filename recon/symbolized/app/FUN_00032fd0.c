#include "g1_app_symbols.h"
/* named: FUN_00032fd0 */
/* Reconstructed FUN_00032fd0 @ 0x32fd0  (parity: 300/300 trials, PROVEN) */

void FUN_00032fd0(unsigned char param_1) {
    *(volatile unsigned char*)((uintptr_t)&g_click_dispatch_flag) /*=0x20019ef2*/ = param_1;
}

