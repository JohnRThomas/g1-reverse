#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00057330 @ 0x00057330
 * public-name: bt_conn_auth_info_cb_register
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_conn_auth_info_cb_register            <= FUN_00057330 @ 0x00057330
 * address symbols (name @ address):
 *   g_bt_conn_auth_info_cb_list              @ 0x2000ad20
 *   auth_info_cbs                            @ 0x2000ad24
 */
/* Reconstructed FUN_00057330 @ 0x57330  (parity: 300/300 trials, PROVEN) */

unsigned int bt_conn_auth_info_cb_register(int param_1)
{
  if (param_1 != 0) {
    *(volatile int *)(param_1 + 0xc) = 0;
    param_1 = param_1 + 0xc;
    if (*(volatile int *)((unsigned long)&auth_info_cbs) /*=0x2000ad24*/ == 0) {
      *(volatile int *)((unsigned long)&g_bt_conn_auth_info_cb_list) /*=0x2000ad20*/ = param_1;
      *(volatile int *)((unsigned long)&auth_info_cbs) /*=0x2000ad24*/ = param_1;
    } else {
      *(volatile int *)(*(volatile int *)((unsigned long)&auth_info_cbs) /*=0x2000ad24*/) = param_1;
      *(volatile int *)((unsigned long)&auth_info_cbs) /*=0x2000ad24*/ = param_1;
    }
    return 0;
  }
  return 0xffffffea;
}
