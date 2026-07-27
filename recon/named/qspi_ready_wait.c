/* readable reconstruction; identity: FUN_0006649c @ 0x0006649c
 * public-name: qspi_ready_wait
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_qspi_cb                                @ 0x2000b348
 *   REG_5002b100                             @ 0x5002b100
 */
/* Reconstructed qspi_ready_wait @ 0x0006649c from pinned nrfx_qspi.c.
 * Raw backmap: FUN_0006649c@0x0006649c. */

#include <stdint.h>
extern void thunk_FUN_00086384(int); /* k_busy_wait thunk */
uint32_t qspi_ready_wait(void)
{
 volatile uint8_t *state=(volatile uint8_t*)0x2000b348u;
 volatile uint32_t *ready=(volatile uint32_t*)0x5002b100u;
 uint32_t attempts=*(volatile uint32_t*)(state+0x34u);
 attempts=attempts ? (attempts*1000u)/10u : 50000u;
 while(*ready==0u && state[0x39u]==0u){thunk_FUN_00086384(10u);if(--attempts==0u)return 0x0bad0007u;}
 return state[0x39u] ? 0x0bad0007u : 0x0bad0000u;
}
