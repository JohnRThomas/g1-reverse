/* Full reconstruction FUN_00067304 @ 0x00067304 (498-byte exact extent). */
#include <stdint.h>

extern void FUN_0007e2fa(unsigned long, ...);
extern void FUN_0007e2ec(uintptr_t, uint32_t) __attribute__((noreturn));
extern void FUN_0008523e(void *, uint32_t, const void *);
extern void FUN_000852ba(void *, void *);
extern void FUN_000852e6(void);
extern void FUN_000852fe(void);

static void fatal(uintptr_t message, uint32_t line)
{
    FUN_0007e2fa(0x00099cbdu, message, 0x000f6df0u, line);
    FUN_0007e2ec(0x000f6df0u, line);
}

uint32_t FUN_00067304(uint32_t *owner, const uint32_t descriptor[4],
                      uint32_t flags, uint32_t fourth)
{
    volatile uint8_t *channels = (volatile uint8_t *)0x2000b384u;
    uint32_t channel = *((uint8_t *)owner + 4);
    volatile uint8_t *state = channels + channel * 0x24u;
    uint32_t saved[4] = {(uint32_t)(uintptr_t)owner,
                         (uint32_t)(uintptr_t)descriptor, flags, fourth};

    if (!state[0x1c]) fatal(0x000f6e3au, 0x314);
    if (!descriptor[0] && descriptor[1]) fatal(0x000f6e66u, 0x315);
    int shift = *(const int8_t *)(0x000f6fd9u + channel);
    if ((!descriptor[2] && descriptor[3]) ||
        (descriptor[2] ? (descriptor[3] >> shift) : (descriptor[1] >> shift)))
        fatal(descriptor[2] ? 0x000f6ef4u : 0x000f6eadu,
              descriptor[2] ? 0x317u : 0x316u);
    if ((flags & 8u) && *(volatile int32_t *)(state + 0x20) != -1)
        fatal(0x000f6fa3u, 0x31au);

    if (state[0x1d]) return 0x0bad000bu;
    if (*(volatile uint32_t *)state && !(flags & 0x14u)) state[0x1d] = 1;
    ((volatile uint32_t *)state)[3] = descriptor[0];
    ((volatile uint32_t *)state)[4] = descriptor[1];
    ((volatile uint32_t *)state)[5] = descriptor[2];
    ((volatile uint32_t *)state)[6] = descriptor[3];

    if (*(volatile int32_t *)(state + 0x20) != -1) {
        if (state[0x1f]) FUN_000852e6(); else FUN_000852fe();
    }
    uint8_t *object = (uint8_t *)(uintptr_t)*owner;
    if ((descriptor[0] && (descriptor[0] & 0xe0000000u) != 0x20000000u) ||
        (descriptor[2] && (descriptor[2] & 0xe0000000u) != 0x20000000u)) {
        state[0x1d] = 0;
        return 0x0bad000au;
    }

    *(uint32_t *)(object + 0x550) = !!(flags & 1u);
    *(uint32_t *)(object + 0x540) = !!(flags & 2u);
    *(uint32_t *)(object + 0x544) = descriptor[0];
    *(uint32_t *)(object + 0x548) = descriptor[1];
    *(uint32_t *)(object + 0x534) = descriptor[2];
    *(uint32_t *)(object + 0x538) = descriptor[3];
    *(uint32_t *)(object + 0x118) = 0;
    *(uint32_t *)(object + 0x500) = 7;

    if (!(flags & 8u)) {
        *(uint32_t *)(object + 0x10) = 1;
        if (!*(volatile uint32_t *)state) {
            while (!*(volatile uint32_t *)(object + 0x118)) { }
            FUN_0008523e(object, 0x40, saved);
        }
        if (!*(volatile uint32_t *)state) {
            if (*(volatile int32_t *)(state + 0x20) != -1) {
                if (state[0x1f]) FUN_000852fe(); else FUN_000852e6();
            }
            FUN_000852ba(object, (void *)state);
            return 0x0bad0000u;
        }
    } else if (!*(volatile uint32_t *)state) {
        if (*(volatile int32_t *)(state + 0x20) != -1) {
            if (state[0x1f]) FUN_000852fe(); else FUN_000852e6();
        }
        return 0x0bad0000u;
    }
    if (flags & 4u) *(uint32_t *)(object + 0x308) = 0x40;
    else *(uint32_t *)(object + 0x304) = 0x40;
    return 0x0bad0000u;
}
