/* readable reconstruction; identity: FUN_00016268 @ 0x00016268
 * public-name: runtime_info_sync
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   global_ipc_service_send                  <= FUN_00025b78 @ 0x00025b78
 * address symbols (name @ address):
 *   rodata_9957c                             @ 0x0009957c   [INLINED -- G6 literal batch]
 *   rodata_99bee                             @ 0x00099bee   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_esb_bringup_log_pending_flag           @ 0x20002fe0
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed runtime_info_sync @ 0x16268 */

#include <stdint.h>

struct __attribute__((packed)) runtime_sync_packet {
    uint16_t marker;
    uint8_t runtime[5];
    uint8_t reserved;
};

extern uint32_t global_ipc_service_send(const void *packet, uint32_t length);
extern void log_message(uint32_t format, uint32_t function_name, ...);
extern void debug_print(uint32_t format, uint32_t function_name, ...);

uint32_t runtime_info_sync(const uint8_t *runtime)
{
    struct runtime_sync_packet packet = {
        .marker = 1,
        .runtime = {runtime[0], runtime[1], runtime[2], runtime[3], runtime[4]},
        .reserved = 0,
    };

    uint32_t result = global_ipc_service_send(&packet, sizeof(packet));
    if (*(volatile uint8_t *)0x20002fe0UL != 0) {
        *(volatile uint8_t *)0x20002fe0UL = 0;
        if (*(volatile int32_t *)0x2000230cUL > 1) {
            if (*(volatile uint32_t *)0x20007554UL == 0) {
                log_message(0x0009957cUL, 0x00099beeUL,
                            runtime[0], runtime[1], runtime[2], result,
                            runtime[3], runtime[4]);
            } else {
                debug_print(0x0009957cUL, 0x00099beeUL,
                             runtime[0], runtime[1], runtime[2], result,
                             runtime[3], runtime[4]);
            }
        }
    }
    return result;
}
