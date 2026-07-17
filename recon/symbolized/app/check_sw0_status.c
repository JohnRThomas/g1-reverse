#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0002a868 @ 0x0002a868
 * public-name: check_sw0_status
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   read_sw0_pin                             <= FUN_00017e30 @ 0x00017e30
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   pt_nfc_eeprom_link_start                 <= FUN_00030c90 @ 0x00030c90
 * address symbols (name @ address):
 *   rodata_a18cd                             @ 0x000a18cd
 *   rodata_a18ea                             @ 0x000a18ea
 *   rodata_a19af                             @ 0x000a19af
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_sw0_irq_low_cnt                        @ 0x20007af0
 */
/* Reconstructed check_sw0_status @ 0x2a868  (parity: 300/300 trials, PROVEN) */

extern int read_sw0_pin(void);
extern void debug_print(void);
extern void pt_nfc_eeprom_link_start(void);
extern void DEBUG_PRINT(unsigned int fmt, unsigned int arg);

void check_sw0_status(void)
{
    int iVar3 = read_sw0_pin();
    volatile int *piVar2 = (volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/;
    volatile int *piVar1 = (volatile int *)((unsigned long)&g_sw0_irq_low_cnt) /*=0x20007af0*/;

    if (iVar3 == 0) {
        if (*piVar2 > 1) {
            if (*(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                DEBUG_PRINT(((unsigned long)&rodata_a18cd) /*=0xa18cd*/, ((unsigned long)&rodata_a19af) /*=0xa19af*/);
            } else {
                debug_print();
            }
        }
        iVar3 = *piVar1 + 1;
        *piVar1 = iVar3;
        if (iVar3 > 3) {
            if (*piVar2 > 1) {
                if (*(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                    DEBUG_PRINT(((unsigned long)&rodata_a18ea) /*=0xa18ea*/, ((unsigned long)&rodata_a19af) /*=0xa19af*/);
                } else {
                    debug_print();
                }
            }
            pt_nfc_eeprom_link_start();
            return;
        }
    } else {
        *piVar1 = 0;
    }
    return;
}
