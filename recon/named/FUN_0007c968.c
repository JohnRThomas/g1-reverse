/* readable reconstruction; identity: FUN_0007c968 @ 0x0007c968
 * public-name: FUN_0007c968
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ipc_ept_op_b_locked_retry                <= FUN_000257ec @ 0x000257ec
 */
/* Reconstructed FUN_0007c968 @ 0x7c968  (parity: 300/300 trials, PROVEN) */

extern int ipc_ept_op_b_locked_retry(unsigned int, unsigned int, void *, unsigned int);

int FUN_0007c968(unsigned int param_1, unsigned int *param_2, unsigned int param_3)
{
  int iVar1;
  unsigned short local_14 = 0;
  if (param_2 == 0) {
    iVar1 = -0x16;
  } else {
    iVar1 = ipc_ept_op_b_locked_retry(param_1, 0x14, &local_14, 2);
    if (iVar1 == 0) {
      *(unsigned short *)((char *)param_2 + 2) = local_14;
      iVar1 = ipc_ept_op_b_locked_retry(param_1, 0x16, (void *)param_2, 1);
    }
  }
  return iVar1;
}
