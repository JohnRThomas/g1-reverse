/* readable reconstruction; identity: FUN_00024420 @ 0x00024420
 * public-name: upgradeQuickNoteDataToFlash
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   k_msgq_put                               <= FUN_000720d0 @ 0x000720d0
 * address symbols (name @ address):
 *   rodata_9edc2                             @ 0x0009edc2
 *   rodata_9edf3                             @ 0x0009edf3
 *   rodata_9f094                             @ 0x0009f094
 *   g_log_level                              @ 0x2000230c
 *   g_quicknote_flash_msgq                   @ 0x20003960
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_app_language_msgq                      @ 0x200079e4
 */
/* Reconstructed upgradeQuickNoteDataToFlash @ 0x24420  (parity: 300/300 trials, PROVEN) */

extern int k_msgq_put(unsigned int, void*, int, int);
extern void DEBUG_PRINT(unsigned int, unsigned int, ...);
extern void debug_print(unsigned int, ...);
extern void FUN_00072880(unsigned int);

int upgradeQuickNoteDataToFlash(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    unsigned int request[3];
    int iVar1;
    int uVar2;

    request[0] = 0x10001;
    request[1] = (param_2 & 0xffff0000U) | (param_1 & 0xffU);
    request[2] = param_3;
    iVar1 = k_msgq_put(0x20003960UL, request, 0, 0);
    if (iVar1 == 0) {
        if (2 < *(volatile int*)0x2000230cUL) {
            if (*(volatile unsigned int*)0x20007554UL == 0) {
                DEBUG_PRINT(0x9edf3, 0x9f094, param_1);
            } else {
                debug_print(0x9edf3, 0x9f094, param_1);
            }
        }
        FUN_00072880(0x200079e4UL);
        uVar2 = 0;
    } else {
        if (0 < *(volatile int*)0x2000230cUL) {
            if (*(volatile unsigned int*)0x20007554UL == 0) {
                DEBUG_PRINT(0x9edc2, 0x9f094);
            } else {
                debug_print(0x9edc2, 0x9f094);
            }
        }
        uVar2 = -1;
    }
    return uVar2;
}
