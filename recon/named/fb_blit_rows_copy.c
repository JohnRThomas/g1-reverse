/* readable reconstruction; identity: FUN_0007d53a @ 0x0007d53a
 * public-name: fb_blit_rows_copy
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   fb_blit_rows_copy                        <= FUN_0007d53a @ 0x0007d53a
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 */
/* Reconstructed FUN_0007d53a @ 0x7d53a  (parity: 145/300 trials, PROVEN) */

extern void memcpy(int a, int b, int c);
int fb_blit_rows_copy(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6)
{
  int *piVar1;
  int iVar2;

  if (199 < param_6) {
    param_6 = 200;
  }
  if (0x27f < param_5) {
    param_5 = 0x280;
  }
  piVar1 = (int *)(param_1 + param_6 * 4);
  for (iVar2 = 0; iVar2 < param_4; iVar2 = iVar2 + 1) {
    memcpy(*piVar1 + param_5 / 2,param_2,param_3);
    param_2 = param_2 + param_3;
    piVar1 = piVar1 + 1;
  }
  return param_6;
}
