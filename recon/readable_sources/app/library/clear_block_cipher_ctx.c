#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007ab20 @ 0x0007ab20
 * public-name: clear_block_cipher_ctx
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   clear_block_cipher_ctx                   <= FUN_0007ab20 @ 0x0007ab20
 */
/* Reconstructed FUN_0007ab20 @ 0x7ab20  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void thunk_FUN_00086c78(int,int,int);
void clear_block_cipher_ctx(int param_1)
{
  if (param_1 != 0) {
    thunk_FUN_00086c78(param_1,0,0x74);
    return;
  }
  return;
}
