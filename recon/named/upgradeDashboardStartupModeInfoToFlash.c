/* readable reconstruction; identity: FUN_00023bfc @ 0x00023bfc
 * public-name: upgradeDashboardStartupModeInfoToFlash
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   k_msgq_put                               <= FUN_000720d0 @ 0x000720d0
 *   k_sem_give                               <= FUN_00072880 @ 0x00072880
 * address symbols (name @ address):
 *   rodata_9e903                             @ 0x0009e903
 *   rodata_9e98c                             @ 0x0009e98c
 *   rodata_9ed68                             @ 0x0009ed68
 *   g_log_level                              @ 0x2000230c
 *   g_flash_store_cmd_msgq                   @ 0x20003994
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_app_language_msgq                      @ 0x200079e4
 */
/* Reconstructed upgradeDashboardStartupModeInfoToFlash @ 0x23bfc  (parity: 300/300 trials, PROVEN) */
extern int k_msgq_put(unsigned int a0, void *a1, unsigned int a2, unsigned int a3);
extern void DEBUG_PRINT(unsigned int a0, ...);
extern void debug_print(unsigned int a0, ...);
extern void k_sem_give(unsigned int a0);

unsigned int upgradeDashboardStartupModeInfoToFlash(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    unsigned int buf[3];
    int iVar1;
    unsigned int uVar2;
    buf[0] = 0x00010003UL;
    buf[1] = (param_2 & 0xffff0000UL) | (param_1 & 0xffUL);
    buf[2] = param_3;
    iVar1 = k_msgq_put(0x20003994UL, buf, 0UL, 0UL);
    if (iVar1 == 0) {
        if (2 < *(volatile int*)0x2000230cUL) {
            if (*(volatile int*)0x20007554UL == 0)
                DEBUG_PRINT(0x9e98cUL, 0x9ed68UL, param_1);
            else
                debug_print(0x9e98cUL, 0x9ed68UL, param_1);
        }
        k_sem_give(0x200079e4UL);
        uVar2 = 0;
    } else {
        if (0 < *(volatile int*)0x2000230cUL) {
            if (*(volatile int*)0x20007554UL == 0)
                DEBUG_PRINT(0x9e903UL, 0x9ed68UL);
            else
                debug_print(0x9e903UL, 0x9ed68UL);
        }
        uVar2 = 0xffffffffUL;
    }
    return uVar2;
}
