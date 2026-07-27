#include "g1_app_symbols.h"
#include "../../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_00023bfc @ 0x00023bfc
 * public-name: upgradeDashboardStartupModeInfoToFlash
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   k_msgq_put                               <= FUN_000720d0 @ 0x000720d0
 *   k_sem_give                               <= FUN_00072880 @ 0x00072880
 * address symbols (name @ address):
 *   rodata_9e903                             @ 0x0009e903   [INLINED -- G6 literal batch]
 *   rodata_9e98c                             @ 0x0009e98c   [INLINED -- G6 literal batch]
 *   rodata_9ed68                             @ 0x0009ed68   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_flash_store_cmd_msgq                   @ 0x20003994
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_app_language_msgq                      @ 0x200079e4
 */
/* Reconstructed upgradeDashboardStartupModeInfoToFlash @ 0x23bfc  (parity: 300/300 trials, PROVEN) */
extern int k_msgq_put(unsigned int, void*, int, int);
extern void k_sem_give(int);

unsigned int upgradeDashboardStartupModeInfoToFlash(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    unsigned int buf[3];
    int iVar1;
    unsigned int uVar2;
    buf[0] = 0x00010003UL;
    buf[1] = (param_2 & 0xffff0000UL) | (param_1 & 0xffUL);
    buf[2] = param_3;
    iVar1 = k_msgq_put(((unsigned long)&g_flash_store_cmd_msgq) /*=0x20003994*/, buf, 0UL, 0UL);
    if (iVar1 == 0) {
        if (2 < *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/) {
            if (*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0)
                log_message(((unsigned long)"%s(): send startup mode  store Command, mode = %d\n") /*=0x9e98c*/, ((unsigned long)"upgradeDashboardStartupModeInfoToFlash") /*=0x9ed68*/, param_1);
            else
                debug_print(((unsigned long)"%s(): send startup mode  store Command, mode = %d\n") /*=0x9e98c*/, ((unsigned long)"upgradeDashboardStartupModeInfoToFlash") /*=0x9ed68*/, param_1);
        }
        k_sem_give(((unsigned long)&g_app_language_msgq) /*=0x200079e4*/);
        uVar2 = 0;
    } else {
        if (0 < *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/) {
            if (*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0)
                log_message(((unsigned long)"%s(): setting flash store queue fill failed\r\n\n") /*=0x9e903*/, ((unsigned long)"upgradeDashboardStartupModeInfoToFlash") /*=0x9ed68*/);
            else
                debug_print(((unsigned long)"%s(): setting flash store queue fill failed\r\n\n") /*=0x9e903*/, ((unsigned long)"upgradeDashboardStartupModeInfoToFlash") /*=0x9ed68*/);
        }
        uVar2 = 0xffffffffUL;
    }
    return uVar2;
}
