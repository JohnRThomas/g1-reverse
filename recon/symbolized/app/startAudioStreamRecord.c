#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0002f764 @ 0x0002f764
 * public-name: startAudioStreamRecord
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   display_DelayClose                       <= FUN_000498c0 @ 0x000498c0
 *   k_msgq_put                               <= FUN_000720d0 @ 0x000720d0
 *   k_sem_give                               <= FUN_00072880 @ 0x00072880
 *   log_message                              <= FUN_0007dda4 @ 0x0007dda4
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_a4304                             @ 0x000a4304
 *   rodata_a432a                             @ 0x000a432a
 *   rodata_a496f                             @ 0x000a496f
 *   g_log_level                              @ 0x2000230c
 *   g_audio_msgq                             @ 0x20003890
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_app_language_msgq                      @ 0x200079e4
 */
/* Reconstructed startAudioStreamRecord @ 0x2f764  (parity: 300/300 trials, PROVEN) */

extern void log_message(unsigned int message, unsigned int function);
extern void debug_print(unsigned int message, unsigned int function);
extern unsigned int get_device_info(void);
extern void display_DelayClose(unsigned int ms);
extern int k_msgq_put(int a, void *b, int c, int d);
extern void k_sem_give(void *a);
extern void memset_bytes(void *dst, int val, int n);
extern void sync_to_slave(unsigned int a, unsigned int b, void *c, unsigned int d);

unsigned int startAudioStreamRecord(void)
{
    unsigned char buf[208];
    int iVar2;
    unsigned int uVar3;

    memset_bytes(buf + 5, 0, 0xcb);
    buf[4] = 1;
    iVar2 = k_msgq_put(((unsigned long)&g_audio_msgq) /*=0x20003890*/, buf + 4, 0, 0);
    if (iVar2 == 0) {
        k_sem_give((void*)((unsigned long)&g_app_language_msgq) /*=0x200079e4*/);
        uVar3 = 0;
    } else {
        if (0 < *(int *)((unsigned long)&g_log_level) /*=0x2000230c*/) {
            if (*(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                log_message(((unsigned long)&rodata_a4304) /*=0xa4304*/, ((unsigned long)&rodata_a496f) /*=0xa496f*/);
            } else {
                debug_print(((unsigned long)&rodata_a4304) /*=0xa4304*/, ((unsigned long)&rodata_a496f) /*=0xa496f*/);
            }
        }
        *(unsigned short *)buf = 1;
        uVar3 = get_device_info();
        sync_to_slave(uVar3, 6, buf, 2);
        display_DelayClose(10000);
        if (0 < *(int *)((unsigned long)&g_log_level) /*=0x2000230c*/) {
            if (*(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                log_message(((unsigned long)&rodata_a432a) /*=0xa432a*/, ((unsigned long)&rodata_a496f) /*=0xa496f*/);
            } else {
                debug_print(((unsigned long)&rodata_a432a) /*=0xa432a*/, ((unsigned long)&rodata_a496f) /*=0xa496f*/);
            }
        }
        uVar3 = 0xffffffff;
    }
    return uVar3;
}
