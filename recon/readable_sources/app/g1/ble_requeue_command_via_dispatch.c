#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007c244 @ 0x0007c244
 * public-name: ble_requeue_command_via_dispatch
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ancs_get_conn_ctx                        <= FUN_000181fc @ 0x000181fc
 *   ble_process_req_dispatch                 <= FUN_00021460 @ 0x00021460
 *   ble_requeue_command_via_dispatch         <= FUN_0007c244 @ 0x0007c244
 */
/* Reconstructed FUN_0007c244 @ 0x7c244  (parity: 300/300 trials, PROVEN) */

extern int ancs_get_conn_ctx(void);
extern void ble_process_req_dispatch(unsigned int a, void *b, void *c, unsigned int d, void *e);

void ble_requeue_command_via_dispatch(unsigned char *param_1, unsigned int param_2, unsigned int param_3)
{
  unsigned char *puVar2 = param_1;
  unsigned int uStack_10 = param_3;
  (void)uStack_10;
  unsigned int uVar1 = ancs_get_conn_ctx();
  struct { unsigned char b0; unsigned char b1; unsigned short h; } loc;
  loc.b0 = *param_1;
  loc.b1 = 1;
  loc.h = (unsigned short)param_2;
  ble_process_req_dispatch(uVar1, &loc, param_1, 1, puVar2);
}
