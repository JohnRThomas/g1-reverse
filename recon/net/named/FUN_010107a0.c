/* readable reconstruction; identity: FUN_010107a0 @ 0x010107a0
 * public-name: FUN_010107a0
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_lookup_table_desc                  @ 0x21000f14
 */
/* net-core FUN_010107a0 @ 0x10107a0  (parity 300 trials PROVEN) */

void FUN_010107a0(void) {
    *(volatile unsigned char *)0x21000f14 = 0;
}
