#include "g1_app_symbols.h"
/* named: FUN_0002f758 */
/* globals referenced:
//   0x20003890  g_audio_msgq                 
*/
/* Reconstructed FUN_0002f758 @ 0x2f758  (parity: 300/300 trials, PROVEN) */

unsigned int FUN_0002f758(void) {
    return *(volatile unsigned int*)(((uintptr_t)&g_audio_msgq) /*=0x20003890*/ + 0x24);
}

