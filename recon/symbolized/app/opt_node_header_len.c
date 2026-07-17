#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007c3ea @ 0x0007c3ea
 * public-name: opt_node_header_len
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   opt_node_header_len                      <= FUN_0007c3ea @ 0x0007c3ea
 */
/* Reconstructed FUN_0007c3ea @ 0x7c3ea  (parity: 300/300 trials, PROVEN) */

unsigned char * opt_node_header_len(unsigned char *param_1)
{
  int iVar1;

  if (param_1 != (unsigned char *)0x0) {
    if ((*param_1 & 0x10) == 0) {
      iVar1 = 6;
    }
    else {
      iVar1 = 3;
    }
    if ((int)((unsigned int)*param_1 << 0x1c) < 0) {
      iVar1 = iVar1 + 1;
    }
    param_1 = (unsigned char *)((unsigned int)param_1[1] + (unsigned int)param_1[2] + iVar1);
  }
  return param_1;
}
