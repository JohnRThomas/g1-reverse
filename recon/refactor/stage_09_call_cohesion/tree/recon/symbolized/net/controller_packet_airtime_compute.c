#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010109ec @ 0x010109ec
 * public-name: controller_packet_airtime_compute
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_packet_airtime_compute        <= FUN_010109ec @ 0x010109ec
 */
/* net-core FUN_010109ec @ 0x010109ec.
 * Exact Thumb executable extent is 0x540 bytes: the CFG crosses the literal
 * island at 0x01010dc0 and ends at the branch at 0x01010f28; literals start
 * at 0x01010f2c.  This is a pure controller packet-duration calculation. */
#include <stdint.h>

/* Reciprocal-multiply quotient used by the shipped controller for /247. */
static inline uint32_t blocks_247(uint32_t value)
{
    uint32_t high = (uint32_t)(((uint64_t)0x0953f391u * value) >> 32);
    return ((high + ((value - high) >> 1)) >> 7) & 0xffu;
}

/* Signed reciprocal scale used by coded-PHY duration paths. */
static inline int32_t coded_block_scale(int32_t value)
{
    int64_t product = (int64_t)(int32_t)0x84a9f9c9u * value;
    return ((int32_t)(product >> 32) + value) >> 7;
}

uint32_t controller_packet_airtime_compute(uint32_t timing, uint32_t base, uint32_t octets,
                      int32_t coded_phy, uint16_t flags)
{
    uint32_t capped = timing > 0xd8u ? 0xd9u : timing;
    capped = (uint16_t)(capped + 0x30u);
    if (capped > 0xfeu) {
        capped = 0xffu;
    }

    uint32_t result;
    uint32_t a, b, c, remainder, excess;

    if ((flags & 3u) == 0u) {
        result = base + 0x14au;
        if (coded_phy == 0) {
            if (octets == 8u) {
                result += (uint16_t)(capped + 5u) * 0x40u + 0x190u;
                if (timing > 0xd9u) {
                    base = 0x43dau;
                    excess = (uint16_t)(timing - 0xd9u);
                    a = blocks_247(excess);
                    result += a * 0x43dau;
                    remainder = (uint16_t)(excess - a * 0xf7u);
                    if (remainder != 0u) {
                        a = 0x190u;
                        b = 0x40u;
                        c = (uint16_t)(remainder + 8u) + 5u;
                        goto add_remainder_14a;
                    }
                }
                goto return_result;
            }
            if (octets == 4u) {
                base = 0x17eu;
                a = 0x10u;
                goto uncoded_initial;
            }
            if (octets == 2u) {
                base = 0x18u;
                a = 4u;
                goto uncoded_initial;
            }
            result += (uint16_t)(capped + 5u) * 8u + 0x28u;
            if (timing <= 0xd9u) {
                goto return_result;
            }
            excess = (uint16_t)(timing - 0xd9u);
            a = blocks_247(excess);
            base = 0x992u;
            result += a * 0x992u;
            remainder = (uint16_t)(excess - a * 0xf7u);
            if (remainder != 0u) {
                a = 0x28u;
                b = 8u;
                c = (uint16_t)(remainder + 8u) + 5u;
                goto add_remainder_14a;
            }
            goto return_result;

uncoded_initial:
            result += (uint16_t)(capped + 5u) * a + base;
            if (timing <= 0xd9u) {
                goto return_result;
            }
            excess = (uint16_t)(timing - 0xd9u);
            c = blocks_247(excess);
            base = c;
            if (octets == 4u) {
                result += c * 0x1308u;
                remainder = (uint16_t)(excess - c * 0xf7u);
                if (remainder != 0u) {
                    a = 0x17eu; b = 0x10u;
                    c = (uint16_t)(remainder + 8u) + 5u;
                    goto add_remainder_14a;
                }
                goto return_result;
            }
            if (octets == 2u) {
                result += c * 0x572u;
                remainder = (uint16_t)(excess - c * 0xf7u);
                if (remainder != 0u) {
                    a = 0x18u; b = 4u;
                    c = (uint16_t)(remainder + 8u) + 5u;
                    goto add_remainder_14a;
                }
                goto return_result;
            }
            result += c * 0x992u;
            remainder = (uint16_t)(excess - c * 0xf7u);
            if (remainder != 0u) {
                a = 0x28u; b = 8u;
                c = (uint16_t)(remainder + 8u) + 5u;
                goto add_remainder_14a;
            }
            goto return_result;
        }

        if (octets == 8u) {
            result = base + 0x43dau;
            a = (uint32_t)coded_block_scale((int32_t)((uint16_t)(timing - 0xd9u) + 0xf6u));
            if (timing > 0xd9u) {
                return result + a * 0x43dau;
            }
            goto return_result;
        }
        if (octets == 4u) {
            result += 0x11beu;
            goto coded_tail;
        }
        if (octets == 2u) {
            result += 0x428u;
            goto coded_tail;
        }
        result = base + 0x992u;
        if (timing <= 0xd9u) {
            goto return_result;
        }
        a = (uint16_t)(timing - 0xd9u) + 0xf6u;
        c = (uint32_t)coded_block_scale((int32_t)a);
        return result + c * 0x992u;

coded_tail:
        if (timing <= 0xd9u) {
            goto return_result;
        }
        a = (uint16_t)(timing - 0xd9u) + 0xf6u;
        c = (uint32_t)coded_block_scale((int32_t)a);
        if (octets == 4u) {
            return result + c * 0x1308u;
        }
        if (octets == 2u) {
            return result + c * 0x572u;
        }
        return result + c * 0x992u;
    }

    if ((flags & 2u) != 0u) {
        if (octets == 8u) a = 0x12d0u;
        else if (octets == 4u) a = 0x5ceu;
        else if (octets == 2u) a = 0x12cu;
        else a = 0x250u;
    } else if (coded_phy != 0) {
        if (octets == 8u) a = 0x4290u;
        else if (octets == 4u) a = 0x11beu;
        else if (octets == 2u) a = 0x428u;
        else a = 0x848u;
    } else {
        if (octets == 8u) { a = 0x190u; b = 0x40u; }
        else if (octets == 4u) { a = 0x17eu; b = 0x10u; }
        else if (octets == 2u) { a = 0x18u; b = 4u; }
        else { a = 0x28u; b = 8u; }
        base += 0x14au + (uint16_t)(capped + 5u) * b + a;
        goto common_middle;
    }

    base += 0x14au + a;
common_middle:
    if ((octets & 0xcu) == 0u) {
        if (octets == 8u) a = 0xb50u;
        else if (octets == 4u) a = 0x3eeu;
        else if (octets == 2u) a = 0xb4u;
        else a = 0x160u;
        base += 0x9cu;
        a += base;
        result = a + 0x98u;
    } else {
        a = base + 0xc14u;
        result = base + 0xcacu;
    }

    if ((flags & 1u) != 0u) {
        if (octets == 8u) base = 0x650u;
        else if (octets == 4u) base = 0x2aeu;
        else if (octets == 2u) base = 0x64u;
        else base = 0xc0u;
        result += base;
        goto return_result;
    }

    if (coded_phy != 0) {
        if (octets == 8u) {
            result = a + 0x4328u;
            if (timing > 0xd9u) {
                b = (uint16_t)(timing - 0xd9u) + 0xf6u;
                c = (uint32_t)coded_block_scale((int32_t)b);
                return result + c * 0x43dau;
            }
            goto return_result;
        }
        if (octets == 4u) base = 0x11beu;
        else if (octets == 2u) base = 0x428u;
        else {
            result = a + 0x8e0u;
            if (timing <= 0xd9u) goto return_result;
            b = (uint16_t)(timing - 0xd9u) + 0xf6u;
            c = (uint32_t)coded_block_scale((int32_t)b);
            return result + c * 0x992u;
        }
        result += base;
        if (timing <= 0xd9u) goto return_result;
        b = (uint16_t)(timing - 0xd9u) + 0xf6u;
        c = (uint32_t)coded_block_scale((int32_t)b);
        if (octets == 4u) return result + c * 0x1308u;
        return result + c * 0x572u;
    }

    capped = timing > 0xf0u ? 0xf1u : timing;
    if (octets == 8u) { a = 0x190u; b = 0x40u; }
    else if (octets == 4u) { a = 0x17eu; b = 0x10u; }
    else if (octets == 2u) { a = 0x18u; b = 4u; }
    else { a = 0x28u; b = 8u; }
    result += (uint16_t)(capped + 0x13u) * b + a;
    if (timing <= 0xd9u) goto return_result;
    excess = (uint16_t)(timing - 0xd9u);
    c = blocks_247(excess);
    if (octets == 8u) base = 0x43dau;
    else if (octets == 4u) base = 0x1308u;
    else if (octets == 2u) base = 0x572u;
    else base = 0x992u;
    result += c * base;
    remainder = (uint16_t)(excess - c * 0xf7u);
    if (remainder != 0u) {
        c = (uint16_t)(remainder + 8u) + 5u;
        goto add_remainder_14a;
    }
    goto return_result;

add_remainder_14a:
    return result + c * b + a + 0x14au;
return_result:
    return result;
}
