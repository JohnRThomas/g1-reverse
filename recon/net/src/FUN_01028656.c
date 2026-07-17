/* net-core FUN_01028656 @ 0x1028656  (CFG-directed candidate) */
#include <stdint.h>
#include <stdbool.h>

struct controller_handle_ref {
    uint8_t kind;
    uint8_t reserved[3];
    uint32_t object;
};
struct controller_bounds {
    uint16_t handle;
    uint16_t interval_min;
    uint16_t latency_min;
    uint16_t interval_max;
    uint16_t latency_max;
};

extern uint32_t controller_handle_lookup(uint16_t, struct controller_handle_ref *); /* =FUN_0100cfc0 */
extern uintptr_t controller_connection_config_get(const struct controller_handle_ref *); /* =FUN_010282a6 */
extern uintptr_t controller_object_get(const struct controller_handle_ref *); /* =FUN_010282a2 */
extern void controller_default_bounds_build(uintptr_t, bool, struct controller_bounds *); /* =FUN_010282fc */

uint32_t FUN_01028656(const uint16_t *requested)
{
    struct controller_handle_ref handle_ref;
    struct controller_bounds defaults;
    uint32_t result = controller_handle_lookup(requested[0], &handle_ref);
    uintptr_t root;
    uintptr_t config;
    bool active;
    bool special = false;

    if (result != 0u)
        return result;

    config = controller_connection_config_get(&handle_ref);
    root = handle_ref.object;
    active = *(volatile uint8_t *)(root + 0x1eau) != 0u;

    if (handle_ref.kind == 0u) {
        if (*(volatile uint8_t *)(config + 0x1eu) == 0x1fu)
            special = !active;
    } else if ((*(volatile uint32_t *)(config + 0x0cu) & 0x20u) != 0u) {
        special = !active;
    }

    if (((*(volatile uint8_t *)(config + 0x6eu) & 0x20u) == 0u) && !special)
        return 0x1au;

    if ((uint16_t)(requested[3] - 0x1bu) > 0xe0u ||
        (uint16_t)(requested[4] - 0x148u) > 0x4148u ||
        (uint16_t)(requested[1] - 0x1bu) > 0xe0u ||
        (uint16_t)(requested[2] - 0x148u) > 0x4148u)
        return 0x12u;

    if (requested[4] > 0xa90u || requested[2] > 0xa90u)
        return 0x11u;

    root = controller_object_get(&handle_ref);
    *(volatile uint8_t *)(root + 0x163u) = 0xffu;
    if (active) {
        result = 0x3au;
    } else {
        uint16_t value;
        controller_default_bounds_build(root, handle_ref.kind == 0u, &defaults);

        value = defaults.interval_max;
        if (requested[1] <= value)
            value = requested[1];
        *(volatile uint16_t *)(root + 0x168u) = value;

        value = defaults.latency_max;
        if (value > 0x847u)
            value = 0x848u;

        {
            uint16_t low = defaults.interval_min;
            if (requested[3] <= low)
                low = requested[3];
            *(volatile uint16_t *)(root + 0x164u) = low;
        }

        {
            uint16_t low = defaults.latency_min;
            if (low > 0x847u)
                low = 0x848u;
            if (requested[4] <= low)
                low = requested[4];
            *(volatile uint16_t *)(root + 0x166u) = low;
        }

        if (defaults.latency_max <= requested[2])
            value = defaults.latency_max;
        else
            value = requested[2];
        *(volatile uint16_t *)(root + 0x16au) = value;
        *(volatile uint8_t *)(root + 0x162u) = 0xffu;
        result = 0u;
    }
    *(volatile uint8_t *)(root + 0x163u) = 0u;
    return result;
}
