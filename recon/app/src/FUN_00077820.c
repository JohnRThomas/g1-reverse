/* Reconstructed internal function FUN_00077820 @ 0x77820.
 * Reachable code is [0x77820,0x778c4), 164 bytes.  Its four-word literal
 * pool is separately preserved at [0x778c4,0x778d4). */
#include <stdint.h>

extern int FUN_0000ef12(int value);
extern void FUN_000510fc(uint32_t lock);
extern void FUN_00051134(uint32_t lock);
extern void FUN_00076bcc(int context);
extern int FUN_00077e70(int context, int stream, void *iov_descriptor);

struct local_iov {
    uint32_t *items;
    uint32_t count;
    uint32_t remaining;
    uint32_t item[4];
};

int FUN_00077820(int context, int value)
{
    struct local_iov iov;
    int measured = FUN_0000ef12(value);
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
        FUN_00076bcc(context);
        stream = *(int *)(context + 8);
        if (*(int *)(context + 0x18) == 0)
            FUN_00076bcc(context);
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
        FUN_000510fc(*(uint32_t *)(stream + 0x58));

    int result = FUN_00077e70(context, stream, &iov.items) == 0 ? 10 : -1;

    state = *(uint32_t *)(stream + 0x64);
    flags = *(uint16_t *)(stream + 0xc);
    if ((state & 1u) == 0 && (flags & 0x0200u) == 0)
        FUN_00051134(*(uint32_t *)(stream + 0x58));

    return result;
}
