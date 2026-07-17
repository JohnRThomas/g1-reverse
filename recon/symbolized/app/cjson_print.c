#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00064a88 @ 0x00064a88
 * public-name: cjson_print
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cjson_print_value                        <= FUN_000646c0 @ 0x000646c0
 *   cjson_print                              <= FUN_00064a88 @ 0x00064a88
 *   cursor_advance_past_cstring              <= FUN_00084f16 @ 0x00084f16
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   g_cjson_hooks                            @ 0x20002bac
 */
/* Reconstructed FUN_00064a88 @ 0x00064a88. */
#include <stdint.h>

typedef uintptr_t (*allocate_fn)(uint32_t size);
typedef void (*release_fn)(uintptr_t allocation);
typedef uintptr_t (*resize_fn)(uintptr_t allocation, uint32_t size);

struct allocator_ops {
    allocate_fn allocate;
    release_fn release;
    resize_fn resize;
};

struct encoded_buffer {
    uintptr_t data;
    uint32_t capacity;
    uint32_t length;
    uint32_t fields_0c_13[2];
    uint32_t context;
    allocate_fn allocate;
    release_fn release;
    resize_fn resize;
};

extern int cjson_print_value(uint32_t source, struct encoded_buffer *buffer);
extern void cursor_advance_past_cstring(struct encoded_buffer *buffer);
extern void memcpy(void *destination, const void *source, uint32_t size);
extern void memset_bytes(void *destination, int value, uint32_t size);

int cjson_print(uint32_t source, uint32_t context)
{
    const struct allocator_ops *ops =
        (const struct allocator_ops *)(uintptr_t)((unsigned long)&g_cjson_hooks) /*=0x20002bac*/;
    struct encoded_buffer buffer;

    memset_bytes(&buffer, 0, sizeof(buffer));
    buffer.data = ops->allocate(0x100);
    buffer.capacity = 0x100;
    buffer.allocate = ops->allocate;
    buffer.release = ops->release;
    buffer.resize = ops->resize;
    buffer.context = context;

    if (buffer.data != 0 && cjson_print_value(source, &buffer) != 0) {
        cursor_advance_past_cstring(&buffer);
        uint32_t required = buffer.length + 1;

        if (ops->resize != 0) {
            uintptr_t resized = ops->resize(buffer.data, required);
            if (resized != 0)
                return (int)resized;
        } else {
            uintptr_t result = ops->allocate(required);
            if (result != 0) {
                uint32_t copy_size = required;
                if (copy_size >= buffer.capacity)
                    copy_size = buffer.capacity;
                memcpy((void *)result, (const void *)buffer.data,
                             copy_size);
                *(uint8_t *)(result + buffer.length) = 0;
                ops->release(buffer.data);
                return (int)result;
            }
        }
    }

    if (buffer.data != 0)
        ops->release(buffer.data);
    return 0;
}
