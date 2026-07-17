/* readable reconstruction; identity: FUN_00024d50 @ 0x00024d50
 * public-name: FUN_00024d50
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_st25dv_dev                             @ 0x20007a44
 */
/* Reconstructed FUN_00024d50 @ 0x24d50  (parity: 300/300 trials, PROVEN) */

extern void FUN_0007c968(unsigned int, void *, unsigned int, unsigned int, unsigned int);

int FUN_00024d50(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
  int iVar1;
  unsigned int local_c;
  unsigned int uStack_8;

  local_c = param_2;
  uStack_8 = param_3;
  FUN_0007c968(*(volatile unsigned int*)0x20007a44UL,&local_c,param_3,0x20007a44UL,param_1);
  iVar1 = (int)(local_c >> 0x10) + 1;
  return (int)(local_c & 0xff) * iVar1 + iVar1;
}
