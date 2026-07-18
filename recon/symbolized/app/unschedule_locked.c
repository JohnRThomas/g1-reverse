#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0008656a @ 0x0008656a
 * public-name: unschedule_locked
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed unschedule_locked @ 0x0008656a from Zephyr work.c.
 * Raw backmap: FUN_0008656a@0x0008656a. */

#include <stdint.h>
#ifdef G1_APP_SDK_INLINE_COHESION
/* Exact Zephyr 3.4.99 work.c local owner; raw FUN_00086554 @ 0x00086554. */
static __attribute__((always_inline)) inline uint32_t
flag_test_and_clear(volatile uint32_t *flags, uint32_t bit)
{
 uint32_t old = *flags;
 *flags = old & ~(1u << (bit & 0xffu));
 return (old >> (bit & 0xffu)) & 1u;
}
#else
extern uint32_t flag_test_and_clear(volatile uint32_t *flags,uint32_t bit);
#endif
extern int FUN_00074d74(void *timeout); /* z_abort_timeout */
uint32_t unschedule_locked(void *dwork_arg)
{
 uint8_t *dwork=(uint8_t*)dwork_arg;
 uint32_t ret=flag_test_and_clear((volatile uint32_t*)(dwork+0x0cu),3u);
 if(ret!=0u) ret=(uint32_t)(FUN_00074d74(dwork+0x10u)==0);
 return ret;
}
