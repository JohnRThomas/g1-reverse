#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00080fba @ 0x00080fba
 * public-name: bt_addr_copy
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_addr_copy                             <= FUN_00080fba @ 0x00080fba
 */
/* Reconstructed FUN_00080fba @ 0x80fba  (parity: 300/300 trials, PROVEN) */

void bt_addr_copy(unsigned int *param_1, unsigned int *param_2)
{
  *param_1 = *param_2;
  *(unsigned short *)((unsigned char*)param_1 + 4) = *(unsigned short *)((unsigned char*)param_2 + 4);
}
