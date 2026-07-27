/* readable reconstruction; identity: FUN_00030c90 @ 0x00030c90
 * public-name: pt_nfc_eeprom_link_start
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   pt_nfc_eeprom_link_init                  <= FUN_00030b3c @ 0x00030b3c
 *   pt_nfc_eeprom_link_start                 <= FUN_00030c90 @ 0x00030c90
 * address symbols (name @ address):
 *   g_pt_nfc_link_cfg_static                 @ 0x20002408
 *   g_pt_nfc_link_ready                      @ 0x20007bcc
 */
/* Reconstructed FUN_00030c90 @ 0x30c90  (parity: 300/300 trials, PROVEN) */

extern int pt_nfc_eeprom_link_init(int *);

void pt_nfc_eeprom_link_start(void)
{
    int iVar1 = pt_nfc_eeprom_link_init(0x20002408UL);
    if (iVar1 >= 0) {
        *(volatile unsigned int*)0x20007bccUL = 1;
    }
}
