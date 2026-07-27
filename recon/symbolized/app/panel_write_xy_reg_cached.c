#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00047028 @ 0x00047028
 * public-name: panel_write_xy_reg_cached
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   panel_write_xy_reg_cached                <= FUN_00047028 @ 0x00047028
 *   projector_send_cmd_0x46                  <= FUN_0007d67e @ 0x0007d67e
 *   net_pkt_write_be16                       <= FUN_0007d696 @ 0x0007d696
 * address symbols (name @ address):
 *   g_panel_reg_y_cache                      @ 0x2000a058
 *   g_panel_reg_x_cache                      @ 0x2000a05c
 */
/* Reconstructed FUN_00047028 @ 0x47028  (parity: 300/300 trials, PROVEN) */

extern void projector_send_cmd_0x46(int a0);
extern void net_pkt_write_be16(unsigned int);

void panel_write_xy_reg_cached(int param_1, int param_2)
{
  volatile int *piVar1;
  piVar1 = (volatile int *)((unsigned long)&g_panel_reg_x_cache) /*=0x2000a05c*/;
  if (param_1 != *piVar1) {
    net_pkt_write_be16(param_1);
    *piVar1 = param_1;
  }
  piVar1 = (volatile int *)((unsigned long)&g_panel_reg_y_cache) /*=0x2000a058*/;
  if (param_2 != *piVar1) {
    projector_send_cmd_0x46(param_2);
    *piVar1 = param_2;
  }
}
