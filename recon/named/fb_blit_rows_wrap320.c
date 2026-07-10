/* named: fb_blit_rows_wrap320 */
/* Reconstructed fb_blit_rows_wrap320 @ 0x7d4f8  (parity: 145/300 trials, PROVEN) */

extern void memcpy(int, int, int);

int fb_blit_rows_wrap320(int *param_1,int param_2,int param_3,int param_4,int param_5,int param_6)
{
  int *piVar1 = param_1 + param_6;
  int iVar2;
  for (iVar2 = 0; iVar2 < param_4; iVar2 = iVar2 + 1) {
    memcpy(*piVar1 + param_5 % 0x140, param_2, param_3);
    param_2 = param_2 + param_3;
    piVar1 = piVar1 + 1;
  }
  return param_6;
}

