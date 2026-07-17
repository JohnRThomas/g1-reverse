/* readable reconstruction; identity: FUN_0004bb64 @ 0x0004bb64
 * public-name: FUN_0004bb64
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   rodata_f8a6b                             @ 0x000f8a6b
 */
/* Reconstructed FUN_0004bb64 @ 0x4bb64  (parity: 300/300 trials, PROVEN) */

int FUN_0004bb64(unsigned int *param_1)
{
  int iVar1 = 0;
  unsigned char *pbVar2 = (unsigned char *)*param_1;
  while (1) {
    unsigned char c = *pbVar2;
    unsigned char tbl = *(volatile unsigned char *)(0x000f8a6bUL + c);
    if ((int)((unsigned int)tbl << 0x1d) >= 0) break;
    iVar1 = iVar1*10 + (int)c - 0x30;
    pbVar2 = pbVar2 + 1;
  }
  *param_1 = (unsigned int)pbVar2;
  return iVar1;
}
