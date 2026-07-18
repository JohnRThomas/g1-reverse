/* Reconstructed libmetal metal_bus_unregister @ 0x000680f8.
 * Raw/address back-map: metal_bus_unregister <= FUN_000680f8 @ 0x000680f8.
 */
#include <stdint.h>

struct metal_bus_raw;

struct metal_list_raw {
    struct metal_list_raw *next;
    struct metal_list_raw *prev;
};

struct metal_bus_raw {
    const char *name;
    void (*bus_close)(struct metal_bus_raw *bus);
    uint8_t reserved[0x1c];
    struct metal_list_raw node;
};

typedef void (*metal_log_handler_raw)(uint32_t level, const char *format, ...);

struct metal_log_state_raw {
    uint8_t level;
    uint8_t reserved[3];
    metal_log_handler_raw handler;
};

#define METAL_LOG_STATE ((volatile struct metal_log_state_raw *)0x2000b424u)
#define METAL_LOG_DEBUG 7u
#define METAL_BUS_UNREGISTERED_FORMAT ((const char *)0x000f7a8au)

#define metal_bus_unregister FUN_000680f8
int metal_bus_unregister(struct metal_bus_raw *bus)
{
    struct metal_list_raw *next = bus->node.next;
    struct metal_list_raw *prev = bus->node.prev;

    next->prev = prev;
    prev->next = next;
    bus->node.next = &bus->node;
    bus->node.prev = &bus->node;

    if (bus->bus_close != 0) {
        bus->bus_close(bus);
    }

    if (METAL_LOG_STATE->level > 6u && METAL_LOG_STATE->handler != 0) {
        METAL_LOG_STATE->handler(METAL_LOG_DEBUG,
                                 METAL_BUS_UNREGISTERED_FORMAT, bus->name);
    }
    return 0;
}
