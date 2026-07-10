#include "g1_app_symbols.h"
/* named: FUN_00034410 */
/* Reconstructed FUN_00034410 @ 0x34410  (parity: 300/300 trials, PROVEN) */

unsigned char FUN_00034410(void) {
    return *(volatile unsigned char*)((uintptr_t)&g_message_pending_state) /*=0x2001a229*/;
}

