/* readable reconstruction; identity: FUN_00013e60 @ 0x00013e60
 * public-name: scalbn
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   __aeabi_dadd                             <= FUN_0000d58c @ 0x0000d58c
 *   __muldf3                                 <= FUN_0000d8f8 @ 0x0000d8f8
 *   scalbn                                   <= FUN_00013e60 @ 0x00013e60
 */
/* Reconstructed FUN_00013e60 @ 0x13e60 */
#include <stdint.h>

extern uint64_t __muldf3(uint32_t, uint32_t, uint32_t, uint32_t);
extern uint64_t __aeabi_dadd(uint32_t, uint32_t, uint32_t);

static uint64_t pack_words(uint32_t low, uint32_t high)
{
    return ((uint64_t)high << 32) | low;
}

double scalbn(double value, int scale)
{
    union { double d; uint64_t bits; } number;
    uint32_t low, high, exponent;

    number.d = value;
    low = (uint32_t)number.bits;
    high = (uint32_t)(number.bits >> 32);
    exponent = (high >> 20) & 0x7ff;

    if (exponent == 0) {
        if (((high & 0x7fffffff) | low) == 0)
            return number.d;
        number.bits = __muldf3(low, high, 0, 0x43500000);
        low = (uint32_t)number.bits;
        high = (uint32_t)(number.bits >> 32);
        if (scale < -50000) {
            number.bits = __muldf3(low, high, 0xc2f8f359, 0x01a56e1f);
            return number.d;
        }
        exponent = ((high >> 20) & 0x7ff) - 0x36;
    } else if (exponent == 0x7ff) {
        number.bits = __aeabi_dadd(low, high, low);
        return number.d;
    }

    {
        int adjusted = (int)exponent + scale;
        if (adjusted > 0 && adjusted < 0x7ff) {
            high = (high & 0x800fffff) | ((uint32_t)adjusted << 20);
            number.bits = pack_words(low, high);
            return number.d;
        }
        if (adjusted >= 0x7ff) {
            uint32_t out_high = (int32_t)high < 0 ? 0xfe37e43c : 0x7e37e43c;
            number.bits = __muldf3(0x8800759c, out_high,
                                      0x8800759c, 0x7e37e43c);
            return number.d;
        }
        if (adjusted < -0x35) {
            uint32_t out_high = (int32_t)high < 0 ? 0x81a56e1f : 0x01a56e1f;
            number.bits = __muldf3(0xc2f8f359, out_high,
                                      0xc2f8f359, 0x01a56e1f);
            return number.d;
        }
        high = (high & 0x800fffff) | ((uint32_t)(adjusted + 0x36) << 20);
        number.bits = __muldf3(low, high, 0, 0x3c900000);
        return number.d;
    }
}
