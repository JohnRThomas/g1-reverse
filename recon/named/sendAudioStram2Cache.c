/* readable reconstruction; identity: FUN_0002f6b0 @ 0x0002f6b0
 * public-name: sendAudioStram2Cache
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   k_msgq_put                               <= FUN_000720d0 @ 0x000720d0
 *   k_sem_give                               <= FUN_00072880 @ 0x00072880
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_a3f45                             @ 0x000a3f45
 *   rodata_a42cf                             @ 0x000a42cf
 *   rodata_a4986                             @ 0x000a4986
 *   g_log_level                              @ 0x2000230c
 *   g_audio_msgq                             @ 0x20003890
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_app_language_msgq                      @ 0x200079e4
 */
/* Reconstructed sendAudioStram2Cache @ 0x2f6b0  (CFG-directed parity verified) */

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

struct audio_cache_record {
    uint8_t type;
    uint8_t reserved;
    uint16_t payload_length;
    uint8_t payload[200];
};

extern void log_message(uint32_t format, uint32_t module);
extern void debug_print(uint32_t format, uint32_t module);
extern int k_msgq_put(void *queue, const void *record, int timeout, int flags);
extern void k_sem_give(void *event);
extern void memcpy(void *destination, const void *source, int length);
extern void memset_bytes(void *destination, int value, int length);

#define AUDIO_CACHE_QUEUE       ((void *)0x20003890u)
#define AUDIO_CACHE_EVENT       ((void *)0x200079e4u)
#define LOG_LEVEL               (*(volatile int *)0x2000230cu)
#define DEFERRED_LOGGER_ENABLED (*(volatile int *)0x20007554u)

#define LOG_MODULE_AUDIO_CACHE  0x000a4986u
#define LOG_CACHE_FULL          0x000a42cfu
#define LOG_CACHE_SEND_FAILED   0x000a3f45u

uint32_t sendAudioStram2Cache(const void *audio_stream)
{
    struct audio_cache_record record;

    memset_bytes(&record, 0, sizeof(record));

    if (*(volatile int *)((uint8_t *)AUDIO_CACHE_QUEUE + 0x24) == 0x12) {
        if (LOG_LEVEL > 0) {
            if (DEFERRED_LOGGER_ENABLED == 0) {
                log_message(LOG_CACHE_FULL, LOG_MODULE_AUDIO_CACHE);
            } else {
                debug_print(LOG_CACHE_FULL, LOG_MODULE_AUDIO_CACHE);
            }
        }
        return 0xffffffffu;
    }

    memcpy(record.payload, audio_stream, sizeof(record.payload));
    record.payload_length = sizeof(record.payload);
    record.type = 2;

    if (k_msgq_put(AUDIO_CACHE_QUEUE, &record, 0, 0) == 0) {
        k_sem_give(AUDIO_CACHE_EVENT);
        return 0;
    }

    if (LOG_LEVEL > 0) {
        if (DEFERRED_LOGGER_ENABLED == 0) {
            log_message(LOG_CACHE_SEND_FAILED, LOG_MODULE_AUDIO_CACHE);
        } else {
            debug_print(LOG_CACHE_SEND_FAILED, LOG_MODULE_AUDIO_CACHE);
        }
    }
    return 0xffffffffu;
}
