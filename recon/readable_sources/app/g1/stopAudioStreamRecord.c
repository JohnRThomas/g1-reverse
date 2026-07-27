#include "g1_app_symbols.h"
#include "../../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_0002f80c @ 0x0002f80c
 * public-name: stopAudioStreamRecord
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   k_msgq_put                               <= FUN_000720d0 @ 0x000720d0
 *   k_sem_give                               <= FUN_00072880 @ 0x00072880
 *   log_message                              <= FUN_0007dda4 @ 0x0007dda4
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_a3f45                             @ 0x000a3f45   [INLINED -- G6 literal batch]
 *   rodata_a4959                             @ 0x000a4959   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_audio_msgq                             @ 0x20003890
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_app_language_msgq                      @ 0x200079e4
 */
/* Reconstructed stopAudioStreamRecord @ 0x2f80c  (parity: 300/300 trials, PROVEN) */

extern void memset_bytes(void*, int, int);
extern int k_msgq_put(unsigned int, void*, int, int);
extern void k_sem_give(int);

unsigned int stopAudioStreamRecord(void)
{
    unsigned char record[208];
    memset_bytes(record + 5, 0, 203);
    record[4] = 3;
    int iVar1 = k_msgq_put(((unsigned long)&g_audio_msgq) /*=0x20003890*/, record + 4, 0, 0);
    unsigned int uVar2;
    if (iVar1 == 0) {
        k_sem_give((void *)((unsigned long)&g_app_language_msgq) /*=0x200079e4*/);
        uVar2 = 0;
    } else {
        if (*(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/ > 0) {
            if (*(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                log_message(((unsigned long)"%s(): enqueue_dmic failed\r\n\n") /*=0xa3f45*/, ((unsigned long)"stopAudioStreamRecord") /*=0xa4959*/);
            } else {
                debug_print(((unsigned long)"%s(): enqueue_dmic failed\r\n\n") /*=0xa3f45*/, ((unsigned long)"stopAudioStreamRecord") /*=0xa4959*/);
            }
        }
        uVar2 = 0xffffffffUL;
    }
    return uVar2;
}
