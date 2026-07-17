/* readable reconstruction; identity: FUN_0101deb8 @ 0x0101deb8
 * public-name: schedule_node_list_unlock
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   schedule_node_list_unlock                <= FUN_0101deb8 @ 0x0101deb8
 * address symbols (name @ address):
 *   g_timeout_list                           @ 0x2100113c
 */
/* net-core FUN_0101deb8 @ 0x101deb8  (parity 300 trials PROVEN) */

void schedule_node_list_unlock(void) {
    *(volatile unsigned char *)(0x2100113c + 4) = 0;
}
