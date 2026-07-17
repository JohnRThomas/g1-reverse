/* readable reconstruction; identity: FUN_00065478 @ 0x00065478
 * public-name: gpiote_pin_sense_is_enabled
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_pin_idx                              <= FUN_00065434 @ 0x00065434
 *   gpiote_pin_sense_is_enabled              <= FUN_00065478 @ 0x00065478
 * address symbols (name @ address):
 *   g_gpiote_cb                              @ 0x20002bc0
 */
/* Reconstructed FUN_00065478 @ 0x65478  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int get_pin_idx(void);
unsigned short gpiote_pin_sense_is_enabled(void) {
    int iVar3 = get_pin_idx();
    unsigned short uVar1 = *(volatile uint16_t*)(0x20002bc0UL + (uint32_t)((iVar3 + 8) * 2));
    unsigned short uVar2 = uVar1 & 0x1c;
    if ((uVar1 & 0x1c) != 0) {
        uVar2 = 1;
    }
    return uVar2;
}
