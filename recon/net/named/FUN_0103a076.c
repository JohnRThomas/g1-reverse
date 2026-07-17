/* readable reconstruction; identity: FUN_0103a076 @ 0x0103a076
 * public-name: FUN_0103a076
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   atomic_set                               <= FUN_01039fb6 @ 0x01039fb6
 */
/* net-core FUN_0103a076 @ 0x103a076 */
#include <stdint.h>

extern void FUN_0102f580(void *);
extern void FUN_0103b62e(void *, uint32_t, uint32_t);
extern void atomic_set(volatile uint32_t *, uint32_t);

typedef int32_t (*prepare_fn)(void *, void *);
typedef int32_t (*attach_fn)(void *, void *, uint32_t);
typedef void (*init_fn)(void *, uint32_t);

int32_t FUN_0103a076(void *object)
{
    uint8_t *outer = object;
    uint8_t *state = *(uint8_t **)(outer + 0x10);
    uint8_t *configuration = *(uint8_t **)(outer + 4);
    volatile uint32_t *lock = (volatile uint32_t *)(state + 0x37c);

    uint32_t expected = 2;
    if (!__atomic_compare_exchange_n(lock, &expected, 1, 0,
                                     __ATOMIC_ACQ_REL, __ATOMIC_ACQUIRE))
        return -0x78;

    int32_t result = -0x10;
    if (state[0x64] || state[0xd4])
        return result;

    result = ((prepare_fn)(uintptr_t)0x0103a193u)
        (state, *(void **)(state + 0x378));
    if (result) {
        atomic_set(lock, 2);
        return result;
    }

    void *driver = *(void **)(configuration + 0x14);
    attach_fn attach = *(attach_fn *)(*(uint8_t **)((uint8_t *)driver + 8) + 0x10);
    if (!attach) {
        result = -0x58;
        atomic_set(lock, 2);
        return result;
    }
    result = attach(driver, *(void **)(configuration + 0x18), 0);
    if (result) {
        atomic_set(lock, 2);
        return result;
    }

    void *device = state + 0x2c0;
    ((init_fn)(uintptr_t)0x01036da5u)(device, 1);
    FUN_0102f580(device);

    void *buffer = state + 0x1c8;
    result = ((prepare_fn)(uintptr_t)0x0103a20du)
        (buffer, *(void **)configuration);
    if (result) {
        atomic_set(lock, 2);
        return result;
    }
    FUN_0103b62e(buffer, 0, 0xe8);
    FUN_0103b62e(state, 0, 0x1c4);
    atomic_set(lock, 0);
    return 0;
}
