/* net-core FUN_0102ab50 @ 0x0102ab50
 * Readable identity: g1_ipc_endpoint_register.
 * Raw back-map: FUN_0102acb4 stores runtime Thumb pointer 0x0102b351.
 */
#include <stdint.h>

#define g1_ipc_endpoint_register FUN_0102ab50

extern void FUN_01039722(const char *format, ...);

struct g1_ipc_endpoint {
    uint8_t id;
    uint8_t reserved[3];
    const char *name;
};

struct g1_ipc_registry {
    uint32_t reserved;
    int32_t count;
    const struct g1_ipc_endpoint *entries[22];
};

int g1_ipc_endpoint_register(const struct g1_ipc_endpoint *endpoint)
{
    struct g1_ipc_registry *registry =
        *(struct g1_ipc_registry * volatile *)0x21004604u;
    int32_t count = registry->count;
    int32_t level = *(volatile int32_t *)0x21000580u;

    if (count <= 21) {
        registry->entries[count] = endpoint;
        registry->count = count + 1;
        if (level > 1)
            FUN_01039722((const char *)0x0103ce0du,
                          endpoint->id, endpoint->name, count + 1);
        return 0;
    }

    if (level > 0)
        FUN_01039722((const char *)0x0103ce35u,
                      endpoint->id, endpoint->name, count, 22u);
    return -1;
}
