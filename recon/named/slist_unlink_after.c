/* readable reconstruction; identity: FUN_000815f6 @ 0x000815f6
 * public-name: slist_unlink_after
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   slist_unlink_after                       <= FUN_000815f6 @ 0x000815f6
 */
/* Reconstructed FUN_000815f6 @ 0x815f6  (parity: 300/300 trials, PROVEN) */

void slist_unlink_after(unsigned int *param_1,unsigned int *param_2,unsigned int *param_3)
{
  unsigned int uVar1;
  uVar1 = *param_3;
  if (param_2 == (unsigned int*)0) {
    *param_1 = uVar1;
    if (param_3 == (unsigned int*)param_1[1]) {
      param_1[1] = uVar1;
    }
  } else {
    *param_2 = uVar1;
    if (param_3 == (unsigned int*)param_1[1]) {
      param_1[1] = (unsigned int)param_2;
    }
  }
  *param_3 = 0;
  return;
}
