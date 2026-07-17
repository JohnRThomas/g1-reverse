/* Reconstructed FUN_000818dc @ 0x818dc  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>

extern void FUN_0005f24c(uintptr_t);
extern void FUN_00073418(uintptr_t, unsigned, unsigned, unsigned);
extern uint64_t FUN_00081852(uintptr_t, int *, unsigned);
extern int thunk_FUN_000727ac(uintptr_t, unsigned, unsigned, unsigned);

void FUN_000818dc(uintptr_t owner, unsigned inherited_wait, unsigned unused)
{
    (void)unused;
    int item;
    for (;;) {
        item = *(volatile int *)(owner - 4);
        if (item == 0) {
            item = thunk_FUN_000727ac(owner - 0x20, inherited_wait, 0, 0);
            if (item == 0)
                return;
        } else {
            *(volatile int *)(owner - 4) = 0;
        }

        uint64_t result_pair = FUN_00081852(
            owner - 0x50, &item,
            **(volatile uint16_t **)(uintptr_t)(item + 0x18));
        int result = (int)(uint32_t)result_pair;
        if (result >= 0)
            continue;
        if (result == -11) {
            *(volatile int *)(owner - 4) = item;
            FUN_00073418(owner, (unsigned)(result_pair >> 32), 0x8000, 0);
            return;
        }
        FUN_0005f24c((uintptr_t)item);
        return;
    }
}
