#include "g1_app_symbols.h"
/* named: FUN_00024678 */
/* globals referenced:
//   0x20003960  g_quicknote_flash_msgq       
*/
/* Reconstructed FUN_00024678 @ 0x24678  (parity: 300/300 trials, PROVEN) */

unsigned int FUN_00024678(void) {
    return *(volatile unsigned int*)(((uintptr_t)&g_quicknote_flash_msgq) /*=0x20003960*/ + 0x24);
}

