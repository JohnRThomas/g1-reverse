/* readable reconstruction; identity: FUN_0102d708 @ 0x0102d708
 * public-name: FUN_0102d708
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0102d708 @ 0x102d708; true CFG extent 0x102d8a0 (408 bytes) */
#include <stdint.h>
extern uint32_t FUN_0103a056(uint32_t, uint32_t);
extern int FUN_0102db30(void *, uint32_t);
extern void FUN_01036cb8(void *);
extern void FUN_01036ce4(void *, void *, uint32_t, uint32_t, uint32_t);
extern void FUN_01036bec(void *, uint32_t);
extern int FUN_0102dac0(void *, uint32_t, uint32_t, uint32_t,
                        uint32_t, uint32_t, uint32_t, uint32_t);
extern int FUN_010357ec(void *);
extern void FUN_01039fb6(volatile uint32_t *, uint32_t);

int FUN_0102d708(uint8_t *owner)
{
    uint8_t *state = *(uint8_t **)(owner + 0x10);
    uint8_t *configuration = *(uint8_t **)(owner + 4);
    volatile uint32_t *lock = (volatile uint32_t *)(state + 0x37c);
    if (*lock != 0) return -120;
    *lock = 1;

    uint32_t count = 1;
    uint32_t required = *(uint32_t *)(configuration + 8) - 4;
    while (required > FUN_0103a056(count, *(uint32_t *)(configuration + 0x28)))
        ++count;
    if (count == 1) {
        FUN_01039fb6(lock, 2);
        return -12;
    }

    uint32_t slots = 1u << (31u - (uint32_t)__builtin_clz(count - 1));
    uint32_t header = (*(uint32_t *)(configuration + 4) + 7) & ~3u;
    *(uint32_t *)(state + 0x260) = header;
    *(uint32_t *)(state + 0x264) =
        FUN_0103a056(slots, *(uint32_t *)(configuration + 0x28));
    uint32_t payload = (slots * *(uint32_t *)(configuration + 0x28) + 3) & ~3u;
    uint32_t descriptors = ((slots * 18 + 9) & ~3u) + slots * 8;
    *(uint32_t *)(state + 0x258) = header + payload * 2;
    *(uint32_t *)(state + 0x254) = header + payload * 2 + descriptors + 8;
    *(uint32_t *)(state + 0x25c) = slots;
    *(uint32_t *)(state + 0x250) = *(uint32_t *)(configuration + 4);
    *(void **)(state + 0x2a4) = configuration;
    *(uint32_t *)(state + 0x2a8) = 0x0103a79f;

    uint8_t *buffer = state + 0x1c8;
    int result = FUN_0102db30(buffer, *(uint32_t *)configuration);
    if (result != 0) {
        FUN_01039fb6(lock, 0);
        return result;
    }

    uint8_t *device = state + 0x2c0;
    FUN_01036cb8(device);
    uint32_t limit = *(uint32_t *)(configuration + 0x20);
    if (*(uint32_t *)(configuration + 0x1c) == 1) limit -= 16;
    void *arena = (void *)(uintptr_t)(0x21007d80 +
                   0x440 * *(uint32_t *)(configuration + 0x24));
    FUN_01036ce4(device, arena, 0x400, limit, 0);
    FUN_01036bec(state + 0x2b0, 0x0103a785);

    void *driver = *(void **)(configuration + 0x14);
    void **operations = *(void ***)((uint8_t *)driver + 8);
    int (*open)(void *, void *, uint32_t, void *) =
        (int (*)(void *, void *, uint32_t, void *))operations[1];
    if (open == 0) result = -88;
    else result = open(driver, *(void **)(configuration + 0x18),
                       0x0103a779, state);
    if (result == 0) {
        int (*enable)(void *, void *, uint32_t) =
            (int (*)(void *, void *, uint32_t))operations[4];
        if (enable == 0) result = -88;
        else result = enable(driver, *(void **)(configuration + 0x18), 1);
    }
    if (result != 0) {
        FUN_01039fb6(lock, 0);
        return result;
    }

    *(uint32_t *)(state + 0x1a8) = 0x0102e0bd;
    *(uint32_t *)(state + 0x1ac) = 0x0103a92d;
    result = FUN_0102dac0(state, *(uint32_t *)(state + 0x378),
                           *(uint32_t *)(configuration + 0x28),
                           *(uint32_t *)(state + 0x268),
                           (uint32_t)(uintptr_t)buffer,
                           *(uint32_t *)(state + 0x208),
                           *(uint32_t *)(state + 0x210), 0x0103a7e7);
    if (result == 0) {
        result = FUN_010357ec(state + 0xe0);
        *(int *)(state + 0x380) = result;
        if (result < 0) result = -22;
    }
    FUN_01039fb6(lock, result == 0 ? 2 : 0);
    return result;
}
