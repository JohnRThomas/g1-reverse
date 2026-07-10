#include "g1_app_symbols.h"
/* named: FUN_000269fc */
/* Reconstructed FUN_000269fc @ 0x269fc  (parity: 300/300 trials, PROVEN) */

unsigned char FUN_000269fc(void) {
    return *(volatile unsigned char*)((uintptr_t)&g_last_standby_event_id) /*=0x2000302d*/;
}

