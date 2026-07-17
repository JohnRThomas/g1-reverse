#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0101b7e4 @ 0x0101b7e4
 * public-name: FUN_0101b7e4
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 *   controller_timing_request_schedule       <= FUN_0100d4d0 @ 0x0100d4d0
 *   sdc_radio_context_fixed_time_get         <= FUN_0100f0fc @ 0x0100f0fc
 *   sdc_conn_radio_overhead_set              <= FUN_0100f48c @ 0x0100f48c
 *   signed_drift_clamp                       <= FUN_0100f69c @ 0x0100f69c
 *   radio_transition_overhead_get            <= FUN_0101a0e8 @ 0x0101a0e8
 *   schedule_node_list_is_locked             <= FUN_0101dec4 @ 0x0101dec4
 *   radio_phy_airtime_base_get               <= FUN_010209f0 @ 0x010209f0
 * address symbols (name @ address):
 *   rodata_103c290                           @ 0x0103c290
 */
/* net-core timing-record construction @ 0x0101b7e4.
 *
 * Raw provenance: the TBB at 0x0101b810 owns states 0..3 and the three
 * controller-fault tails at 0x0101ba30, 0x0101ba3a and 0x0101ba44.  The last
 * BL completes at 0x0101ba4e; 0x0101ba4e is alignment, 0x0101ba50/54 are
 * literals, and FUN_0101ba58 begins with an independent prologue.
 */
#include <stdint.h>

extern __attribute__((noreturn)) void sdc_assertion_fail(uint32_t module,
                                                   uint32_t line);
extern uint32_t controller_timing_request_schedule(void *record, uint32_t timeline_unit);
extern uint32_t sdc_radio_context_fixed_time_get(const void *source);
extern void sdc_conn_radio_overhead_set(void *context, uint32_t delay);
extern uint32_t signed_drift_clamp(int32_t budget, uint32_t requested);
extern uint16_t radio_transition_overhead_get(void);
extern void FUN_0101da18(void *context, uint32_t count);
extern uint32_t FUN_0101dc50(void *context);
extern int32_t schedule_node_list_is_locked(void);
extern int32_t radio_phy_airtime_base_get(uint8_t channel_flags);

#define controller_fault           sdc_assertion_fail
#define measure_record_count       controller_timing_request_schedule
#define read_record_source         sdc_radio_context_fixed_time_get
#define schedule_controller_delay  sdc_conn_radio_overhead_set
#define consume_timing_budget      signed_drift_clamp
#define read_controller_timestamp  radio_transition_overhead_get
#define publish_record_count       FUN_0101da18
#define read_controller_capacity   FUN_0101dc50
#define timing_budget_is_blocked   schedule_node_list_is_locked
#define channel_timing_offset      radio_phy_airtime_base_get

#define CONTEXT_U8(offset)  (*(volatile uint8_t *)(context + (offset)))
#define CONTEXT_U16(offset) (*(volatile uint16_t *)(context + (offset)))
#define CONTEXT_U32(offset) (*(volatile uint32_t *)(context + (offset)))
#define RECORD_U8(offset)   (*(volatile uint8_t *)(record + (offset)))
#define RECORD_U16(offset)  (*(volatile uint16_t *)(record + (offset)))
#define RECORD_U32(offset)  (*(volatile uint32_t *)(record + (offset)))

#define CHANNEL_DELAY_TABLE ((const uint16_t *)UINT32_C(0x0103c290))
#define DELAY_SCALE UINT64_C(0x10624dd3)

static uint32_t add_carry_u32(uint32_t left, uint32_t right)
{
    uint32_t result;
    return __builtin_add_overflow(left, right, &result);
}

