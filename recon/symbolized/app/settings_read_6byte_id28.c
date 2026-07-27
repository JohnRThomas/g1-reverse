#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007fae4 @ 0x0007fae4
 * public-name: settings_read_6byte_id28
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   audio_codec_reg_op_dispatch              <= FUN_0007f97c @ 0x0007f97c
 *   settings_read_6byte_id28                 <= FUN_0007fae4 @ 0x0007fae4
 */
/* Reconstructed FUN_0007fae4 @ 0x7fae4  (parity: 300/300 trials, PROVEN) */

extern int audio_codec_reg_op_dispatch(unsigned int, unsigned int, void*, unsigned int);
void settings_read_6byte_id28(unsigned int param_1, unsigned short *param_2)
{
  unsigned int local_10 = param_1;
  unsigned int local_c = (unsigned int)param_2;
  audio_codec_reg_op_dispatch(param_1, 0x28, &local_10, 6);
  *(volatile unsigned short *)&param_2[0] = (unsigned short)(local_10 & 0xffff);
  *(volatile unsigned short *)&param_2[1] = (unsigned short)((local_10 >> 16) & 0xffff);
  *(volatile unsigned short *)&param_2[2] = (unsigned short)(local_c & 0xffff);
}
