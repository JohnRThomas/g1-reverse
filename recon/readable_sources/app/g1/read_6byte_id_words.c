#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_2          => struct g1_layout_id_words_pair__param_0543              [param_0543; G1-original]
 * Raw function identity: 0x0007faa8.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0007faa8 @ 0x0007faa8
 * public-name: read_6byte_id_words
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   audio_codec_reg_op_dispatch              <= FUN_0007f97c @ 0x0007f97c
 *   read_6byte_id_words                      <= FUN_0007faa8 @ 0x0007faa8
 */
/* Reconstructed FUN_0007faa8 @ 0x7faa8  (parity: 300/300 trials, PROVEN) */

extern int audio_codec_reg_op_dispatch(unsigned int, unsigned int, void*, unsigned int);
void read_6byte_id_words(unsigned int param_1, unsigned short *param_2)
{
  unsigned int local_10 = param_1;
  unsigned int local_c = (unsigned int)param_2;
  audio_codec_reg_op_dispatch(param_1, 0x22, &local_10, 6);
  *(volatile unsigned short *)&param_2[0] = (unsigned short)(local_10 & 0xffff);
  *(volatile unsigned short *)&param_2[1] = (unsigned short)((local_10 >> 16) & 0xffff);
  *(volatile unsigned short *)&param_2[2] = (unsigned short)(local_c & 0xffff);
}
