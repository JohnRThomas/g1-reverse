#include "g1_app_symbols.h"
/* named: FUN_000370b0 */
/* Reconstructed FUN_000370b0 @ 0x370b0  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
uint8_t FUN_000370b0(void) {
    return *(volatile uint8_t*)((uintptr_t)&g_dashboard_disp_mode) /*=0x2000496a*/;
}

