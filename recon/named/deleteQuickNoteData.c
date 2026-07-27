struct k_sem;
/* readable reconstruction; identity: FUN_000244a8 @ 0x000244a8
 * public-name: deleteQuickNoteData
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   k_msgq_put                               <= FUN_000720d0 @ 0x000720d0
 *   k_sem_give                               <= FUN_00072880 @ 0x00072880
 * address symbols (name @ address):
 *   rodata_9edc2                             @ 0x0009edc2   [INLINED -- G6 literal batch]
 *   rodata_9ee23                             @ 0x0009ee23   [INLINED -- G6 literal batch]
 *   rodata_9f080                             @ 0x0009f080   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_quicknote_flash_msgq                   @ 0x20003960
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_app_language_msgq                      @ 0x200079e4
 */
#include "../headers/g1_log.h"
/* Reconstructed deleteQuickNoteData @ 0x244a8  (parity: 300/300 trials, PROVEN) */
extern int k_msgq_put(unsigned int, void*, int, int);
extern void k_sem_give(struct k_sem *);

unsigned int deleteQuickNoteData(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    unsigned int buf[3];
    int iVar1;
    unsigned int uVar2;
    buf[0] = 0x00010002UL;
    /* The compact record owns a byte selector and a zero byte; its upper
       halfword is the caller's second field, exactly as queued by firmware. */
    buf[1] = (param_2 & 0xffff0000UL) | (unsigned char)param_1;
    buf[2] = param_3;
    iVar1 = k_msgq_put(0x20003960UL, buf, 0UL, 0UL);
    if (iVar1 == 0) {
        if (2 < *(volatile int*)0x2000230cUL) {
            if (*(volatile int*)0x20007554UL == 0)
                log_message(0x9ee23UL, 0x9f080UL, param_1);
            else
                debug_print(0x9ee23UL, 0x9f080UL, param_1);
        }
        k_sem_give(0x200079e4UL);
        uVar2 = 0;
    } else {
        if (0 < *(volatile int*)0x2000230cUL) {
            if (*(volatile int*)0x20007554UL == 0)
                log_message(((unsigned long)"%s(): quicknote flash store queue fill failed\r\n\n"), 0x9f080UL);
            else
                debug_print(((unsigned long)"%s(): quicknote flash store queue fill failed\r\n\n"), 0x9f080UL);
        }
        uVar2 = 0xffffffffUL;
    }
    return uVar2;
}
