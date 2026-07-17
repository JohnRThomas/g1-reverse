#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00059708 @ 0x00059708
 * public-name: bt_att_req_free
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_att_req_free                          <= FUN_00059708 @ 0x00059708
 *   net_buf_unref                            <= FUN_0005f24c @ 0x0005f24c
 *   k_mem_slab_free                          <= FUN_00071cf4 @ 0x00071cf4
 * address symbols (name @ address):
 *   req_slab                                 @ 0x20003798
 */
/* Reconstructed FUN_00059708 @ 0x59708  (parity: 300/300 trials, PROVEN) */

extern void FUN_0005833c(int a);
extern void net_buf_unref(int a);
extern void k_mem_slab_free(int a, int b);
void bt_att_req_free(int param_1)
{
  if (*(volatile int *)(param_1 + 8) != 0) {
    FUN_0005833c(*(volatile int *)(*(volatile int *)(param_1 + 8) + 0x18));
    net_buf_unref(*(volatile int *)(param_1 + 8));
    *(volatile int *)(param_1 + 8) = 0;
  }
  k_mem_slab_free(((unsigned long)&req_slab) /*=0x20003798*/, param_1);
}
