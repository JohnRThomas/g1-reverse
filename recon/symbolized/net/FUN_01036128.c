#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01036128 @ 0x01036128
 * public-name: FUN_01036128
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01036128 @ 0x1036128  (parity 300 trials PROVEN) */

struct kernel_lock_state {
  unsigned int reserved[2];
  unsigned int owner;
  unsigned char padding[4];
  unsigned char nested;
};

int FUN_01036128(unsigned int *lock) {
  volatile struct kernel_lock_state *state =
      (volatile struct kernel_lock_state *)0x21004b28u;
  unsigned int expected = state->owner | state->nested;
  int released = (*lock == expected);
  if (released) {
    *lock = 0;
  }
  return released;
}
