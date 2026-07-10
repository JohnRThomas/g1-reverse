/* named: bt_att_req_free */
/* globals referenced:
//   0x20003798  req_slab                     
*/
/* Reconstructed bt_att_req_free @ 0x59708  (parity: 300/300 trials, PROVEN) */

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
  k_mem_slab_free(0x20003798, param_1);
}

