/* Full reconstruction of FUN_0004f92c @ 0x4f92c (240 bytes). */
#include <stdint.h>

typedef struct {
    uint32_t reserved;
    uint32_t *owner;
    uint32_t index;
    int8_t operation;
} indexed_event;

typedef struct {
    uint32_t kind;
    uintptr_t label;
    uint32_t owner_value;
    uintptr_t indexed_value;
    uintptr_t operation_name;
    uint32_t encoding;
    uint16_t encoding_size;
} dispatch_record;

extern void FUN_0004d944(uintptr_t target, uint32_t command,
                        const dispatch_record *record, uint32_t zero);
extern void FUN_0007e2fa(uintptr_t domain, uintptr_t message,
                        uintptr_t file, uint32_t line);
extern void FUN_0007e2ec(uintptr_t file, uint32_t line) __attribute__((noreturn));

void FUN_0004f92c(const indexed_event *event)
{
    if (event->owner != (uint32_t *)0x000fa9e4u)
        __builtin_trap();

    if (event->index >= 2) {
        FUN_0007e2fa(0x00099cbdu, 0x000f18bdu, 0x000f1885u, 0x15u);
        FUN_0007e2ec(0x000f1885u, 0x15u);
    }
    if (event->operation > 2) {
        FUN_0007e2fa(0x00099cbdu, 0x000f18e0u, 0x000f1885u, 0x16u);
        FUN_0007e2ec(0x000f1885u, 0x16u);
    }
    if (event->operation < -1) {
        FUN_0007e2fa(0x00099cbdu, 0x000f18ffu, 0x000f1885u, 0x17u);
        FUN_0007e2ec(0x000f1885u, 0x17u);
    }

    static const uintptr_t operation_names[3] = {
        0x000f1941u, 0x000f1854u, 0x000f18fbu
    };
    uintptr_t operation_name = (event->operation >= 0 && event->operation <= 2)
        ? operation_names[(uint8_t)event->operation] : 0x000f191au;
    const uintptr_t *values = (const uintptr_t *)0x000faa2cu;
    dispatch_record record = {
        .kind = 0x03000005u,
        .label = 0x000f1920u,
        .owner_value = *event->owner,
        .indexed_value = values[event->index],
        .operation_name = operation_name,
        .encoding = 0x03010200u,
        .encoding_size = 0x0402u,
    };
    FUN_0004d944(0x000880f0u, 0x34c0u, &record, 0);
}
