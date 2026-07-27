/* Full reconstruction of FUN_0004f860 @ 0x4f860 (204 bytes). */
#include <stdint.h>

typedef struct {
    uint32_t reserved;
    uint32_t *owner;
    uint32_t *value;
    uint8_t operation;
} work_event;

typedef struct {
    uint32_t kind;
    uintptr_t label;
    uint32_t owner_value;
    uint32_t data_value;
    uintptr_t operation_name;
    uint32_t encoding;
    uint16_t encoding_size;
} dispatch_record;

extern void FUN_0004d944(uintptr_t target, uint32_t command,
                        const dispatch_record *record, uint32_t zero);
extern void FUN_0007e2fa(unsigned long, ...);
extern void FUN_0007e2ec(uintptr_t file, uint32_t line) __attribute__((noreturn));

void FUN_0004f860(const work_event *event)
{
    if (event->owner != (uint32_t *)0x000fa9b4u)
        __builtin_trap();

    if (event->operation >= 4) {
        FUN_0007e2fa(0x00099cbdu, 0x000f17a1u, 0x000f176au, 0x1cu);
        FUN_0007e2ec(0x000f176au, 0x1cu);
    }

    static const uintptr_t operation_names[4] = {
        0x000f184eu, 0x000f1854u, 0x000f1858u, 0x000f1860u
    };
    uintptr_t operation_name = operation_names[event->operation];
    if (operation_name == 0) {
        FUN_0007e2fa(0x00099cbdu, 0x000f17c3u, 0x000f176au, 0x1du);
        FUN_0007e2ec(0x000f176au, 0x1du);
    }
    if (event->value == 0) {
        FUN_0007e2fa(0x00099cbdu, 0x0009a1ddu, 0x000f17ebu, 0x51u);
        FUN_0007e2ec(0x000f17ebu, 0x51u);
    }

    dispatch_record record = {
        .kind = 0x03000005u,
        .label = 0x000f1823u,
        .owner_value = *event->owner,
        .data_value = *event->value,
        .operation_name = operation_name,
        .encoding = 0x03010200u,
        .encoding_size = 0x0402u,
    };
    FUN_0004d944(0x000880f0u, 0x34c0u, &record, 0);
}
