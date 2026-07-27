/* ABI-faithful reconstruction of FUN_0008349c @ 0x8349c. */
#include <stdint.h>

/* The allocator helper returns its object in r0.  Its otherwise-unspecified
 * r1 half is deliberately represented as part of the call result so the
 * compiler observes the original r1:r0 return ABI. */
extern uint64_t FUN_0005caa4(uint32_t kind);
extern int FUN_0005cc68(int);
extern int FUN_0005d0ac(int);
extern void FUN_0005dc2c(void *object, int32_t reason);
extern uint32_t FUN_00082ff6(const void *bits, uint32_t bit);
extern void FUN_0008304c(void *bits, uint32_t bit);
extern void FUN_00083090(void *bits, uint32_t bit);

static inline void *low_pointer(uint64_t result)
{
    return (void *)(uintptr_t)(uint32_t)result;
}

void FUN_0008349c(const uint32_t source[8])
{
    void *object = low_pointer(FUN_0005caa4(8));

    if (object != 0) {
        void *state = (uint8_t *)object + 4;

        FUN_0008304c(state, 8);
        if (source == 0) {
            FUN_0005dc2c(object, 11);
        } else {
            uint32_t *destination = (uint32_t *)((uint8_t *)object + 0x97);

            FUN_0008304c(state, 7);
            for (uint32_t index = 0; index != 8; ++index)
                destination[index] = source[index];

            if (FUN_00082ff6(state, 10) != 0 ||
                FUN_00082ff6(state, 16) != 0) {
                FUN_00083090(state, 9);
            } else if (FUN_00082ff6(state, 9) != 0) {
                int32_t reason = FUN_0005d0ac(object);
                if (reason != 0)
                    FUN_0005dc2c(object, reason);
            }
        }
    }

    for (;;) {
        object = low_pointer(FUN_0005caa4(7));
        if (object == 0)
            return;

        int32_t reason = FUN_0005cc68(object);
        if (reason == 0)
            return;
        FUN_0005dc2c(object, reason);
    }
}
