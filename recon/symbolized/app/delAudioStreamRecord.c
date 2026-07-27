#include "g1_app_symbols.h"
#include "../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_0002f878 @ 0x0002f878
 * public-name: delAudioStreamRecord
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   k_msgq_put                               <= FUN_000720d0 @ 0x000720d0
 *   k_sem_give                               <= FUN_00072880 @ 0x00072880
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_a3f45                             @ 0x000a3f45   [INLINED -- G6 literal batch]
 *   rodata_a420e                             @ 0x000a420e
 *   rodata_a4944                             @ 0x000a4944   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_audio_msgq                             @ 0x20003890
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_app_language_msgq                      @ 0x200079e4
 */
/* Reconstructed delAudioStreamRecord @ 0x2f878  (parity: 300/300 trials, PROVEN) */

extern void memset_bytes(void*, int, int);
extern int k_msgq_put(unsigned int, void*, int, int);
extern void k_sem_give(int);

unsigned int delAudioStreamRecord(unsigned char param_1)
{
    int iVar2;
    unsigned int uVar3;
    unsigned char buf[204];

    if (2 < *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/) {
        if (*(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            log_message(((unsigned long)&rodata_a420e) /*=0xa420e*/, ((unsigned long)"delAudioStreamRecord") /*=0xa4944*/);
        } else {
            debug_print(((unsigned long)&rodata_a420e) /*=0xa420e*/, ((unsigned long)"delAudioStreamRecord") /*=0xa4944*/);
        }
    }
    memset_bytes(buf + 1, 0, 0xcb);
    *(unsigned short*)(buf + 2) = 1;
    buf[0] = 4;
    buf[4] = param_1;
    iVar2 = k_msgq_put(((unsigned long)&g_audio_msgq) /*=0x20003890*/, buf, 0, 0);
    if (iVar2 == 0) {
        k_sem_give(((unsigned long)&g_app_language_msgq) /*=0x200079e4*/);
        uVar3 = 0;
    } else {
        if (0 < *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/) {
            if (*(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                log_message(((unsigned long)"%s(): enqueue_dmic failed\r\n\n") /*=0xa3f45*/, ((unsigned long)"delAudioStreamRecord") /*=0xa4944*/);
            } else {
                debug_print(((unsigned long)"%s(): enqueue_dmic failed\r\n\n") /*=0xa3f45*/, ((unsigned long)"delAudioStreamRecord") /*=0xa4944*/);
            }
        }
        uVar3 = 0xffffffff;
    }
    return uVar3;
}
