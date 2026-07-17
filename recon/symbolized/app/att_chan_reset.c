#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00083204 @ 0x00083204
 * public-name: att_chan_reset
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   atomic_set_bit                           <= FUN_00083090 @ 0x00083090
 *   att_chan_reset                           <= FUN_00083204 @ 0x00083204
 */
/* Reconstructed FUN_00083204 @ 0x83204  (parity: 300/300 trials, PROVEN) */

extern void FUN_00073518(unsigned int *, unsigned int, unsigned int,
                         unsigned int *exchange_word);
extern void atomic_set_bit(unsigned int *, unsigned int);

void att_chan_reset(unsigned int *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned int uVar1 = __atomic_exchange_n(param_1 + 1, 0,
                                            __ATOMIC_ACQ_REL);
  FUN_00073518(param_1 + 0x82, 0, uVar1, param_1 + 1);
  *(volatile unsigned char *)(param_1 + 2) = 0;
  (void)__atomic_exchange_n(param_1, 0, __ATOMIC_ACQ_REL);
  atomic_set_bit(param_1, 1);
}
