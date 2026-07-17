/* readable reconstruction; identity: FUN_000875ae @ 0x000875ae
 * public-name: bignum_compare_abs
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bignum_compare_abs                       <= FUN_000875ae @ 0x000875ae
 */
/* Reconstructed FUN_000875ae @ 0x875ae  (parity: 300/300 trials, PROVEN) */

int bignum_compare_abs(int param_1,int param_2)
{
  int iVar1;
  unsigned int *puVar2;
  int iVar3;
  unsigned int *puVar4;

  iVar3 = *(int *)(param_2 + 0x10);
  iVar1 = *(int *)(param_1 + 0x10) - iVar3;
  if (iVar1 == 0) {
    puVar4 = (unsigned int *)(param_1 + 0x14) + iVar3;
    puVar2 = (unsigned int *)(param_2 + 0x14) + iVar3;
    do {
      puVar4 = puVar4 - 1;
      puVar2 = puVar2 - 1;
      if (*puVar4 != *puVar2) {
        if (*puVar4 < *puVar2) return -1;
        return 1;
      }
    } while ((unsigned int *)(param_1 + 0x14) < puVar4);
  }
  return iVar1;
}
