#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007fb3e @ 0x0007fb3e
 * public-name: audio_codec_read_reg0x0f
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   audio_codec_reg_op_dispatch              <= FUN_0007f97c @ 0x0007f97c
 *   audio_codec_read_reg0x0f                 <= FUN_0007fb3e @ 0x0007fb3e
 */
/* Reconstructed FUN_0007fb3e @ 0x7fb3e  (parity: 300/300 trials, PROVEN) */

extern void audio_codec_reg_op_dispatch(int a, int b, int c, int d, int e);
void audio_codec_read_reg0x0f(int param_1, int param_2, int param_3, int param_4)
{
  audio_codec_reg_op_dispatch(param_1, 0xf, param_2, 1, param_4);
  return;
}
