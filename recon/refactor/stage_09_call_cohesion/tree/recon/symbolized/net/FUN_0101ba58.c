#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0101ba58 @ 0x0101ba58
 * public-name: FUN_0101ba58
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 *   sdc_radio_context_fixed_time_get         <= FUN_0100f0fc @ 0x0100f0fc
 *   controller_packet_rendering_budget_remaining <= FUN_0100f368 @ 0x0100f368
 *   radio_slot_margin_get                    <= FUN_0101a130 @ 0x0101a130
 *   controller_radio_transition_apply        <= FUN_01020d1c @ 0x01020d1c
 *   sdc_conn_window_admit                    <= FUN_010231c8 @ 0x010231c8
 * address symbols (name @ address):
 *   g_2100111d                               @ 0x2100111d
 *   g_21001120                               @ 0x21001120
 */
/* net-core FUN_0101ba58 @ 0x101ba58 -- true code extent ends at 0x101bb94 */
#include <stdint.h>

extern int sdc_assertion_fail(int subsystem, int reason);
extern int FUN_0101d404(void);
extern int radio_slot_margin_get(void);
extern int sdc_radio_context_fixed_time_get(int address);
extern uint32_t FUN_01023dec(int unit);
extern int FUN_01023ea8(uint32_t amount, int unit);
extern uint32_t controller_packet_rendering_budget_remaining(int object, int offset, uint32_t span);
extern void FUN_01023d38(int offset);
extern void FUN_0101b7e4(void *scratch, int object, int zero, int one);
extern int sdc_conn_window_admit(uint8_t channel, void *scratch);
extern void FUN_0101d890(int object);
extern void controller_radio_transition_apply(int object);
extern int FUN_01022a30(int enabled);
extern void FUN_0100b5f8(int prior_result);

static __attribute__((always_inline)) inline void render_case0(int object, int skip_setup)
{
    uint32_t limit;
    int offset;
    int baseline;
    uint32_t room;
    uint32_t available;

    if (!skip_setup) {
        if (*(volatile uint8_t *)(object + 0x300) == 0)
            for (;;) sdc_assertion_fail(0x35, 0x109);
        if (FUN_0101d404() == 0)
            return;
    }

    uint32_t span = 0;
    if (!skip_setup) {
        baseline = radio_slot_margin_get();
        span = (uint16_t)(baseline + 200);
        if ((*(volatile uint8_t *)(object + 0x6f) & 0x0c) != 0)
            span += 0x28;
    }

    if (*(volatile uint8_t *)((unsigned long)&g_2100111d) /*=0x2100111d*/ == 0) {
        limit = *(volatile uint32_t *)(object + 0x30);
        if (*(volatile uint32_t *)(object + 0x14) <= limit)
            limit = *(volatile uint32_t *)(object + 0x14);
    } else {
        limit = *(volatile uint32_t *)(object + 0x14);
    }

    offset = sdc_radio_context_fixed_time_get(object + 0x30) + radio_slot_margin_get();
    available = FUN_01023dec(2);
    room = limit - (uint32_t)offset;
    room &= ~(uint32_t)((int32_t)room >> 31);
    if (available <= room)
        room = available;
    if (FUN_01023ea8(room, 2) == 0)
        offset += (int)room;

    baseline = radio_slot_margin_get();
    *(volatile uint32_t *)(skip_setup ? 4u : ((unsigned long)&g_21001120) /*=0x21001120*/) =
        controller_packet_rendering_budget_remaining(object, offset, span);
    FUN_01023d38((offset - 0xb7) - baseline);
}

void FUN_0101ba58(int object, unsigned int event)
{
    uint8_t scratch[12];

    if (object == 0)
        for (;;) sdc_assertion_fail(0x35, 0x101);

    switch (event) {
    case 0:
        render_case0(object, 0);
        return;
    case 1:
        FUN_0101d890(object);
        return;
    case 2:
    case 3:
        FUN_0101b7e4(scratch, object, 0, 1);
        if (sdc_conn_window_admit(*(volatile uint8_t *)(object + 0x301), scratch) == 0)
            for (;;) sdc_assertion_fail(0x35, 0x2d4);
        return;
    case 4:
        controller_radio_transition_apply(object);
        return;
    case 6: {
        int result = FUN_01022a30(1);
        FUN_0100b5f8(result);
        return;
    }
    case 7:
        if (*(volatile uint8_t *)(object + 0x300) != 4)
            for (;;) sdc_assertion_fail(0x35, 0x12f);
        return;
    case 8:
        sdc_assertion_fail(0x35, 0x134);
        /* Physical fallthrough after the returning panic oracle. */
        sdc_assertion_fail(0x35, 0x138);
        render_case0(object, 1);
        return;
    default:
        sdc_assertion_fail(0x35, 0x138);
        /* Out-of-range entries physically continue at 0x101bb68. */
        render_case0(object, 1);
        return;
    }
}
