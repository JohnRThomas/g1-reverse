#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00059c48 @ 0x00059c48
 * public-name: ccc_match_conn_cfg
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ccc_match_conn_cfg                       <= FUN_00059c48 @ 0x00059c48
 *   bt_conn_is_peer_addr_le                  <= FUN_000814e6 @ 0x000814e6
 *   bt_addr_le_eq_0                          <= FUN_000826b2 @ 0x000826b2
 * address symbols (name @ address):
 *   rodata_f2b3a                             @ 0x000f2b3a
 */
/* Reconstructed FUN_00059c48 @ 0x59c48  (parity: 300/300 trials, PROVEN) */

extern int bt_conn_is_peer_addr_le(int a, unsigned char b);
extern int bt_addr_le_eq_0(void*, unsigned int);
unsigned char *ccc_match_conn_cfg(int param_1, unsigned char *param_2)
{
  int iVar1;

  if (param_1 == 0) {
    iVar1 = bt_addr_le_eq_0(param_2 + 1, ((unsigned long)&rodata_f2b3a) /*=0xf2b3a*/);
  } else {
    iVar1 = bt_conn_is_peer_addr_le(param_1, *param_2);
  }
  if (iVar1 == 0) {
    param_2 = (unsigned char *)0;
  }
  return param_2;
}
