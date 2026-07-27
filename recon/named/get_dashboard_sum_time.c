/* readable reconstruction; identity: FUN_0004a960 @ 0x0004a960
 * public-name: get_dashboard_sum_time
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   k_uptime_get_10                          <= FUN_0007daa4 @ 0x0007daa4
 * address symbols (name @ address):
 *   rodata_f0369                             @ 0x000f0369   [INLINED -- G6 literal batch]
 *   rodata_f0492                             @ 0x000f0492   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
#include "../headers/g1_log.h"
/* Reconstructed get_dashboard_sum_time @ 0x4a960  (parity: 300/300 trials, PROVEN) */

extern unsigned long long k_uptime_get_10(void);
extern int get_device_info(void);

long long get_dashboard_sum_time(void)
{
    unsigned long long uVar7;
    unsigned int iVar1;
    unsigned long long field;
    long long lVar8;

    uVar7 = k_uptime_get_10();
    iVar1 = get_device_info();
    field = *(volatile unsigned long long*)(iVar1 + 0x1094);
    if ((long long)field >= (long long)uVar7) {
        iVar1 = get_device_info();
        field = *(volatile unsigned long long*)(iVar1 + 0x1094);
        uVar7 = k_uptime_get_10();
        lVar8 = (long long)(field - uVar7);
    } else {
        uVar7 = k_uptime_get_10();
        iVar1 = get_device_info();
        field = *(volatile unsigned long long*)(iVar1 + 0x1094);
        lVar8 = (long long)(uVar7 - field);
    }
    if (1 < *(volatile int*)0x2000230cUL) {
        unsigned int loP = (unsigned int)lVar8;
        unsigned int hiP = (unsigned int)((unsigned long long)lVar8 >> 32);
        if (*(volatile unsigned int*)0x20007554UL == 0) {
            log_message(((unsigned long)"%s(): get_dashboard_sum_time is %d\n"), ((unsigned long)"get_dashboard_sum_time"), loP, hiP);
        } else {
            debug_print(((unsigned long)"%s(): get_dashboard_sum_time is %d\n"), ((unsigned long)"get_dashboard_sum_time"), loP, hiP);
        }
    }
    return lVar8;
}
