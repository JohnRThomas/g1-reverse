/* readable reconstruction; identity: FUN_0100e7b8 @ 0x0100e7b8
 * public-name: FUN_0100e7b8
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0100e7b8 @ 0x100e7b8  (parity 300 trials PROVEN) */

void FUN_0100e7b8(int param_1, unsigned int param_2) {
    *(char *)(param_1 + 6) = (char)param_2;
    *(char *)(param_1 + 7) = (char)(param_2 >> 8);
}
