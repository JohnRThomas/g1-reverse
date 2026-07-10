/* named: pt_nfc_eeprom_link_start */
/* globals referenced:
//   0x20002408  g_pt_nfc_link_cfg_static     
//   0x20007bcc  g_pt_nfc_link_ready          
*/
/* Reconstructed pt_nfc_eeprom_link_start @ 0x30c90  (parity: 300/300 trials, PROVEN) */

extern int pt_nfc_eeprom_link_init(unsigned int a);

void pt_nfc_eeprom_link_start(void)
{
    int iVar1 = pt_nfc_eeprom_link_init(0x20002408UL);
    if (iVar1 >= 0) {
        *(volatile unsigned int*)0x20007bccUL = 1;
    }
}

