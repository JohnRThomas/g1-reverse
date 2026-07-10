/* named: stop_some_timer */
/* globals referenced:
//   0x20004ce0  g_some_k_timer               
*/
/* Reconstructed stop_some_timer @ 0x48ff4  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void z_impl_k_timer_stop(uint32_t);
void stop_some_timer(void) {
    z_impl_k_timer_stop(0x20004ce0UL);
}

