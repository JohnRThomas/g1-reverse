#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00084ade @ 0x00084ade
 * public-name: uarte_nrfx_tx_complete
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   audio_dma_start_transfer                 <= FUN_0008496c @ 0x0008496c
 *   is_tx_ready                              <= FUN_00084abe @ 0x00084abe
 *   uarte_nrfx_tx_complete                   <= FUN_00084ade @ 0x00084ade
 */
/* Reconstructed FUN_00084ade @ 0x84ade  (parity: 300/300 trials, PROVEN) */

extern long long is_tx_ready(unsigned int);
extern void audio_dma_start_transfer(unsigned int, unsigned int, unsigned int);

void uarte_nrfx_tx_complete(unsigned int param_1)
{
  long long uVar2;
  int iVar1;
  int field;
  uVar2 = is_tx_ready(*(unsigned int *)(param_1 + 4));
  iVar1 = (int)(uVar2 >> 32);
  field = *(int *)(iVar1 + 0xc);
  if ((int)uVar2 == 0) {
    *(unsigned char *)(field + 0xcd) = 1;
    return;
  }
  *(unsigned char *)(field + 0xcd) = 0;
  *(unsigned int *)(field + 0xbc) = 0xffffffff;
  audio_dma_start_transfer(param_1, *(unsigned int *)(field + 0x10), *(unsigned int *)(field + 0x14));
}
