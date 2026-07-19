#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00024678 @ 0x00024678
 * public-name: quicknote_flash_msgq_read_field24
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   quicknote_flash_msgq_read_field24        <= FUN_00024678 @ 0x00024678
 * address symbols (name @ address):
 *   g_quicknote_flash_msgq                   @ 0x20003960
 */
/* Reconstructed FUN_00024678 @ 0x24678  (parity: 300/300 trials, PROVEN) */

unsigned int quicknote_flash_msgq_read_field24(void) {
    return *(volatile unsigned int*)(((unsigned long)&g_quicknote_flash_msgq) /*=0x20003960*/ + 0x24);
}
