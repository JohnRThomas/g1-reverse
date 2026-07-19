#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_flash_layout_region__param_0673        [param_0673; G1-original]
 * Raw function identity: 0x00084774.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00084774 @ 0x00084774
 * public-name: layout_select_region
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   flash_page_index_lookup                  <= FUN_00084602 @ 0x00084602
 *   layout_select_region                     <= FUN_00084774 @ 0x00084774
 */
/* Reconstructed FUN_00084774 @ 0x84774  (parity: 300/300 trials, PROVEN) */

extern int flash_page_index_lookup(int *);

int layout_select_region(int *param_1, int param_2)
{
  int diff1 = *(unsigned short *)((char *)param_1 + 10) - *(unsigned short *)((char *)param_1 + 8);
  int formula1 = param_1[1] * diff1 + param_1[0];
  if (formula1 < param_2) {
    int diff2 = *(unsigned short *)((char *)param_1 + 0x16) - *(unsigned short *)((char *)param_1 + 0x14);
    int formula2 = param_1[4] * diff2 + param_1[3];
    if (formula2 < param_2) {
      return 0xffffffea;
    }
    param_1 = param_1 + 3;
  }
  return flash_page_index_lookup(param_1);
}
