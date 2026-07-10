#include "g1_app_symbols.h"
/* named: get_dmic_msgq_count */
/* globals referenced:
//   0x20007b7c  g_dmic_msgq                  
*/
/* Reconstructed get_dmic_msgq_count @ 0x2ecf4  (parity: 300/300 trials, PROVEN) */

unsigned int get_dmic_msgq_count(void) {
    return *(volatile unsigned int*)(((uintptr_t)&g_dmic_msgq) /*=0x20007b7c*/ + 0x24);
}

