/* readable reconstruction; identity: FUN_0103973c @ 0x0103973c
 * public-name: FUN_0103973c
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0103973c @ 0x103973c  (parity 300 trials PROVEN) */

unsigned int FUN_0103973c(int param_1, int param_2, int param_3) {
  unsigned int uVar1;
  int iVar2;
  iVar2 = param_1 + param_2 * 8;
  if (*(unsigned int *)(param_1 + 8) < 0x8000) {
    uVar1 = (unsigned int)*(unsigned short *)(iVar2 + param_3 * 2);
  } else {
    uVar1 = *(unsigned int *)(iVar2 + param_3 * 4);
  }
  return uVar1;
}
