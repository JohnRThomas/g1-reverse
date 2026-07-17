/* readable reconstruction; identity: FUN_0100f368 @ 0x0100f368
 * public-name: controller_packet_rendering_budget_remaining
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 *   controller_packet_rendering_budget_remaining <= FUN_0100f368 @ 0x0100f368
 * address symbols (name @ address):
 *   g_21000ef2                               @ 0x21000ef2
 */
/* net-core FUN_0100f368 @ 0x100f368  (CFG-directed candidate) */
/* net-core FUN_0100f368 @ 0x0100f368
 * Readable role: compute the remaining controller packet rendering budget.
 * Address back-map:
 *   controller minimum-budget policy flag @ 0x21000ef2
 *   sdc_assertion_fail = FUN_01008d00 @ 0x01008d00
 */
#include <stdint.h>

extern void sdc_assertion_fail(uint32_t module, uint32_t line,
                         uint32_t diagnostic_context, uint32_t value)
    __attribute__((noreturn));
#define sdc_assertion_fail sdc_assertion_fail

static uint16_t load_u16(const uint8_t *object, unsigned int offset)
{
    return *(const uint16_t *)(object + offset);
}

static uint16_t minimum_u16(uint16_t left, uint16_t right)
{
    return left < right ? left : right;
}

static uint16_t maximum_u16(uint16_t left, uint16_t right)
{
    return left < right ? right : left;
}

static uint16_t mode_budget(uint16_t value, uint8_t mode)
{
    if (mode == 1U) {
        return (uint16_t)((uint32_t)(value + 14U) * 8U);
    }
    return (uint16_t)((uint32_t)(value + 15U) * 4U);
}

static uint16_t mode_minimum(uint8_t mode, uint32_t diagnostic_context,
                             uint16_t assertion_value)
{
    if ((mode & 0x0cU) != 0U) {
        return 0x0e90U;
    }
    if (mode == 1U) {
        return 0x01c8U;
    }
    if (mode == 2U) {
        return 0x00e8U;
    }
    sdc_assertion_fail(6U, 0x1e2U, diagnostic_context, assertion_value);
}

uint32_t controller_packet_rendering_budget_remaining(const void *controller_object, uint32_t available,
                      uint32_t payload_span)
{
    const uint8_t *object = (const uint8_t *)controller_object;
    const uint8_t primary_mode = object[0x6e];
    const uint8_t secondary_mode = object[0x6f];
    const uint32_t fixed_span =
        (*(const uint32_t *)(object + 0x14) < 0x1d4cU) ? 0x4dU : 0x96U;
    const uint16_t primary_source = load_u16(object, 0x38);
    uint16_t primary_budget;
    uint16_t lower_budget;
    uint16_t secondary_budget;
    uint16_t secondary_source;
    uint16_t minimum;
    uint32_t total;

    if ((primary_mode & 0x0cU) != 0U) {
        primary_budget =
            (uint16_t)((uint32_t)primary_source * 64U + 0x03d0U);
        lower_budget = minimum_u16(0x0a90U, primary_budget);
        secondary_source = load_u16(object, 0x40);
    } else {
        if (primary_mode != 1U && primary_mode != 2U) {
            sdc_assertion_fail(6U, 0x1e2U, payload_span,
                               primary_source);
        }
        primary_budget = mode_budget(primary_source, primary_mode);
        lower_budget = minimum_u16(load_u16(object, 0x4a),
                                   load_u16(object, 0x4e));
        lower_budget = minimum_u16(lower_budget, primary_budget);
        secondary_source = load_u16(object, 0x40);
    }

    if ((secondary_mode & 0x0cU) != 0U) {
        secondary_budget =
            (uint16_t)((uint32_t)secondary_source * 64U + 0x03d0U);
        secondary_budget = minimum_u16(secondary_budget, 0x0a90U);
    } else {
        if (secondary_mode != 1U && secondary_mode != 2U) {
            sdc_assertion_fail(6U, 0x1e2U, payload_span,
                               primary_budget);
        }
        secondary_budget = mode_budget(secondary_source, secondary_mode);
        secondary_budget = minimum_u16(secondary_budget,
                                        load_u16(object, 0x42));
    }

    if (*(const volatile uint8_t *)0x21000ef2U != 0U) {
        minimum = mode_minimum(secondary_mode, payload_span,
                               secondary_budget);
        secondary_budget = maximum_u16(secondary_budget, minimum);
        minimum = mode_minimum(primary_mode, payload_span,
                               secondary_budget);
        lower_budget = maximum_u16(lower_budget, minimum);
    }

    total = (uint32_t)secondary_budget + (uint32_t)lower_budget +
            payload_span + 6U + fixed_span * 2U;
    return available < total ? 0U : available - total;
}
