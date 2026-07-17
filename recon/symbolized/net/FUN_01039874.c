#include "g1_net_symbols.h"
/* net-core FUN_01039874 @ 0x1039874 */
#include <stdint.h>

extern uint32_t FUN_010397d2(uint32_t);
extern uint32_t FUN_01039768(void *, uint32_t);
extern uint32_t FUN_0103973c(void *, uint32_t, uint32_t);
extern void FUN_010397ea(void *, uint32_t, uint32_t);

uint32_t FUN_01039874(void *context, uint32_t required_size)
{
    uint8_t *base = context;
    uint32_t bucket = FUN_010397d2(*(uint32_t *)(base + 8));
    uint32_t *head = (uint32_t *)(base + 0x10 + bucket * 4u);
    uint32_t original = *head;
    if (original) {
        for (unsigned attempts = 0; attempts < 3; ++attempts) {
            uint32_t item = *head;
            if (FUN_01039768(context, item) >= required_size) {
                FUN_010397ea(context, item, bucket);
                return item;
            }
            *head = FUN_0103973c(context, item, 3);
            if (*head == original)
                break;
        }
    }

    uint32_t shift = (bucket + 1u) & 255u;
    uint32_t available = (shift < 32u ? 0xffffffffu << shift : 0u) &
                         *(uint32_t *)(base + 0x0c);
    if (!available)
        return 0;
    uint32_t next_bucket = (uint32_t)__builtin_ctz(available);
    uint32_t item = *(uint32_t *)(base + (next_bucket + 4u) * 4u);
    FUN_010397ea(context, item, bucket + 1u);
    return item;
}
