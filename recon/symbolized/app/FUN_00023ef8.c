#include "g1_app_symbols.h"
/* named: FUN_00023ef8 */
/* globals referenced:
//   0x20003994  g_flash_store_cmd_msgq       
*/
/* Reconstructed FUN_00023ef8 @ 0x23ef8  (parity: 300/300 trials, PROVEN) */

unsigned int FUN_00023ef8(void) {
    return *(volatile unsigned int*)(((uintptr_t)&g_flash_store_cmd_msgq) /*=0x20003994*/ + 0x24);
}

