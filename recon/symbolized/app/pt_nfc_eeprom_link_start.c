#include "g1_app_symbols.h"
/* named: pt_nfc_eeprom_link_start */
/* globals referenced:
//   0x20002408  g_pt_nfc_link_cfg_static     
//   0x20007bcc  g_pt_nfc_link_ready          
*/
/* Reconstructed pt_nfc_eeprom_link_start @ 0x30c90  (parity: 300/300 trials, PROVEN) */

extern int pt_nfc_eeprom_link_init(unsigned int a);

void pt_nfc_eeprom_link_start(void)
{
    int iVar1 = pt_nfc_eeprom_link_init(((uintptr_t)&g_pt_nfc_link_cfg_static) /*=0x20002408*/);
    if (iVar1 >= 0) {
        *(volatile unsigned int*)((uintptr_t)&g_pt_nfc_link_ready) /*=0x20007bcc*/ = 1;
    }
}

