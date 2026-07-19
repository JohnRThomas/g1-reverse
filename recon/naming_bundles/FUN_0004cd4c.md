### FUN_0004cd4c  @ 0x0004cd4c  (size=404)

callers (0): (none / root or address-taken)
callees (8): FUN_0004d100, ipc_static_vrings_init, FUN_00071314, k_work_init, k_work_queue_init, k_work_queue_start, atomic_set, shm_size

```c
/* readable reconstruction; identity: FUN_0004cd4c @ 0x0004cd4c
 * public-name: FUN_0004cd4c
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ipc_static_vrings_init                   <= FUN_0004d170 @ 0x0004d170
 *   k_work_init                              <= FUN_00072e50 @ 0x00072e50
 *   k_work_queue_init                        <= FUN_000730b4 @ 0x000730b4
 *   k_work_queue_start                       <= FUN_000730e8 @ 0x000730e8
 *   atomic_set                               <= FUN_0007eb4e @ 0x0007eb4e
 *   shm_size                                 <= FUN_0007ebee @ 0x0007ebee
 * address symbols (name @ address):
 *   ADDR_bound_cb_THUMB                      @ 0x0004cefd
 *   rodata_7eb11                             @ 0x0007eb11
 *   rodata_7eb1d                             @ 0x0007eb1d
 *   rodata_7eb37                             @ 0x0007eb37
 *   ADDR_FUN_0007eb7e_THUMB                  @ 0x0007eb7f
 *   ADDR_ept_cb_THUMB                        @ 0x0007ecc5
 */
/* Full reconstruction of FUN_0004cd4c @ 0x4cd4c (404 bytes). */
#include <stdint.h>

extern uint64_t shm_size(uint32_t, uint32_t);
extern int32_t ipc_static_vrings_init(uintptr_t, uint32_t);
extern void k_work_queue_init(uintptr_t);
extern void k_work_queue_start(uintptr_t, uintptr_t, uint32_t, uint32_t, uint32_t);
extern void k_work_init(uintptr_t, uintptr_t);
extern int32_t FUN_0004d100(uintptr_t, uint32_t, uint32_t, uint32_t,
                           uintptr_t, uint32_t, uint32_t, uintptr_t);
extern int32_t FUN_00071314(uintptr_t);
extern void atomic_set(volatile uint32_t *, uint32_t);

typedef int32_t (*open_fn)(uintptr_t, uint32_t, uintptr_t, uintptr_t);
typedef int32_t (*enable_fn)(uintptr_t, uint32_t, uint32_t);

int32_t FUN_0004cd4c(uintptr_t context)
{
    uintptr_t runtime = *(volatile uintptr_t *)(context + 0x10);
    uintptr_t config = *(volatile uintptr_t *)(context + 4);
    volatile uint32_t *busy = (volatile uint32_t *)(runtime + 0x3bc);
    uint32_t expected = 0;
    if (!__atomic_compare_exchange_n(busy, &expected, 1, 0,
                                     __ATOMIC_ACQ_REL, __ATOMIC_ACQUIRE))
        return -120;

    uint32_t slots = 1;
    uint32_t available = *(volatile uint32_t *)(config + 8) - 4u;
    uint32_t quantum = *(volatile uint32_t *)(config + 0x28);
    while ((uint32_t)shm_size(slots, quantum) < available)
        ++slots;

    int32_t result;
    if (slots == 1) {
        result = -12;
    } else {
        uint32_t lanes = 0x80000000u >> __builtin_clz(slots - 1u);
        uint32_t header = (*(volatile uint32_t *)(config + 4) + 7u) & ~3u;
        *(volatile uint32_t *)(runtime + 0x260) = header;
        *(volatile uint32_t *)(runtime + 0x264) = (uint32_t)shm_size(lanes, quantum);
        uint32_t payload = header + (((lanes * quantum + 3u) & ~3u) << 1);
        *(volatile uint32_t *)(runtime + 0x258) = payload;
        *(volatile uint32_t *)(runtime + 0x254) =
            payload + ((lanes * 18u + 9u) & ~3u) + lanes * 8u + 8u;
        *(volatile uint32_t *)(runtime + 0x25c) = lanes;
        *(volatile uint32_t *)(runtime + 0x250) = *(volatile uint32_t *)(config + 4);
        *(volatile uintptr_t *)(runtime + 0x2a4) = config;
        *(volatile uintptr_t *)(runtime + 0x2a8) = 0x0007eb37u;

        result = ipc_static_vrings_init(runtime + 0x1c8, *(volatile uint32_t *)config);
        if (result == 0) {
            uint32_t buffer_size = *(volatile uint32_t *)(config + 0x20);
            if (*(volatile uint32_t *)(config + 0x1c) == 1)
                buffer_size -= 0x10;
            k_work_queue_init(runtime + 0x2c0);
            k_work_queue_start(runtime + 0x2c0,
                         0x2002a268u + (*(volatile uint32_t *)(config + 0x24) << 10),
                         0x400, buffer_size, 0);
            k_work_init(runtime + 0x2b0, 0x0007eb1du);

            uintptr_t device = *(volatile uintptr_t *)(config + 0x14);
            uintptr_t ops = *(volatile uintptr_t *)(device + 8);
            open_fn open = *(open_fn *)(ops + 4);
            if (!open) {
                result = -88;
            } else {
                result = open(device, *(volatile uint32_t *)(config + 0x18),
                              0x0007eb11u, runtime);
                if (result == 0) {
                    enable_fn enable = *(enable_fn *)(ops + 0x10);
                    if (!enable) {
                        result = -88;
                    } else {
                        result = enable(device, *(volatile uint32_t *)(config + 0x18), 1);
                        if (result == 0) {
                            *(volatile uintptr_t *)(runtime + 0x1a8) = 0x0004cefdu;
                            *(volatile uintptr_t *)(runtime + 0x1ac) = 0x0007ecc5u;
                            result = FUN_0004d100(runtime,
                                *(volatile uint32_t *)(runtime + 0x3b8), quantum,
                                *(volatile uint32_t *)(runtime + 0x268), runtime + 0x1c8,
                                *(volatile uint32_t *)(runtime + 0x208),
                                *(volatile uint32_t *)(runtime + 0x210), 0x0007eb7fu);
                            if (result == 0) {
                                int32_t handle = FUN_00071314(runtime + 0xe0);
                                *(volatile int32_t *)(runtime + 0x3c0) = handle;
                                result = handle < 0 ? -22 : 0;
                            }
                        }
                    }
                }
            }
        }
    }
    atomic_set(busy, result == 0 ? 2u : 0u);
    return result;
}
```