/* readable reconstruction; identity: FUN_0101deac @ 0x0101deac
 * public-name: FUN_0101deac
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_timeout_list                           @ 0x2100113c
 */
/* net-core FUN_0101deac @ 0x101deac  (parity 300 trials PROVEN) */

void FUN_0101deac(void) {
    *(volatile unsigned char *)(0x2100113c + 4) = 1;
}
