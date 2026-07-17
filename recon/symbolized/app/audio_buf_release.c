#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00080b0e @ 0x00080b0e
 * public-name: audio_buf_release
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   net_buf_unref                            <= FUN_0005f24c @ 0x0005f24c
 *   audio_buf_release                        <= FUN_00080b0e @ 0x00080b0e
 */
/* Reconstructed FUN_00080b0e @ 0x80b0e  (parity: 300/300 trials, PROVEN) */

typedef void (*fp_t)(int);
extern void net_buf_unref(int);
void audio_buf_release(int param_1,int param_2)
{
  if (param_1 != 0) {
    fp_t f = *(volatile fp_t *)(param_2 + 0x38);
    if (f != (fp_t)0) {
      f(param_1 + 0x18);
    }
    net_buf_unref(param_1);
  }
}
