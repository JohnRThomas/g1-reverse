/* readable reconstruction; identity: FUN_00075e14 @ 0x00075e14
 * public-name: __ieee754_sqrt
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed __ieee754_sqrt @ 0x00075e14 from newlib 3.3.0 e_sqrt.c.
 * Raw backmap: FUN_00075e14@0x00075e14. */

#include <stdint.h>

union ieee_double_words {
    double value;
    struct { uint32_t low, high; } words;
};

double __ieee754_sqrt(double x)
{
    static const double one = 1.0;
    static const double tiny = 1.0e-300;
    union ieee_double_words bits = { .value = x };
    double z;
    int32_t sign = (int32_t)0x80000000u;
    uint32_t r, t1, s1, ix1, q1;
    int32_t ix0, s0, q, m, t, i;

    ix0 = (int32_t)bits.words.high;
    ix1 = bits.words.low;
    if ((ix0 & 0x7ff00000) == 0x7ff00000) {
        return x * x + x;
    }
    if (ix0 <= 0) {
        if ((((uint32_t)ix0 & ~(uint32_t)sign) | ix1) == 0u) {
            return x;
        }
        if (ix0 < 0) {
            return (x - x) / (x - x);
        }
    }

    m = ix0 >> 20;
    if (m == 0) {
        while (ix0 == 0) {
            m -= 21;
            ix0 |= (int32_t)(ix1 >> 11);
            ix1 <<= 21;
        }
        for (i = 0; (ix0 & 0x00100000) == 0; i++) {
            ix0 <<= 1;
        }
        m -= i - 1;
        ix0 |= (int32_t)(ix1 >> (32 - i));
        ix1 <<= i;
    }
    m -= 1023;
    ix0 = (ix0 & 0x000fffff) | 0x00100000;
    if ((m & 1) != 0) {
        ix0 += ix0 + (int32_t)((ix1 & (uint32_t)sign) >> 31);
        ix1 += ix1;
    }
    m >>= 1;
    ix0 += ix0 + (int32_t)((ix1 & (uint32_t)sign) >> 31);
    ix1 += ix1;
    q = 0; q1 = 0; s0 = 0; s1 = 0;
    r = 0x00200000u;
    while (r != 0u) {
        t = s0 + (int32_t)r;
        if (t <= ix0) {
            s0 = t + (int32_t)r;
            ix0 -= t;
            q += (int32_t)r;
        }
        ix0 += ix0 + (int32_t)((ix1 & (uint32_t)sign) >> 31);
        ix1 += ix1;
        r >>= 1;
    }
    r = (uint32_t)sign;
    while (r != 0u) {
        t1 = s1 + r;
        t = s0;
        if (t < ix0 || (t == ix0 && t1 <= ix1)) {
            s1 = t1 + r;
            if ((t1 & (uint32_t)sign) != 0u &&
                (s1 & (uint32_t)sign) == 0u) {
                s0 += 1;
            }
            ix0 -= t;
            if (ix1 < t1) {
                ix0 -= 1;
            }
            ix1 -= t1;
            q1 += r;
        }
        ix0 += ix0 + (int32_t)((ix1 & (uint32_t)sign) >> 31);
        ix1 += ix1;
        r >>= 1;
    }
    if ((ix0 | (int32_t)ix1) != 0) {
        z = one - tiny;
        if (z >= one) {
            z = one + tiny;
            if (q1 == 0xffffffffu) {
                q1 = 0u;
                q += 1;
            } else if (z > one) {
                if (q1 == 0xfffffffeu) q += 1;
                q1 += 2u;
            } else {
                q1 += q1 & 1u;
            }
        }
    }
    bits.words.high = (uint32_t)((q >> 1) + 0x3fe00000 + (m << 20));
    bits.words.low = q1 >> 1;
    if ((q & 1) != 0) bits.words.low |= (uint32_t)sign;
    return bits.value;
}
