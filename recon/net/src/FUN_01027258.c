/* net-core FUN_01027258 @ 0x01027258 */
#include <stdint.h>

extern void sdc_assertion_fail(uint32_t, uint32_t);
extern void FUN_010271f6(uint32_t, uint32_t);

uint32_t FUN_01027258(uint32_t *storage, uint32_t length)
{
    if (length != 0u && length < 8u) {
        sdc_assertion_fail(0x15u, 0x19au);
    }

    if (length == 0u) {
        if (storage != 0) {
            *storage = 0u;
        }
        return 0u;
    }

    if (storage != 0) {
        if (length >= 0x10000u) {
            sdc_assertion_fail(0x15u, 0x1acu);
        }
        FUN_010271f6(*storage, (uint16_t)length);
    }
    return length + 4u;
}
