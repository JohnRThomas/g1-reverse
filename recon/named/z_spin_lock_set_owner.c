/* readable reconstruction; identity: FUN_00072078 @ 0x00072078
 * public-name: z_spin_lock_set_owner
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 * address symbols (name @ address):
 *   _kernel                                  @ 0x2000b448
 */
/* Reconstructed FUN_00072078 @ 0x72078  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
void z_spin_lock_set_owner(unsigned int *param_1)
{
  *param_1 = *(volatile uint32_t*)(0x2000b448UL + 8) | (unsigned int)*(volatile uint8_t*)(0x2000b448UL + 0x10);
  return;
}
