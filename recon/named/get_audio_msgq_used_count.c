/* readable reconstruction; identity: FUN_0002f758 @ 0x0002f758
 * public-name: get_audio_msgq_used_count
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_audio_msgq_used_count                <= FUN_0002f758 @ 0x0002f758
 * address symbols (name @ address):
 *   g_audio_msgq                             @ 0x20003890
 */
/* Reconstructed FUN_0002f758 @ 0x2f758  (parity: 300/300 trials, PROVEN) */

unsigned int get_audio_msgq_used_count(void) {
    return *(volatile unsigned int*)(0x20003890UL + 0x24);
}
