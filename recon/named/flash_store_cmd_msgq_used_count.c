/* readable reconstruction; identity: FUN_00023ef8 @ 0x00023ef8
 * public-name: flash_store_cmd_msgq_used_count
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   flash_store_cmd_msgq_used_count          <= FUN_00023ef8 @ 0x00023ef8
 * address symbols (name @ address):
 *   g_flash_store_cmd_msgq                   @ 0x20003994
 */
/* Reconstructed FUN_00023ef8 @ 0x23ef8  (parity: 300/300 trials, PROVEN) */

unsigned int flash_store_cmd_msgq_used_count(void) {
    return *(volatile unsigned int*)(0x20003994UL + 0x24);
}
