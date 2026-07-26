/* readable reconstruction; identity: FUN_00022518 @ 0x00022518
 * public-name: sett_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   settings_register                        <= FUN_0004e494 @ 0x0004e494
 *   settings_subsys_init                     <= FUN_0004e744 @ 0x0004e744
 *   log_message                              <= FUN_0007dda4 @ 0x0007dda4
 * address symbols (name @ address):
 *   rodata_22121                             @ 0x00022121
 *   ADDR_local_store_write_THUMB             @ 0x00022169
 *   rodata_7c26b                             @ 0x0007c26b
 *   rodata_9e266                             @ 0x0009e266
 *   rodata_9e2cb                             @ 0x0009e2cb
 *   rodata_9e549                             @ 0x0009e549
 *   g_log_level                              @ 0x2000230c
 *   g_t_init                                 @ 0x20002368
 *   g_log_use_alt_sink                       @ 0x20007554
 */
#include "../headers/g1_log.h"
/* Reconstructed sett_init @ 0x22518  (parity: 300/300 trials, PROVEN) */

extern int settings_subsys_init(void);
extern int settings_register(unsigned int);

void sett_init(int *param_1)
{
    int iVar2;
    volatile int *piVar1;
    unsigned int format_string;
    int iVar3;

    iVar2 = settings_subsys_init();
    piVar1 = (volatile int*)0x2000230cUL;
    if (iVar2 == 0) {
        iVar2 = settings_register(0x20002368UL);
        if (iVar2 == 0) {
            if (1 < *piVar1) {
                if (*(volatile unsigned int*)0x20007554UL == 0) {
                    log_message(0x9e2cb, 0x9e549);
                } else {
                    debug_print(0x9e2cb, 0x9e549);
                }
            }
            iVar2 = 1;
            goto LAB;
        }
        if (*piVar1 < 2) goto LAB;
        iVar3 = *(volatile int*)0x20007554UL;
        format_string = 0x9e2a0;
    } else {
        if (*piVar1 < 2) goto LAB;
        iVar3 = *(volatile int*)0x20007554UL;
        format_string = 0x9e266;
    }
    if (iVar3 == 0) {
        log_message(format_string, 0x9e549, iVar2);
    } else {
        debug_print(format_string, 0x9e549, iVar2);
    }
LAB:
    param_1[0] = iVar2;
    param_1[1] = 0x22169;
    param_1[2] = 0x7c26b;
    param_1[3] = 0x22121;
}
