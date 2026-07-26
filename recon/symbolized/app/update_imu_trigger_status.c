#include "g1_app_symbols.h"
#include "../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_0002bcbc @ 0x0002bcbc
 * public-name: update_imu_trigger_status
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   k_sem_give                               <= FUN_00072880 @ 0x00072880
 * address symbols (name @ address):
 *   rodata_a24a9                             @ 0x000a24a9   [INLINED -- G6 literal batch]
 *   rodata_a24c3                             @ 0x000a24c3   [INLINED -- G6 literal batch]
 *   rodata_a2530                             @ 0x000a2530   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed update_imu_trigger_status @ 0x2bcbc  (parity: 300/300 trials, PROVEN) */

extern void k_sem_give(unsigned int);

unsigned int update_imu_trigger_status(unsigned int param_1, int param_2, int param_3)
{
    unsigned int uVar2;

    if (*(volatile int*)(param_2 + 0xee8) == param_3) {
        uVar2 = 0xffffffff;
    } else {
        *(volatile int*)(param_2 + 0xee8) = param_3;
        if (2 < *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/) {
            if (*(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                log_message(((unsigned long)"%s(): %s new status: %d\n\n") /*=0xa24a9*/, ((unsigned long)"update_imu_trigger_status") /*=0xa2530*/, param_1, param_3);
            } else {
                debug_print(((unsigned long)"%s(): %s new status: %d\n\n") /*=0xa24a9*/, ((unsigned long)"update_imu_trigger_status") /*=0xa2530*/, param_1, param_3);
            }
        }
        if ((*(volatile unsigned char*)(param_2 + 0xfea) == 0xa) && (param_3 != 0) &&
            (*(volatile unsigned char*)(param_2 + 0xb0c) == 0)) {
            if (2 < *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/) {
                if (*(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                    log_message(((unsigned long)"%s(): imu wakeup thd-> \n") /*=0xa24c3*/, ((unsigned long)"update_imu_trigger_status") /*=0xa2530*/, 0, 0);
                } else {
                    debug_print(((unsigned long)"%s(): imu wakeup thd-> \n") /*=0xa24c3*/, ((unsigned long)"update_imu_trigger_status") /*=0xa2530*/, 0, 0);
                }
            }
            *(volatile unsigned char*)(param_2 + 0xfe9) = 1;
            k_sem_give(param_2 + 0xaf4);
        }
        uVar2 = 0;
    }
    return uVar2;
}
