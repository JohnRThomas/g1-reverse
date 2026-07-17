/* readable reconstruction; identity: FUN_0101deb8 @ 0x0101deb8
 * public-name: FUN_0101deb8
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_timeout_list                           @ 0x2100113c
 */
/* net-core FUN_0101deb8 @ 0x101deb8  (parity 300 trials PROVEN) */

void FUN_0101deb8(void) {
    *(volatile unsigned char *)(0x2100113c + 4) = 0;
}
