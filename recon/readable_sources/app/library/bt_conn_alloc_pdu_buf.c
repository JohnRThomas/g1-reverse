#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_net_buf_pool__param_0277               [param_0277; library]
 * Raw function identity: 0x000836de.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_000836de @ 0x000836de
 * public-name: bt_conn_alloc_pdu_buf
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_conn_alloc_pdu_buf                    <= FUN_000836de @ 0x000836de
 */
/* Reconstructed FUN_000836de @ 0x836de  (parity: 300/300 trials, PROVEN) */

extern void net_buf_alloc_len(int, unsigned int, unsigned int, unsigned int); /* FUN_0005eeb4 @ 0x0005eeb4 */

void bt_conn_alloc_pdu_buf(int param_1, unsigned int unused_2,
                   unsigned int param_3, unsigned int param_4)
{
  unsigned int queue = *(volatile unsigned int *)(param_1 + 0x2c);
  unsigned int pending = *(volatile unsigned int *)(queue + 4);
  unsigned int item = *(volatile unsigned int *)pending;

  net_buf_alloc_len(param_1, item, param_3, param_4);
}
