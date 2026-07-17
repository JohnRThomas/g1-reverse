#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0002bffc @ 0x0002bffc
 * public-name: update_temp_task_status
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   display_close_screen                     <= FUN_00049858 @ 0x00049858
 * address symbols (name @ address):
 *   rodata_a2597                             @ 0x000a2597
 *   rodata_a25b9                             @ 0x000a25b9
 *   rodata_a25d9                             @ 0x000a25d9
 *   rodata_a2648                             @ 0x000a2648
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_persist_task_status_lock               @ 0x20018d9c
 */
/* Reconstructed update_temp_task_status @ 0x2bffc  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void log_message(uint32_t, ...);
extern void debug_print(uint32_t, ...);
extern void display_close_screen(unsigned char);
extern void FUN_0007cdf8(void);

unsigned int update_temp_task_status(int param_1, unsigned int param_2, unsigned int param_3)
{
    volatile char *pcVar1 = (volatile char*)((unsigned long)&g_persist_task_status_lock) /*=0x20018d9c*/;
    uint32_t format_string;
    unsigned int uVar2;
    unsigned char *puVar3;
    int iVar4;

    while (*pcVar1 != 0) {
        FUN_0007cdf8();
    }
    *pcVar1 = 1;

    if (((**(unsigned int**)(intptr_t)(param_1 + 0x1054) == param_2) &&
         ((uVar2 = (unsigned int)(unsigned char)((*(unsigned int**)(intptr_t)(param_1 + 0x1054))[1]),
           uVar2 == 1 || (uVar2 == param_3)))) ||
        (*(unsigned char*)(intptr_t)(param_1 + 0xd5) == param_2)) {
        goto LAB_0002c076;
    }

    if ((*(char*)(intptr_t)(param_1 + 0xd5) == 0) || (*(char*)(intptr_t)(param_1 + 0xd5) == 1)) {
        if (param_3 != 2) goto LAB_0002c08a;
LAB_0002c052:
        if (0 < *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/) {
            iVar4 = *(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
            format_string = ((unsigned long)&rodata_a2597) /*=0xa2597*/;
LAB_0002c0ac:
            if (iVar4 == 0) {
                log_message(format_string, ((unsigned long)&rodata_a2648) /*=0xa2648*/, param_2);
            } else {
                debug_print(format_string, ((unsigned long)&rodata_a2648) /*=0xa2648*/, param_2);
            }
        }
    } else {
        display_close_screen(*(unsigned char*)(intptr_t)(param_1 + 0xd5));
        if (param_3 == 2) {
            if ((param_2 & 0xfffffffdUL) != 4) goto LAB_0002c076;
            goto LAB_0002c052;
        }
LAB_0002c08a:
        if (param_3 == 3) {
            if (*(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/ < 1) goto LAB_0002c05a;
            iVar4 = *(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
            format_string = ((unsigned long)&rodata_a25b9) /*=0xa25b9*/;
            goto LAB_0002c0ac;
        }
        if (0 < *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/) {
            iVar4 = *(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
            format_string = ((unsigned long)&rodata_a25d9) /*=0xa25d9*/;
            goto LAB_0002c0ac;
        }
    }
LAB_0002c05a:
    *(unsigned char*)(intptr_t)(param_1 + 0xd5) = (unsigned char)param_2;
    puVar3 = *(unsigned char**)(intptr_t)(param_1 + 0x1054);
    *puVar3 = 0;
    puVar3[1] = 0;
    puVar3[2] = 0;
    puVar3[3] = 0;
    *(unsigned char*)(intptr_t)(*(int*)(intptr_t)(param_1 + 0x1054) + 4) = 1;
LAB_0002c076:
    *pcVar1 = 0;
    return param_3;
}
