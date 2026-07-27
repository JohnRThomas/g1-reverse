#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_bt_smp__param_0265                     [param_0265; library]
 * Raw function identity: 0x000830ee.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_000830ee @ 0x000830ee
 * public-name: send_pairing_rsp
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_smp_send_pdu                          <= FUN_0005cb38 @ 0x0005cb38
 *   net_buf_simple_add                       <= FUN_0005f5d0 @ 0x0005f5d0
 *   smp_create_pdu                           <= FUN_000830b0 @ 0x000830b0
 *   send_pairing_rsp                         <= FUN_000830ee @ 0x000830ee
 */
/* Reconstructed FUN_000830ee @ 0x830ee  (parity: 300/300 trials, PROVEN) */

extern int smp_create_pdu(int, int, unsigned int, unsigned int, unsigned int);
extern void *net_buf_simple_add(int, int);
extern void bt_smp_send_pdu(int, unsigned int, unsigned int);

unsigned int send_pairing_rsp(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  int iVar1;
  unsigned int *puVar2;
  unsigned int uVar3;
  iVar1 = smp_create_pdu(param_1, 2, param_3, param_4, param_4);
  if (iVar1 == 0) {
    uVar3 = 8;
  } else {
    puVar2 = (unsigned int *)net_buf_simple_add(iVar1 + 0xc, 6);
    *puVar2 = *(unsigned int *)(param_1 + 0x11);
    *(unsigned short *)(puVar2 + 1) = *(unsigned short *)(param_1 + 0x15);
    bt_smp_send_pdu(param_1, iVar1, 0);
    uVar3 = 0;
  }
  return uVar3;
}
