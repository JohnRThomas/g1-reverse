#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_bt_att_chan_view__param_0182           [param_0182; library]
 * Raw function identity: 0x00080c7c.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00080c7c @ 0x00080c7c
 * public-name: att_get_max_payload_len
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   att_get_max_payload_len                  <= FUN_00080c7c @ 0x00080c7c
 */
/* Reconstructed FUN_00080c7c @ 0x80c7c  (parity: 300/300 trials, PROVEN) */

extern unsigned int thunk_FUN_000823fa(void);
unsigned int att_get_max_payload_len(unsigned char *param_1) {
  unsigned int v = *(unsigned int*)(param_1 + 0x18);
  if (v != 0) {
    unsigned int r = thunk_FUN_000823fa();
    v = (r - 3) & 0xffff;
  }
  return v;
}
