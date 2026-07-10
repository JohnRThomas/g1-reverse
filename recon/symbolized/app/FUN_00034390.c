#include "g1_app_symbols.h"
/* named: FUN_00034390 */
/* globals referenced:
//   0x2001a22a  g_message_pool_index         
*/
/* Reconstructed FUN_00034390 @ 0x34390  (parity: 300/300 trials, PROVEN) */

unsigned char FUN_00034390(void) {
    return *(volatile unsigned char*)((uintptr_t)&g_message_pool_index) /*=0x2001a22a*/;
}

