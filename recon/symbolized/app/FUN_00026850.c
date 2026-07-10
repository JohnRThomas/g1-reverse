#include "g1_app_symbols.h"
/* named: FUN_00026850 */
/* Reconstructed FUN_00026850 @ 0x26850  (parity: 300/300 trials, PROVEN) */

extern void k_mutex_unlock(unsigned int);
void FUN_00026850(void) {
    k_mutex_unlock(((uintptr_t)&g_ui_state_mutex) /*=0x20007b3c*/);
}

