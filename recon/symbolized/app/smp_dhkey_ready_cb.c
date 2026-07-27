#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0008349c @ 0x0008349c
 * public-name: smp_dhkey_ready_cb
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   kobj_test_bit_get_ptr                    <= FUN_0005caa4 @ 0x0005caa4
 *   smp_dhkey_generate                       <= FUN_0005cc68 @ 0x0005cc68
 *   smp_dhkey_check_generate                 <= FUN_0005d0ac @ 0x0005d0ac
 *   smp_error                                <= FUN_0005dc2c @ 0x0005dc2c
 *   atomic_test_bit                          <= FUN_00082ff6 @ 0x00082ff6
 *   atomic_clear_bit_1                       <= FUN_0008304c @ 0x0008304c
 *   atomic_set_bit                           <= FUN_00083090 @ 0x00083090
 *   smp_dhkey_ready_cb                       <= FUN_0008349c @ 0x0008349c
 */
/* ABI-faithful reconstruction of FUN_0008349c @ 0x8349c. */
#include <stdint.h>

/* The allocator helper returns its object in r0.  Its otherwise-unspecified
 * r1 half is deliberately represented as part of the call result so the
 * compiler observes the original r1:r0 return ABI. */
extern uint64_t kobj_test_bit_get_ptr(uint32_t kind);
extern int smp_dhkey_generate(int);
extern int smp_dhkey_check_generate(int);
extern unsigned int smp_error(int, unsigned int);
extern int atomic_test_bit(int, int);
extern void atomic_clear_bit_1(volatile long*, int);
extern void atomic_set_bit(int, int);

static inline void *low_pointer(uint64_t result)
{
    return (void *)(uintptr_t)(uint32_t)result;
}

void smp_dhkey_ready_cb(const uint32_t source[8])
{
    void *object = low_pointer(kobj_test_bit_get_ptr(8));

    if (object != 0) {
        void *state = (uint8_t *)object + 4;

        atomic_clear_bit_1(state, 8);
        if (source == 0) {
            smp_error(object, 11);
        } else {
            uint32_t *destination = (uint32_t *)((uint8_t *)object + 0x97);

            atomic_clear_bit_1(state, 7);
            for (uint32_t index = 0; index != 8; ++index)
                destination[index] = source[index];

            if (atomic_test_bit(state, 10) != 0 ||
                atomic_test_bit(state, 16) != 0) {
                atomic_set_bit(state, 9);
            } else if (atomic_test_bit(state, 9) != 0) {
                int32_t reason = smp_dhkey_check_generate(object);
                if (reason != 0)
                    smp_error(object, reason);
            }
        }
    }

    for (;;) {
        object = low_pointer(kobj_test_bit_get_ptr(7));
        if (object == 0)
            return;

        int32_t reason = smp_dhkey_generate(object);
        if (reason == 0)
            return;
        smp_error(object, reason);
    }
}
