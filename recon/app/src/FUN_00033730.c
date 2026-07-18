/* CPUAPP send_notification_app_whitelist @ 0x00033730.
 * Raw/back-map identity: FUN_00033730, exact extent 0x11c bytes. */
#include <stdint.h>

#define send_notification_app_whitelist FUN_00033730

extern void FUN_00086c78(void *destination, uint32_t value, uint32_t size);
extern void FUN_00086c1e(void *destination, const void *source,
                         uint32_t size, uint32_t destination_size);
extern uint32_t FUN_00086f00(void *destination, uint32_t append,
                             uint32_t capacity, uintptr_t format, ...);
extern void FUN_00074844(uint32_t ticks, uint32_t unused);
extern void DEBUG_PRINT(uintptr_t format, ...);
extern void FUN_00019c70(uintptr_t format, ...);

#define LOG_ROUTE (*(volatile uint32_t *)0x20007554u)

uint32_t send_notification_app_whitelist(uint8_t *transport,
                                         const char *identifier,
                      const char *display_name, uint32_t unused)
{
    uint8_t packet[22];
    char text[320];
    uint32_t text_size;
    uint8_t chunk_count;
    uint8_t chunk_index = 0u;
    uint8_t retry_count = 0u;

    (void)unused;
    *(uint32_t *)(void *)packet = 0u;
    FUN_00086c78(packet + 4, 0u, 0x11u);
    FUN_00086c78(text, 0u, sizeof(text));
    text_size = FUN_00086f00(text, 0u, sizeof(text), 0x000a7b64u,
                             0x0009d759u, identifier,
                             0x0009d790u, display_name);
    if (LOG_ROUTE == 0u)
        DEBUG_PRINT(0x000a7b94u, text);
    else
        FUN_00019c70(0x000a7b94u, text);

    chunk_count = (uint8_t)((text_size & 0xffffu) / 0x11u);
    if ((text_size & 0xffffu) % 0x11u != 0u)
        chunk_count = (uint8_t)(chunk_count + 1u);

    while (chunk_index < chunk_count) {
        uint8_t chunk_size = (uint8_t)(text_size + 0x11u -
                                       (uint32_t)chunk_count * 0x11u);
        int32_t result;
        if (chunk_index < (uint8_t)(chunk_count - 1u))
            chunk_size = 0x11u;
        FUN_00086c78(packet + 3, 0u, 0x12u);
        packet[0] = 0xf6u;
        packet[1] = chunk_count;
        packet[2] = chunk_index;
        FUN_00086c1e(packet + 3, text + (uint32_t)chunk_index * 0x11u,
                     chunk_size, 0x12u);
        result = ((int32_t (*)(const void *, uint32_t))
                  *(volatile uintptr_t *)(transport + 0x0c))
                 (packet, (uint32_t)chunk_size + 3u);
        if (result == 0) {
            retry_count = 0u;
            chunk_index = (uint8_t)(chunk_index + 1u);
        } else {
            retry_count = (uint8_t)(retry_count + 1u);
            if (retry_count == 6u) {
                if (LOG_ROUTE == 0u)
                    DEBUG_PRINT(0x000a7bccu);
                else
                    FUN_00019c70(0x000a7bccu);
                return 0u;
            }
        }
        FUN_00074844(0xa4u, 0u);
    }
    return 0u;
}
