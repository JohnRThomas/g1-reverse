#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004e2b4 @ 0x0004e2b4
 * public-name: stream_flash_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_log_msg_runtime_create                 <= FUN_0004d944 @ 0x0004d944
 *   stream_flash_init                        <= FUN_0004e2b4 @ 0x0004e2b4
 *   stream_flash_vtable_get_value            <= FUN_0007f064 @ 0x0007f064
 *   flash_page_foreach                       <= FUN_00083ac2 @ 0x00083ac2
 * address symbols (name @ address):
 *   rodata_7f071                             @ 0x0007f071
 *   rodata_880d8                             @ 0x000880d8
 *   rodata_f10ce                             @ 0x000f10ce   [INLINED -- G6 literal batch]
 *   rodata_f1105                             @ 0x000f1105
 */
/* Reconstructed FUN_0004e2b4 @ 0x4e2b4  owned extent: 0xae bytes */

#include <stdint.h>

struct buffered_writer {
    uint8_t *buffer;
    uint32_t capacity;
    uint32_t count;
    void *device;
    uint32_t committed;
    uint32_t base;
    uint32_t limit;
    int (*transform)(uint8_t *buffer, uint32_t count, uint32_t offset);
    int32_t state;
};

struct device_geometry {
    uint32_t requested;
    uint32_t available;
};

struct diagnostic_record {
    uint32_t severity;
    uintptr_t message;
};

extern uint32_t stream_flash_vtable_get_value(void *device);
extern void flash_page_foreach(void *device, uintptr_t query,
                         struct device_geometry *geometry);
extern void z_log_msg_runtime_create(uintptr_t source, uint32_t event,
                         const struct diagnostic_record *record,
                         uint32_t reserved);

int stream_flash_init(struct buffered_writer *writer, void *device,
                 uint8_t *buffer, uint32_t capacity, uint32_t base,
                 uint32_t limit,
                 int (*transform)(uint8_t *, uint32_t, uint32_t))
{
    struct device_geometry geometry = {
        .requested = capacity,
        .available = 0,
    };
    uintptr_t message;
    uint32_t unit;

    if (writer == 0 || device == 0 || buffer == 0)
        return -14;

    unit = stream_flash_vtable_get_value(device);
    if (capacity % unit != 0) {
        message = ((unsigned long)"Buffer size is not aligned to minimal write-block-size") /*=0xf10ce*/;
        goto invalid;
    }

    flash_page_foreach(device, ((unsigned long)&rodata_7f071) /*=0x7f071*/, &geometry);
    if (geometry.available == 0)
        return -14;

    if (geometry.available < base + limit ||
        (unit = stream_flash_vtable_get_value(device), base % unit != 0)) {
        message = ((unsigned long)&rodata_f1105) /*=0xf1105*/;
        goto invalid;
    }

    writer->buffer = buffer;
    writer->capacity = capacity;
    writer->device = device;
    writer->committed = 0;
    writer->count = 0;
    writer->base = base;
    writer->transform = transform;
    writer->limit = limit != 0 ? limit : geometry.available - base;
    writer->state = -1;
    return 0;

invalid:
    {
        struct diagnostic_record diagnostic = {
            .severity = 2,
            .message = message,
        };
        z_log_msg_runtime_create(((unsigned long)&rodata_880d8) /*=0x880d8*/, 0x1040u, &diagnostic, 0);
    }
    return -14;
}
