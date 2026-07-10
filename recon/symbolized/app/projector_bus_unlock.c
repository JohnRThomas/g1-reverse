#include "g1_app_symbols.h"
/* named: projector_bus_unlock */
/* globals referenced:
//   0x2000a060  g_projector_bus_lock         
*/
/* Reconstructed projector_bus_unlock @ 0x476a8  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void k_mutex_unlock(uint32_t);
void projector_bus_unlock(void) {
    k_mutex_unlock(((uintptr_t)&g_projector_bus_lock) /*=0x2000a060*/);
}

