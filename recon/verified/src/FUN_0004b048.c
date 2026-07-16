/* Full reconstruction of FUN_0004b048 @ 0x4b048 (58-byte extent). */
#include <stdint.h>

struct dispatch_slot {
    uint32_t object;
    uint32_t operations;
    uint32_t references;
    uint8_t lock_storage[0x1c];
};

void FUN_0004b048(uint32_t slot_index)
{
    volatile struct dispatch_slot *slot =
        (volatile struct dispatch_slot *)(uintptr_t)
        (UINT32_C(0x20002548) + slot_index * UINT32_C(0x28));
    uint32_t old_references;

    /* The firmware uses acquire/release exclusives for the reference drop. */
    old_references = __atomic_load_n(&slot->references, __ATOMIC_ACQUIRE);
    while (old_references != 0) {
        uint32_t expected = old_references;

        if (__atomic_compare_exchange_n(&slot->references, &expected,
                                        old_references - 1, 1,
                                        __ATOMIC_ACQ_REL, __ATOMIC_ACQUIRE)) {
            if (old_references == 1) {
                slot->object = 0;
                slot->operations = 0;
            }
            return;
        }
        old_references = expected;
    }
}
