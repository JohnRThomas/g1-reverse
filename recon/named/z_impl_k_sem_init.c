/* readable reconstruction; identity: FUN_00086534 @ 0x00086534
 * public-name: z_impl_k_sem_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_impl_k_sem_init                        <= FUN_00086534 @ 0x00086534
 */
/* Reconstructed FUN_00086534 @ 0x86534  (parity: 300/300 trials, PROVEN) */

int z_impl_k_sem_init(unsigned int param_1, unsigned long param_2, unsigned long param_3) {
  if ((param_3 != 0) && (param_2 <= param_3)) {
    *(unsigned int *)(param_1 + 8) = param_2;
    *(unsigned int *)(param_1 + 0xc) = param_3;
    *(int *)param_1 = param_1;
    *(int *)(param_1 + 4) = param_1;
    *(int *)(param_1 + 0x10) = param_1 + 0x10;
    *(int *)(param_1 + 0x14) = param_1 + 0x10;
    return 0;
  }
  return 0xffffffea;
}
