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

extern void DEBUG_PRINT(uint32_t format, uint32_t module);
extern void FUN_00019c70(uint32_t format, uint32_t module);
extern int FUN_000720d0(void *queue, const void *record, int timeout, int flags);
extern void FUN_00072880(void *event);
extern void FUN_00086c04(void *destination, const void *source, int length);
extern void FUN_00086c78(void *destination, int value, int length);

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

    FUN_00086c78(&record, 0, sizeof(record));

    if (*(volatile int *)((uint8_t *)AUDIO_CACHE_QUEUE + 0x24) == 0x12) {
        if (LOG_LEVEL > 0) {
            if (DEFERRED_LOGGER_ENABLED == 0) {
                DEBUG_PRINT(LOG_CACHE_FULL, LOG_MODULE_AUDIO_CACHE);
            } else {
                FUN_00019c70(LOG_CACHE_FULL, LOG_MODULE_AUDIO_CACHE);
            }
        }
        return 0xffffffffu;
    }

    FUN_00086c04(record.payload, audio_stream, sizeof(record.payload));
    record.payload_length = sizeof(record.payload);
    record.type = 2;

    if (FUN_000720d0(AUDIO_CACHE_QUEUE, &record, 0, 0) == 0) {
        FUN_00072880(AUDIO_CACHE_EVENT);
        return 0;
    }

    if (LOG_LEVEL > 0) {
        if (DEFERRED_LOGGER_ENABLED == 0) {
            DEBUG_PRINT(LOG_CACHE_SEND_FAILED, LOG_MODULE_AUDIO_CACHE);
        } else {
            FUN_00019c70(LOG_CACHE_SEND_FAILED, LOG_MODULE_AUDIO_CACHE);
        }
    }
    return 0xffffffffu;
}
