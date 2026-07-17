/* net-core FUN_0103547c @ 0x0103547c */
#include <stdint.h>

extern void FUN_0103b5a4(uint32_t, uint32_t, uint32_t);

void FUN_0103547c(uint32_t list_head, uint32_t object, uint32_t name,
                  uint32_t callback, uint32_t callback_arg,
                  uint32_t option_a, uint32_t option_b)
{
    uint32_t link;
    volatile uint32_t *fields = (volatile uint32_t *)(uintptr_t)object;

    if (name == 0u) {
        name = 0x0103cf0au;
    }
    FUN_0103b5a4(object, name, 0x20u);
    fields[9] = callback;
    fields[10] = callback_arg;
    fields[8] = list_head;
    fields[11] = option_a;
    fields[12] = option_b;

    link = object + 0x34u;
    fields[13] = list_head;
    fields[14] = *(uint32_t *)(uintptr_t)(list_head + 4u);
    *(uint32_t *)(uintptr_t)(list_head + 4u) = link;
    *(volatile uint32_t *)(uintptr_t)fields[14] = link;
}
