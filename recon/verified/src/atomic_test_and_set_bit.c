/* Reconstructed atomic_test_and_set_bit @ 0x0007f612 from atomic.h.
 * Raw backmap: FUN_0007f612@0x0007f612. */

#include <stdint.h>
#include <stdbool.h>
bool atomic_test_and_set_bit(volatile int32_t *target,uint32_t bit){uint32_t mask=1u<<bit;return ((uint32_t)__atomic_fetch_or(target,(int32_t)mask,__ATOMIC_SEQ_CST)&mask)!=0u;}
