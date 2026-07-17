#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0002f758 @ 0x0002f758
 * public-name: FUN_0002f758
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_audio_msgq                             @ 0x20003890
 */
/* Reconstructed FUN_0002f758 @ 0x2f758  (parity: 300/300 trials, PROVEN) */

unsigned int FUN_0002f758(void) {
    return *(volatile unsigned int*)(((unsigned long)&g_audio_msgq) /*=0x20003890*/ + 0x24);
}
