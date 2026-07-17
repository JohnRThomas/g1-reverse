/* readable reconstruction; identity: FUN_0100a578 @ 0x0100a578
 * public-name: FUN_0100a578
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_retry_handle                       @ 0x21000bc4
 *   g_net_retry_param2                       @ 0x21000bc8
 *   g_sdc_last_cfg_param3                    @ 0x21000bc9
 */
/* net-core FUN_0100a578 @ 0x100a578  (parity 300 trials PROVEN) */

extern void FUN_0100a50c(unsigned int, unsigned char, unsigned char);
void FUN_0100a578(void) {
  volatile unsigned int *DAT_0100a594 = (volatile unsigned int *)0x21000bc4;
  volatile unsigned char *DAT_0100a598 = (volatile unsigned char *)0x21000bc8;
  volatile unsigned char *DAT_0100a59c = (volatile unsigned char *)0x21000bc9;
  FUN_0100a50c(*DAT_0100a594, *DAT_0100a598, *DAT_0100a59c);
}
