#include "g1_app_symbols.h"
/* named: check_sw0_status */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed check_sw0_status @ 0x2a868  (parity: 300/300 trials, PROVEN) */

extern int read_sw0_pin(void);
extern void debug_print(void);
extern void pt_nfc_eeprom_link_start(void);
extern void DEBUG_PRINT(unsigned int fmt, unsigned int arg);

void check_sw0_status(void)
{
    int iVar3 = read_sw0_pin();
    volatile int *piVar2 = (volatile int *)((uintptr_t)&g_log_level) /*=0x2000230c*/;
    volatile int *piVar1 = (volatile int *)((uintptr_t)&g_sw0_irq_low_cnt) /*=0x20007af0*/;

    if (iVar3 == 0) {
        if (*piVar2 > 1) {
            if (*(volatile int *)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                DEBUG_PRINT("%s(): interrupt line low!!!\n" /*=0xa18cd*/, "check_sw0_status" /*=0xa19af*/);
            } else {
                debug_print();
            }
        }
        iVar3 = *piVar1 + 1;
        *piVar1 = iVar3;
        if (iVar3 > 3) {
            if (*piVar2 > 1) {
                if (*(volatile int *)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                    DEBUG_PRINT("%s(): interrupt line abnormal, now reset\n" /*=0xa18ea*/, "check_sw0_status" /*=0xa19af*/);
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

