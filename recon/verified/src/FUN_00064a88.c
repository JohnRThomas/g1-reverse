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

extern int FUN_000646c0(uint32_t source, struct encoded_buffer *buffer);
extern void FUN_00084f16(struct encoded_buffer *buffer);
extern void FUN_00086c04(void *destination, const void *source, uint32_t size);
extern void FUN_00086c78(void *destination, int value, uint32_t size);

int FUN_00064a88(uint32_t source, uint32_t context)
{
    const struct allocator_ops *ops =
        (const struct allocator_ops *)(uintptr_t)0x20002bac;
    struct encoded_buffer buffer;

    FUN_00086c78(&buffer, 0, sizeof(buffer));
    buffer.data = ops->allocate(0x100);
    buffer.capacity = 0x100;
    buffer.allocate = ops->allocate;
    buffer.release = ops->release;
    buffer.resize = ops->resize;
    buffer.context = context;

    if (buffer.data != 0 && FUN_000646c0(source, &buffer) != 0) {
        FUN_00084f16(&buffer);
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
                FUN_00086c04((void *)result, (const void *)buffer.data,
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
