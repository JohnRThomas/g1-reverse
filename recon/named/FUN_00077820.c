/* readable reconstruction; identity: FUN_00077820 @ 0x00077820
 * public-name: FUN_00077820
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   strlen                                   <= FUN_0000ef12 @ 0x0000ef12
 *   lock_acquire_or_fatal                    <= FUN_000510fc @ 0x000510fc
 *   lock_release_or_fatal                    <= FUN_00051134 @ 0x00051134
 *   stdio_streams_init                       <= FUN_00076bcc @ 0x00076bcc
 *   stdio_buffer_grow                        <= FUN_00077e70 @ 0x00077e70
 * address symbols (name @ address):
 *   rodata_f5400                             @ 0x000f5400
 */
/* Reconstructed internal function FUN_00077820 @ 0x77820.
 * Reachable code is [0x77820,0x778c4), 164 bytes.  Its four-word literal
 * pool is separately preserved at [0x778c4,0x778d4). */
#include <stdint.h>

extern int strlen(int value);
extern void lock_acquire_or_fatal(uint32_t lock);
extern void lock_release_or_fatal(uint32_t lock);
extern void stdio_streams_init(int context);
extern int stdio_buffer_grow(int context, int stream, void *iov_descriptor);

struct local_iov {
    uint32_t *items;
    uint32_t count;
    uint32_t remaining;
    uint32_t item[4];
};

int FUN_00077820(int context, int value)
{
    struct local_iov iov;
    int measured = strlen(value);
    int stream;

    iov.item[0] = (uint32_t)value;
    iov.item[1] = (uint32_t)measured;
    iov.item[2] = 0x000f5400u;
    iov.item[3] = 1;
    iov.items = iov.item;
    iov.count = 2;
    iov.remaining = (uint32_t)(measured + 1);

    if (context == 0) {
        /* The original performs a null load followed by UDF #0xff. */
        (void)*(volatile uint32_t *)(uintptr_t)8;
        __builtin_trap();
    }

    if (*(int *)(context + 0x18) == 0) {
        stdio_streams_init(context);
        stream = *(int *)(context + 8);
        if (*(int *)(context + 0x18) == 0)
            stdio_streams_init(context);
    } else {
        stream = *(int *)(context + 8);
    }

    if (stream == 0x0009871c)
        stream = *(int *)(context + 4);
    else if (stream == 0x000986fc)
        stream = *(int *)(context + 8);
    else if (stream == 0x000986dc)
        stream = *(int *)(context + 0xc);

    uint32_t state = *(uint32_t *)(stream + 0x64);
    uint16_t flags = *(uint16_t *)(stream + 0xc);
    if ((state & 1u) == 0 && (flags & 0x0200u) == 0)
        lock_acquire_or_fatal(*(uint32_t *)(stream + 0x58));

    int result = stdio_buffer_grow(context, stream, &iov.items) == 0 ? 10 : -1;

    state = *(uint32_t *)(stream + 0x64);
    flags = *(uint16_t *)(stream + 0xc);
    if ((state & 1u) == 0 && (flags & 0x0200u) == 0)
        lock_release_or_fatal(*(uint32_t *)(stream + 0x58));

    return result;
}
