/* readable reconstruction; identity: FUN_0100f1f8 @ 0x0100f1f8
 * public-name: controller_timing_windows_clamp
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_timing_windows_clamp          <= FUN_0100f1f8 @ 0x0100f1f8
 */
/* net-core FUN_0100f1f8 @ 0x100f1f8  (CFG-directed candidate) */
/* net-core FUN_0100f1f8 @ 0x0100f1f8
 * Readable role: clamp controller timing windows and report whether any active bound changed.
 */
#include <stdint.h>

static uint16_t read_u16(const volatile uint8_t *object, unsigned int offset)
{
    return *(const volatile uint16_t *)(object + offset);
}

static void write_u16(volatile uint8_t *object, unsigned int offset, uint16_t value)
{
    *(volatile uint16_t *)(object + offset) = value;
}

static uint16_t minimum_u16(uint16_t left, uint16_t right)
{
    return left < right ? left : right;
}

uint32_t controller_timing_windows_clamp(void *controller_object)
{
    volatile uint8_t *object = (volatile uint8_t *)controller_object;
    uint16_t old_primary_low = read_u16(object, 0x3a);
    uint16_t old_primary_high = read_u16(object, 0x3e);
    uint16_t new_primary_low = minimum_u16(read_u16(object, 0x50),
                                           read_u16(object, 0x44));
    uint16_t candidate_high = minimum_u16(read_u16(object, 0x48),
                                           read_u16(object, 0x52));
    uint16_t prior_floor = read_u16(object, 0x40);
    uint16_t required_ceiling;
    uint16_t new_primary_high;
    uint16_t new_floor;
    uint16_t new_ceiling;
    uint16_t old_secondary_low;
    uint16_t old_secondary_high;
    uint16_t new_secondary_low;
    uint16_t new_secondary_high;
    uint32_t changed;

    if ((object[0x6f] & 0x0cU) == 0U) {
        new_primary_high = candidate_high;
        required_ceiling = read_u16(object, 0x42);
    } else {
        new_primary_high = 0x0a90U;
        required_ceiling = 0x0a90U;
    }

    write_u16(object, 0x3e, new_primary_high);
    write_u16(object, 0x3a, new_primary_low);

    new_ceiling = candidate_high < required_ceiling
                      ? required_ceiling : candidate_high;
    old_secondary_low = read_u16(object, 0x38);
    new_floor = prior_floor < new_primary_low ? new_primary_low : prior_floor;
    changed = (old_primary_high != new_primary_high) ? 1U : 0U;
    changed |= (old_primary_low != new_primary_low) ? 1U : 0U;

    write_u16(object, 0x40, new_floor);
    old_secondary_high = read_u16(object, 0x3c);
    write_u16(object, 0x42, new_ceiling);

    new_secondary_low = minimum_u16(read_u16(object, 0x46),
                                     read_u16(object, 0x4c));
    if ((object[0x6e] & 0x0cU) == 0U) {
        new_secondary_high = minimum_u16(read_u16(object, 0x4a),
                                          read_u16(object, 0x4e));
    } else {
        new_secondary_high = 0x0a90U;
    }

    if (object[0x64] == 2U) {
        new_secondary_low = minimum_u16(new_secondary_low, old_secondary_low);
        object[0x64] = 0U;
        new_secondary_high = minimum_u16(new_secondary_high,
                                          old_secondary_high);
    }

    write_u16(object, 0x38, new_secondary_low);
    write_u16(object, 0x3c, new_secondary_high);
    changed |= (old_secondary_low != new_secondary_low) ? 1U : 0U;
    changed |= (old_secondary_high != new_secondary_high) ? 1U : 0U;
    return changed;
}
