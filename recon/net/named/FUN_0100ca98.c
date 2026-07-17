/* readable reconstruction; identity: FUN_0100ca98 @ 0x0100ca98
 * public-name: FUN_0100ca98
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_radio_addr_match_tbl               @ 0x21000d18
 */
/* net-core FUN_0100ca98 @ 0x100ca98  (parity 300 trials PROVEN) */

unsigned int FUN_0100ca98(unsigned int param_1, unsigned char *param_2, unsigned int *param_3)
{
  unsigned int iVar2 = 0x21000d18;
  if (*(unsigned char*)(iVar2+1) <= param_1) return 0;
  unsigned int iVar1 = (unsigned int)(*(unsigned char*)(param_1 + iVar2 + 0x102)) * 7;
  unsigned int iVar3 = iVar1 + 0x153;
  *param_2 = *(unsigned char*)(iVar2 + iVar1 + 0x152);
  *param_3 = *(unsigned int*)(iVar2 + iVar3);
  *(unsigned short*)(param_3+1) = *(unsigned short*)(iVar2 + iVar3 + 4);
  return 1;
}
