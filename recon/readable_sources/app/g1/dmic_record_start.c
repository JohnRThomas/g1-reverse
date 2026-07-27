#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0003b78c @ 0x0003b78c
 * public-name: dmic_record_start
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   drain_audio_msgq                         <= FUN_0002f688 @ 0x0002f688
 *   startAudioStreamRecord                   <= FUN_0002f764 @ 0x0002f764
 *   k_sem_give                               <= FUN_00072880 @ 0x00072880
 * address symbols (name @ address):
 *   rodata_9d30b                             @ 0x0009d30b   [INLINED -- G6 literal batch]
 *   rodata_a9843                             @ 0x000a9843   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_pending_event_word                     @ 0x20007b78
 */
/* Reconstructed dmic_record_start @ 0x3b78c */

#include <stdint.h>
#include "../../../headers/g1_log.h"

extern int get_device_info(void);
extern unsigned int drain_audio_msgq(void);
extern unsigned int startAudioStreamRecord(void);
extern void k_sem_give(int);

void dmic_record_start(void)
{
    uint8_t *device = get_device_info();
    device[0x1059] = 4;

    if (*(volatile int32_t *)((unsigned long)&g_log_level) /*=0x2000230c*/ > 2) {
        if (*(volatile uint32_t *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            log_message(((unsigned long)"%s(): received open dmic command\n") /*=0x9d30b*/, ((unsigned long)"dmic_record_start") /*=0xa9843*/);
        } else {
            debug_print(((unsigned long)"%s(): received open dmic command\n") /*=0x9d30b*/, ((unsigned long)"dmic_record_start") /*=0xa9843*/);
        }
    }

    drain_audio_msgq();
    startAudioStreamRecord();
    (void)__atomic_exchange_n((uint32_t *)((unsigned long)&g_pending_event_word) /*=0x20007b78*/, 1,
                              __ATOMIC_SEQ_CST);

    device = get_device_info();
    *(uint32_t *)(device + 0x104c) = 0x1d;
    device = get_device_info();
    k_sem_give(device + 0x68);
}
