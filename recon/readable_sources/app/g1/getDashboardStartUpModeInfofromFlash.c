#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00023df4 @ 0x00023df4
 * public-name: getDashboardStartUpModeInfofromFlash
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   z_device_is_ready                        <= FUN_0008638c @ 0x0008638c
 * address symbols (name @ address):
 *   rodata_87bf0                             @ 0x00087bf0
 *   rodata_9e9bf                             @ 0x0009e9bf   [INLINED -- G6 literal batch]
 *   rodata_9e9ea                             @ 0x0009e9ea
 *   rodata_9ea0a                             @ 0x0009ea0a
 *   rodata_9ea58                             @ 0x0009ea58   [INLINED -- G6 literal batch]
 *   rodata_9ed09                             @ 0x0009ed09   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_ui_mode_flag                           @ 0x20018462
 */
/* Reconstructed getDashboardStartUpModeInfofromFlash @ 0x23df4  (parity: 100/100 trials, PROVEN) */
#include <stdint.h>
#include "../../../headers/g1_log.h"
extern void *get_device_info(void);
extern int z_device_is_ready(uint32_t);

unsigned char getDashboardStartUpModeInfofromFlash(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    volatile int *piVar1;
    volatile unsigned int *puVar2;
    unsigned char uVar3;
    int iVar4;
    unsigned int uVar5;
    int iVar6;
    int iVar7;

    piVar1 = (volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/;
    volatile unsigned int local_14 = param_2;

    if (2 < *piVar1) {
        if (*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            log_message(((unsigned long)"%s(): read setting flash data to ram...\r\n\n") /*=0x9e9bf*/, ((unsigned long)"getDashboardStartUpModeInfofromFlash") /*=0x9ed09*/, param_3,
                        *(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/);
        } else {
            debug_print(((unsigned long)"%s(): read setting flash data to ram...\r\n\n") /*=0x9e9bf*/, ((unsigned long)"getDashboardStartUpModeInfofromFlash") /*=0x9ed09*/, param_3,
                         *(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/);
        }
    }
    puVar2 = (volatile unsigned int*)((unsigned long)&rodata_87bf0) /*=0x87bf0*/;
    iVar4 = z_device_is_ready(((unsigned long)&rodata_87bf0) /*=0x87bf0*/);
    if (iVar4 == 0) {
        if (0 < *piVar1) {
            if (*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                log_message(((unsigned long)&rodata_9e9ea) /*=0x9e9ea*/, ((unsigned long)"getDashboardStartUpModeInfofromFlash") /*=0x9ed09*/, *puVar2,
                            *(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/);
            } else {
                debug_print(((unsigned long)&rodata_9e9ea) /*=0x9e9ea*/, ((unsigned long)"getDashboardStartUpModeInfofromFlash") /*=0x9ed09*/, *puVar2,
                             *(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/);
            }
        }
        uVar3 = 0xff;
    } else {
        local_14 = local_14 & 0xff000000UL;
        char *p1 = (char*)get_device_info();
        void *pcVar8 = *(void**)(p1 + 0x1030);
        void *r1arg = get_device_info();
        int (*fn)(void*, unsigned int, void*, int) = (int(*)(void*, unsigned int, void*, int))pcVar8;
        iVar6 = fn(r1arg, 0x13e000, (void *)&local_14, 3);
        iVar4 = ((unsigned long)&g_ui_mode_flag) /*=0x20018462*/;
        iVar7 = *piVar1;
        if (iVar6 == 0) {
            if (((unsigned char)local_14 == 0xaa) &&
                ((unsigned char)(local_14 >> 16) != 0xff)) {
                *(unsigned char*)(intptr_t)(((unsigned long)&g_ui_mode_flag) /*=0x20018462*/ + 2) = (unsigned char)(local_14 >> 16);
            } else {
                *(unsigned char*)(intptr_t)(((unsigned long)&g_ui_mode_flag) /*=0x20018462*/ + 2) = 0;
            }
            if (0 < iVar7) {
                if (*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                    log_message(((unsigned long)"%s(): dashboard startup mode = %d\n") /*=0x9ea58*/, ((unsigned long)"getDashboardStartUpModeInfofromFlash") /*=0x9ed09*/, (unsigned int)*(unsigned char*)(intptr_t)(iVar4 + 2),
                                *(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/);
                } else {
                    debug_print(((unsigned long)"%s(): dashboard startup mode = %d\n") /*=0x9ea58*/, ((unsigned long)"getDashboardStartUpModeInfofromFlash") /*=0x9ed09*/, (unsigned int)*(unsigned char*)(intptr_t)(iVar4 + 2),
                                 *(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/);
                }
            }
            uVar3 = *(unsigned char*)(intptr_t)(iVar4 + 2);
        } else {
            if (0 < iVar7) {
                if (*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                    log_message(((unsigned long)&rodata_9ea0a) /*=0x9ea0a*/, ((unsigned long)"getDashboardStartUpModeInfofromFlash") /*=0x9ed09*/, 0x13e000UL,
                                *(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/);
                } else {
                    debug_print(((unsigned long)&rodata_9ea0a) /*=0x9ea0a*/, ((unsigned long)"getDashboardStartUpModeInfofromFlash") /*=0x9ed09*/, 0x13e000UL,
                                 *(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/);
                }
            }
            uVar3 = 0;
        }
    }
    return uVar3;
}
