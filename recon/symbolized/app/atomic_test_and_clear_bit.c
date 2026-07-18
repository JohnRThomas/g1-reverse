#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000831be @ 0x000831be
 * public-name: atomic_test_and_clear_bit
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed atomic_test_and_clear_bit @ 0x000831be from atomic.h.
 * Raw backmap: FUN_000831be@0x000831be. */

#include <stdint.h>
#include <stdbool.h>
bool atomic_test_and_clear_bit(volatile int32_t *target,uint32_t bit){uint32_t mask=1u<<bit;return ((uint32_t)__atomic_fetch_and(target,(int32_t)~mask,__ATOMIC_SEQ_CST)&mask)!=0u;}
