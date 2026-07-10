#include "g1_app_symbols.h"
/* named: getDelayExitValue */
/* globals referenced:
//   0x2000a094  g_delay_exit_value           [g_obj_2000a018.f_7c]
*/
/* Reconstructed getDelayExitValue @ 0x49040  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
uint32_t getDelayExitValue(void) {
    return *(volatile uint32_t*)((uintptr_t)&g_delayexitvalue) /*=0x2000a094*/;
}

