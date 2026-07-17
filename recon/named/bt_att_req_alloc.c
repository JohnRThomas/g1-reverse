/* readable reconstruction; identity: FUN_000596c0 @ 0x000596c0
 * public-name: bt_att_req_alloc
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_att_req_alloc                         <= FUN_000596c0 @ 0x000596c0
 *   k_mem_slab_alloc                         <= FUN_00071c20 @ 0x00071c20
 *   k_current_get                            <= FUN_000748ac @ 0x000748ac
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   req_slab                                 @ 0x20003798
 *   att_handle_rsp_thread                    @ 0x2000ae9c
 */
/* Reconstructed FUN_000596c0 @ 0x596c0  (parity: 300/300 trials, PROVEN) */

extern int k_current_get(void);
extern int k_mem_slab_alloc(int a, int *b, int c, int d, int e);
extern int memset_bytes(int a, int b, int c);

int bt_att_req_alloc(int param_1, int param_2, int param_3)
{
  int iVar1;
  int uVar2;
  int local_14 = 0;

  uVar2 = param_1;
  iVar1 = k_current_get();
  if (*(volatile int*)0x2000ae9cUL == iVar1) {
    param_2 = 0;
    param_1 = param_2;
  }
  iVar1 = k_mem_slab_alloc(0x20003798, &local_14, param_1, param_2, uVar2);
  if (iVar1 == 0) {
    uVar2 = memset_bytes(local_14, 0, 0x1c);
  } else {
    uVar2 = 0;
  }
  return uVar2;
}
