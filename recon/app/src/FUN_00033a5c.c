/* Reconstructed FUN_00033a5c @ 0x33a5c.
 * Readable identity: get_notification_counts_cmd_response.
 * Exact standalone extent: 0x4c bytes; literal pool begins at 0x33aa8.
 */

#include <stdint.h>

extern int log_message(uintptr_t format, ...);
extern int FUN_00019c70(uintptr_t format, ...);
#define debug_print FUN_00019c70

uint32_t FUN_00033a5c(const uint8_t *notification,
                      uint8_t *unread_count)
{
    int32_t level;
    uint32_t sink;
    uint8_t count;

    if (notification == 0 || unread_count == 0) {
        level = *(volatile uint32_t *)0x2000230cUL;
        if (level > 1) {
            sink = *(volatile uint32_t *)0x20007554UL;
            if (sink == 0U) {
                log_message(0x000a7cd6UL, 0x000a829fUL);
            } else {
                debug_print(0x000a7cd6UL, 0x000a829fUL);
            }
        }
        return 0;
    }

    count = notification[0xdd];
    *unread_count = count;
    level = *(volatile uint32_t *)0x2000230cUL;
    if (level > 2) {
        sink = *(volatile uint32_t *)0x20007554UL;
        if (sink == 0U) {
            log_message(0x000a7cf4UL, 0x000a829fUL, count);
        } else {
            debug_print(0x000a7cf4UL, 0x000a829fUL, count);
        }
    }
    return 1;
}
