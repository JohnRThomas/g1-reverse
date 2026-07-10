#include "g1_app_symbols.h"
/* named: gpiote_pin_sense_is_enabled */
/* globals referenced:
//   0x20002bc0  g_gpiote_cb                  
*/
/* Reconstructed gpiote_pin_sense_is_enabled @ 0x65478  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int get_pin_idx(void);
unsigned short gpiote_pin_sense_is_enabled(void) {
    int iVar3 = get_pin_idx();
    unsigned short uVar1 = *(volatile uint16_t*)(((uintptr_t)&g_gpiote_cb) /*=0x20002bc0*/ + (uint32_t)((iVar3 + 8) * 2));
    unsigned short uVar2 = uVar1 & 0x1c;
    if ((uVar1 & 0x1c) != 0) {
        uVar2 = 1;
    }
    return uVar2;
}