void FUN_0101b7e4(uint8_t *record, uint8_t *context,
                  uint32_t allow_state_initialization,
                  uint32_t update_controller_state)
{
    uint16_t timestamp = read_controller_timestamp();
    uint8_t controller_age = (uint8_t)(CONTEXT_U8(0xc5) - 0x0e);
    uint32_t timeline_unit;
    uint32_t base_timeline;
    uint32_t adjustment;
    uint32_t record_low;
    uint32_t record_high;
    uint32_t submitted_count;
    int32_t final_status;

    if (update_controller_state != 0)
        publish_record_count(context, 1);

    switch (CONTEXT_U8(0x300)) {
    case 0: {
        uint8_t channel_flags;
        uint16_t delay_seed;
        uint32_t scaled_delay;
        int32_t timing_offset;

        if (allow_state_initialization == 0)
            controller_fault(0x35, 0x22c);

        channel_flags = CONTEXT_U8(0x6f);
        delay_seed = CHANNEL_DELAY_TABLE[CONTEXT_U8(0x6e)];
        CONTEXT_U8(0x300) = 1;
        timing_offset = channel_timing_offset(channel_flags);
        scaled_delay = (uint32_t)((DELAY_SCALE *
            (uint32_t)(delay_seed + 0x79d + timing_offset)) >> 38);
        schedule_controller_delay(context, scaled_delay + 199 +
                                  ((channel_flags & 0x0c) != 0 ? 0x28 : 0));
        timeline_unit = 0;
        break;
    }
    case 1:
    case 3:
        timeline_unit = CONTEXT_U32(0x14);
        break;
    case 2:
        timeline_unit = CONTEXT_U32(0x308);
        CONTEXT_U8(0x300) = 3;
        break;
    default:
        controller_fault(0x35, 0x264);
    }

    base_timeline = timeline_unit;
    if (timing_budget_is_blocked() == 0) {
        adjustment = consume_timing_budget(
            (int16_t)CONTEXT_U16(0x2fc), 2);
        CONTEXT_U16(0x2fc) =
            (uint16_t)(CONTEXT_U16(0x2fc) - (uint16_t)adjustment);
    } else {
        adjustment = 0;
    }

    {
        uint32_t partial = base_timeline + CONTEXT_U32(0x2d8);
        record_low = partial + adjustment;
        record_high = CONTEXT_U32(0x2dc) +
                      add_carry_u32(base_timeline, CONTEXT_U32(0x2d8)) +
                      ((int32_t)adjustment >> 31) +
                      add_carry_u32(partial, adjustment);
    }
    CONTEXT_U32(0x2d8) = record_low;
    CONTEXT_U32(0x2dc) = record_high;
    RECORD_U32(0x10) = record_low;
    RECORD_U32(0x14) = record_high;
    RECORD_U16(8) = timestamp;
    RECORD_U8(0) = 0;

    if (((CONTEXT_U8(0xc5) & 0xfd) == 0x0c) ||
        (CONTEXT_U8(0xc5) == 0x26)) {
        (void)read_controller_capacity(context);
        RECORD_U16(10) = 0x100;
        RECORD_U32(4) = read_record_source(context + 0x30);
        if (controller_age < 2 || update_controller_state == 0)
            return;

        submitted_count = measure_record_count(record, base_timeline) & 0xffff;
        (void)read_controller_capacity(context);
        publish_record_count(context, submitted_count);
        final_status = timing_budget_is_blocked();
    } else {
        uint32_t capacity = read_controller_capacity(context);

        if (capacity == 0) {
            RECORD_U16(10) = 0x100;
        } else {
            RECORD_U8(10) = CONTEXT_U8(0x300) == 1 ? 1 : 2;
            RECORD_U8(11) = 1;
        }
        RECORD_U32(4) = read_record_source(context + 0x30);
        if (controller_age < 2 || update_controller_state == 0)
            return;

        submitted_count = measure_record_count(record, base_timeline) & 0xffff;
        capacity = read_controller_capacity(context);
        if (capacity <= submitted_count) {
            uint32_t product;
            uint32_t current_low;

            RECORD_U8(10) = 0;
            product = base_timeline * capacity;
            current_low = CONTEXT_U32(0x2d8);
            RECORD_U32(0x10) = current_low + product;
            RECORD_U32(0x14) = CONTEXT_U32(0x2dc) +
                               add_carry_u32(current_low, product);
            if (base_timeline == 0)
                controller_fault(0x35, 0x2a6);
            submitted_count = (capacity +
                measure_record_count(record, base_timeline)) & 0xffff;
        }
        publish_record_count(context, submitted_count);
        final_status = timing_budget_is_blocked();
    }

    if (final_status == 0) {
        uint32_t requested = submitted_count * 2;
        uint32_t current_low;

        if (requested >= 0x10000)
            requested = 0xffff;
        else
            requested &= 0xffff;
        adjustment = consume_timing_budget(
            (int16_t)CONTEXT_U16(0x2fc), requested);
        CONTEXT_U16(0x2fc) =
            (uint16_t)(CONTEXT_U16(0x2fc) - (uint16_t)adjustment);
        current_low = RECORD_U32(0x10);
        RECORD_U32(0x10) = current_low + adjustment;
        RECORD_U32(0x14) = RECORD_U32(0x14) +
                           ((int32_t)adjustment >> 31) +
                           add_carry_u32(adjustment, current_low);
    }

    CONTEXT_U32(0x2d8) = RECORD_U32(0x10);
    CONTEXT_U32(0x2dc) = RECORD_U32(0x14);
    if (CONTEXT_U32(0x74) != 0) {
        int16_t distance =
            (int16_t)(CONTEXT_U16(0xbc) - CONTEXT_U16(0xf2));
        if (distance > 0) {
            uint16_t quantum = CONTEXT_U16(0x78);
            uint16_t previous = CONTEXT_U16(0xf2);
            CONTEXT_U16(0xf2) = (uint16_t)(
                (((uint32_t)distance + quantum - 1) / quantum) * quantum +
                previous);
        }
    }
}
