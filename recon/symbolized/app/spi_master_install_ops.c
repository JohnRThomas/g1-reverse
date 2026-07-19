#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0002659c @ 0x0002659c
 * public-name: spi_master_install_ops
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   spi_master_install_ops                   <= FUN_0002659c @ 0x0002659c
 * address symbols (name @ address):
 *   ADDR_spi_master_trans_data_tx_rx_THUMB   @ 0x000262ad
 *   ADDR_spim_select_instance_by_mode_THUMB  @ 0x00026339
 *   ADDR_spi_master_init_THUMB               @ 0x00026419
 */
/* Reconstructed FUN_0002659c @ 0x2659c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
void spi_master_install_ops(unsigned int *param_1)
{
  *param_1 = ADDR_spi_master_init_THUMB /*=0x26419*/;
  param_1[2] = ADDR_spi_master_trans_data_tx_rx_THUMB /*=0x262ad*/;
  param_1[1] = ADDR_spim_select_instance_by_mode_THUMB /*=0x26339*/;
  return;
}
