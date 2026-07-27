#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0003dfe4 @ 0x0003dfe4
 * public-name: reset_ipc_evt_ctx
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   reset_ipc_evt_ctx                        <= FUN_0003dfe4 @ 0x0003dfe4
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   g_ipc_or_evt_ctx                         @ 0x20004bb8
 */
/* Reconstructed FUN_0003dfe4 @ 0x3dfe4  (parity: 300/300 trials, PROVEN) */

extern void memset_bytes(void*, int, int);
unsigned int reset_ipc_evt_ctx(void) {
  memset_bytes(((unsigned long)g_ipc_or_evt_ctx) /*=0x20004bb8*/, 0, 0x38);
  return 0;
}
