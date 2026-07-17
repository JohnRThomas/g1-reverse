/* readable reconstruction; identity: FUN_0100bc44 @ 0x0100bc44
 * public-name: FUN_0100bc44
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_radio_addr_match_tbl               @ 0x21000d18
 */
/* net-core FUN_0100bc44 @ 0x100bc44  (parity 300 trials PROVEN) */

void FUN_0100bc44(unsigned char param_1) {
    *(volatile unsigned char *)(0x21000d18 + 0x18b) = param_1;
}
