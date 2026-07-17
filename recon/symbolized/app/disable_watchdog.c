#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0002aeb4 @ 0x0002aeb4
 * public-name: disable_watchdog
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 * address symbols (name @ address):
 *   g_watchdog_device                        @ 0x00087cc8
 *   rodata_a1c4e                             @ 0x000a1c4e
 *   rodata_a1c6a                             @ 0x000a1c6a
 *   rodata_a1c85                             @ 0x000a1c85
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_wdt_channel_id                         @ 0x20007b50
 */
/* Reconstructed disable_watchdog @ 0x2aeb4  (parity: 151/300 trials, PROVEN) */

extern void FUN_00074844(unsigned int, unsigned int);
extern void log_message(unsigned int, unsigned int, ...);
extern void debug_print(unsigned int, unsigned int, ...);

typedef int (*fp_t)(unsigned int);

int disable_watchdog(void)
{
    volatile int *piVar1 = (volatile int*)((unsigned long)&g_wdt_channel_id) /*=0x20007b50*/;
    int iVar5;

    if (*piVar1 < 0) {
        if (3 < *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/) {
            if (*(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                log_message(((unsigned long)&rodata_a1c4e) /*=0xa1c4e*/, ((unsigned long)&rodata_a1c85) /*=0xa1c85*/, *piVar1);
            } else {
                debug_print(((unsigned long)&rodata_a1c4e) /*=0xa1c4e*/, ((unsigned long)&rodata_a1c85) /*=0xa1c85*/, *piVar1);
            }
        }
        iVar5 = 0;
    } else {
        int iVar6 = 5;
        do {
            if (3 < *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/) {
                if (*(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                    log_message(((unsigned long)&rodata_a1c6a) /*=0xa1c6a*/, ((unsigned long)&rodata_a1c85) /*=0xa1c85*/, 0,
                                *(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/);
                } else {
                    debug_print(((unsigned long)&rodata_a1c6a) /*=0xa1c6a*/, ((unsigned long)&rodata_a1c85) /*=0xa1c85*/, 0,
                                 *(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/);
                }
            }
            fp_t f = *(fp_t*)(*(int*)(((unsigned long)&g_watchdog_device) /*=0x87cc8*/ + 8) + 4);
            iVar5 = f(((unsigned long)&g_watchdog_device) /*=0x87cc8*/);
            if (iVar5 == 0) {
                *piVar1 = -0x10;
                iVar5 = 0;
                break;
            }
            FUN_00074844(0x667, 0);
            iVar6 = iVar6 - 1;
        } while (iVar6 != 0);
    }
    return iVar5;
}
