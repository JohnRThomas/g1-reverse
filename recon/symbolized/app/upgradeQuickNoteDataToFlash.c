#include "g1_app_symbols.h"
#include "../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_00024420 @ 0x00024420
 * public-name: upgradeQuickNoteDataToFlash
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   k_msgq_put                               <= FUN_000720d0 @ 0x000720d0
 *   k_sem_give                               <= FUN_00072880 @ 0x00072880
 * address symbols (name @ address):
 *   rodata_9edc2                             @ 0x0009edc2   [INLINED -- G6 literal batch]
 *   rodata_9edf3                             @ 0x0009edf3   [INLINED -- G6 literal batch]
 *   rodata_9f094                             @ 0x0009f094   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_quicknote_flash_msgq                   @ 0x20003960
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_app_language_msgq                      @ 0x200079e4
 */
/* Reconstructed upgradeQuickNoteDataToFlash @ 0x24420  (parity: 300/300 trials, PROVEN) */

extern int k_msgq_put(unsigned int, void*, int, int);
extern void k_sem_give(unsigned int);

int upgradeQuickNoteDataToFlash(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    unsigned int request[3];
    int iVar1;
    int uVar2;

    request[0] = 0x10001;
    request[1] = (param_2 & 0xffff0000U) | (param_1 & 0xffU);
    request[2] = param_3;
    iVar1 = k_msgq_put(((unsigned long)&g_quicknote_flash_msgq) /*=0x20003960*/, request, 0, 0);
    if (iVar1 == 0) {
        if (2 < *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/) {
            if (*(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                log_message(((unsigned long)"%s(): SEND QUICKNOTE TEXT Store(%d) Command...\n") /*=0x9edf3*/, ((unsigned long)"upgradeQuickNoteDataToFlash") /*=0x9f094*/, param_1);
            } else {
                debug_print(((unsigned long)"%s(): SEND QUICKNOTE TEXT Store(%d) Command...\n") /*=0x9edf3*/, ((unsigned long)"upgradeQuickNoteDataToFlash") /*=0x9f094*/, param_1);
            }
        }
        k_sem_give(((unsigned long)&g_app_language_msgq) /*=0x200079e4*/);
        uVar2 = 0;
    } else {
        if (0 < *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/) {
            if (*(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                log_message(((unsigned long)"%s(): quicknote flash store queue fill failed\r\n\n") /*=0x9edc2*/, ((unsigned long)"upgradeQuickNoteDataToFlash") /*=0x9f094*/);
            } else {
                debug_print(((unsigned long)"%s(): quicknote flash store queue fill failed\r\n\n") /*=0x9edc2*/, ((unsigned long)"upgradeQuickNoteDataToFlash") /*=0x9f094*/);
            }
        }
        uVar2 = -1;
    }
    return uVar2;
}
