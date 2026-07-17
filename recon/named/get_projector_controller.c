/* readable reconstruction; identity: FUN_0007d4ec @ 0x0007d4ec
 * public-name: get_projector_controller
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   get_projector_controller                 <= FUN_0007d4ec @ 0x0007d4ec
 */
/* Reconstructed FUN_0007d4ec @ 0x7d4ec  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int get_device_info(void);
int get_projector_controller(void)
{
  int iVar1;
  iVar1 = get_device_info();
  return iVar1 + 0xb6c;
}
