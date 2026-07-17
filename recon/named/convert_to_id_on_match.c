/* readable reconstruction; identity: FUN_000831e2 @ 0x000831e2
 * public-name: convert_to_id_on_match
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   convert_to_id_on_match                   <= FUN_000831e2 @ 0x000831e2
 */
/* Reconstructed FUN_000831e2 @ 0x831e2  (parity: 300/300 trials, PROVEN) */

extern int FUN_00086be4(int a, int b, int c);
extern void FUN_00083062(int a, int b);
void convert_to_id_on_match(int param_1, int *param_2)
{
  int iVar1;
  iVar1 = FUN_00086be4(param_1 + 0x90, *param_2, 7);
  if (iVar1 == 0) {
    FUN_00083062(param_1 + 0x90, param_2[1]);
  }
}
