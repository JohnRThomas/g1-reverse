/* readable reconstruction; identity: FUN_010217ac @ 0x010217ac
 * public-name: FUN_010217ac
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_radio_frame_desc                   @ 0x21001664
 */
/* net-core FUN_010217ac @ 0x10217ac  (parity 300 trials PROVEN) */

extern void FUN_01008d00(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
void FUN_010217ac(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4) {
  volatile unsigned int *puVar1 = (volatile unsigned int *)0x21001664;
  if (param_3 > 0xfb) {
    FUN_01008d00(0x26, 0x2e6, param_3, param_4, param_4);
    return;
  }
  puVar1[0] = param_2;
  puVar1[1] = param_1;
  *(volatile short *)(puVar1 + 2) = (short)param_3;
}
