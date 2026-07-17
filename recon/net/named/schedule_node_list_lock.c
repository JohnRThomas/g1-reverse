/* readable reconstruction; identity: FUN_0101deac @ 0x0101deac
 * public-name: schedule_node_list_lock
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   schedule_node_list_lock                  <= FUN_0101deac @ 0x0101deac
 * address symbols (name @ address):
 *   g_timeout_list                           @ 0x2100113c
 */
/* net-core FUN_0101deac @ 0x101deac  (parity 300 trials PROVEN) */

void schedule_node_list_lock(void) {
    *(volatile unsigned char *)(0x2100113c + 4) = 1;
}
