#include "g1_app_symbols.h"
/* named: FUN_00023eec */
/* globals referenced:
//   0x20018462  g_ui_mode_flag               
*/
/* Reconstructed FUN_00023eec @ 0x23eec  (parity: 300/300 trials, PROVEN) */

unsigned char FUN_00023eec(void) {
    return *(volatile unsigned char*)(((uintptr_t)&g_ui_mode_flag) /*=0x20018462*/ + 2);
}

