/* readable reconstruction; identity: FUN_00023af0 @ 0x00023af0
 * public-name: upgradeAppLanguageInfoToFlash
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   k_msgq_put                               <= FUN_000720d0 @ 0x000720d0
 *   k_sem_give                               <= FUN_00072880 @ 0x00072880
 * address symbols (name @ address):
 *   rodata_9e903                             @ 0x0009e903   [INLINED -- G6 literal batch]
 *   rodata_9e932                             @ 0x0009e932   [INLINED -- G6 literal batch]
 *   rodata_9eda4                             @ 0x0009eda4   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_flash_store_cmd_msgq                   @ 0x20003994
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_app_language_msgq                      @ 0x200079e4
 */
#include "../headers/g1_log.h"
/* Reconstructed upgradeAppLanguageInfoToFlash @ 0x23af0  (parity: 300/300 trials, PROVEN) */
extern int k_msgq_put(unsigned int, void*, int, int);
extern void k_sem_give(int);

unsigned int upgradeAppLanguageInfoToFlash(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    unsigned int buf[3];
    int iVar1;
    unsigned int uVar2;
    buf[0] = 0x10001UL;
    /* The shipped frame reuses the saved second argument for this word,
       clears its low halfword, then publishes the language byte. */
    buf[1] = (param_2 & 0xffff0000UL) | (unsigned int)(unsigned char)param_1;
    buf[2] = param_3;
    iVar1 = k_msgq_put(0x20003994UL, buf, 0UL, 0UL);
    if (iVar1 == 0) {
        if (2 < *(volatile int*)0x2000230cUL) {
            unsigned int sink = *(volatile unsigned int*)0x20007554UL;
            if (sink == 0)
                log_message(0x9e932UL, 0x9eda4UL, param_1, sink);
            else
                debug_print(0x9e932UL, 0x9eda4UL, param_1, sink);
        }
        k_sem_give(0x200079e4UL);
        uVar2 = 0;
    } else {
        if (0 < *(volatile int*)0x2000230cUL) {
            unsigned int sink = *(volatile unsigned int*)0x20007554UL;
            if (sink == 0)
                log_message(((unsigned long)"%s(): setting flash store queue fill failed\r\n\n"), 0x9eda4UL, 0UL, sink);
            else
                debug_print(((unsigned long)"%s(): setting flash store queue fill failed\r\n\n"), 0x9eda4UL, 0UL, sink);
        }
        uVar2 = 0xffffffffUL;
    }
    return uVar2;
}
