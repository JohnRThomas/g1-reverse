/* readable reconstruction; identity: FUN_00074b7c @ 0x00074b7c
 * public-name: next_timeout
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   rtc_get_elapsed_cycles_since_baseline    <= FUN_00074b68 @ 0x00074b68
 * address symbols (name @ address):
 *   g_20002cfc                               @ 0x20002cfc
 */
/* Reconstructed Zephyr next_timeout @ 0x00074b7c.
 * Raw/address back-map: FUN_00074b7c / 0x00074b7c.
 */
#include <stdint.h>
#include <limits.h>

struct timeout_node {
    uint8_t reserved[0x10];
    int64_t dticks;
};

extern int32_t rtc_get_elapsed_cycles_since_baseline(void);

int32_t next_timeout(void)
{
    struct timeout_node *const *head =
        (struct timeout_node *const *)0x20002cfcu;
    struct timeout_node *timeout = *head;
    int32_t elapsed = rtc_get_elapsed_cycles_since_baseline();

    if ((timeout == (struct timeout_node *)head) || timeout == 0) {
        return INT32_MAX;
    }

    int64_t remaining = timeout->dticks - elapsed;
    if (remaining > INT32_MAX) {
        return INT32_MAX;
    }
    return remaining < 0 ? 0 : (int32_t)remaining;
}
