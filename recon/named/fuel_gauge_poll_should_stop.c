/* readable reconstruction; identity: FUN_00030cac @ 0x00030cac
 * public-name: fuel_gauge_poll_should_stop
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   fuel_gauge_poll_should_stop              <= FUN_00030cac @ 0x00030cac
 * address symbols (name @ address):
 *   g_fuel_gauge_poll_stop_flag              @ 0x20019dae
 */
/* Reconstructed FUN_00030cac @ 0x30cac  (parity: 300/300 trials, PROVEN) */

unsigned char fuel_gauge_poll_should_stop(void) {
    return *(volatile unsigned char*)0x20019daeUL;
}
