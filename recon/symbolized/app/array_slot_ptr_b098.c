#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00060778 @ 0x00060778
 * public-name: array_slot_ptr_b098
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   array_slot_ptr_b098                      <= FUN_00060778 @ 0x00060778
 */
/* Reconstructed FUN_00060778 @ 0x60778  (parity: 300/300 trials, PROVEN) */

unsigned int array_slot_ptr_b098(unsigned int param_1)
{
  unsigned int b = param_1 & 0xffu;
  return 0x2000b098UL + (b << 5);
}
