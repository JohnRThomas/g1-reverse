/* readable reconstruction; identity: FUN_000849da @ 0x000849da
 * public-name: nvs_timer_arm_and_mark_dirty
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nvs_timer_arm_and_mark_dirty             <= FUN_000849da @ 0x000849da
 *   z_impl_k_timer_stop                      <= FUN_0008673e @ 0x0008673e
 */
/* Reconstructed FUN_000849da @ 0x849da  (parity: 300/300 trials, PROVEN) */

extern void z_impl_k_timer_stop(int a, unsigned int b, int c, int d, unsigned int e);
unsigned int nvs_timer_arm_and_mark_dirty(int param_1,unsigned int param_2,unsigned int param_3,unsigned int param_4)
{
  unsigned int uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;

  iVar5 = *(int *)(param_1 + 0x10);
  iVar4 = **(int **)(param_1 + 4);
  iVar2 = *(int *)(*(int *)(iVar5 + 0xc) + 0x58);
  if (iVar2 == 0) {
    uVar1 = 0xfffffff2;
  } else {
    iVar3 = *(int *)(*(int *)(iVar5 + 0xc) + 100);
    if (iVar3 != 0) {
      *(unsigned int *)(iVar4 + 0x200) = *(unsigned int *)(iVar4 + 0x200) & 0xffffffdf;
      *(unsigned int *)(iVar4 + 0x14c) = 0;
      iVar3 = *(int *)(iVar4 + 0x14c);
    }
    z_impl_k_timer_stop(*(int *)(iVar5 + 0xc) + 0x80,param_2,iVar2,iVar3,param_4);
    uVar1 = 0;
    *(unsigned char *)(*(int *)(iVar5 + 0xc) + 0xca) = 0;
    *(unsigned char *)(*(int *)(iVar5 + 0xc) + 0xcb) = 1;
    *(unsigned int *)(iVar4 + 4) = 1;
  }
  return uVar1;
}
