#include "g1_app_symbols.h"
/* named: FUN_00023ee0 */
/* globals referenced:
//   0x20018462  g_ui_mode_flag               
*/
/* Reconstructed FUN_00023ee0 @ 0x23ee0  (parity: 300/300 trials, PROVEN) */

unsigned char FUN_00023ee0(void) {
    return *(volatile unsigned char*)(((uintptr_t)&g_ui_mode_flag) /*=0x20018462*/ + 1);
}

