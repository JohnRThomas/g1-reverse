/* readable reconstruction; identity: FUN_0101ba58 @ 0x0101ba58
 * public-name: FUN_0101ba58
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_2100111d                               @ 0x2100111d
 *   g_21001120                               @ 0x21001120
 */
/* net-core FUN_0101ba58 @ 0x101ba58 -- true code extent ends at 0x101bb94 */
#include <stdint.h>

extern int FUN_01008d00(int subsystem, int reason);
extern int FUN_0101d404(void);
extern int FUN_0101a130(void);
extern int FUN_0100f0fc(int address);
extern uint32_t FUN_01023dec(int unit);
extern int FUN_01023ea8(uint32_t amount, int unit);
extern uint32_t FUN_0100f368(int object, int offset, uint32_t span);
extern void FUN_01023d38(int offset);
extern void FUN_0101b7e4(void *scratch, int object, int zero, int one);
extern int FUN_010231c8(uint8_t channel, void *scratch);
extern void FUN_0101d890(int object);
extern void FUN_01020d1c(int object);
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
            for (;;) FUN_01008d00(0x35, 0x109);
        if (FUN_0101d404() == 0)
            return;
    }

    uint32_t span = 0;
    if (!skip_setup) {
        baseline = FUN_0101a130();
        span = (uint16_t)(baseline + 200);
        if ((*(volatile uint8_t *)(object + 0x6f) & 0x0c) != 0)
            span += 0x28;
    }

    if (*(volatile uint8_t *)0x2100111d == 0) {
        limit = *(volatile uint32_t *)(object + 0x30);
        if (*(volatile uint32_t *)(object + 0x14) <= limit)
            limit = *(volatile uint32_t *)(object + 0x14);
    } else {
        limit = *(volatile uint32_t *)(object + 0x14);
    }

    offset = FUN_0100f0fc(object + 0x30) + FUN_0101a130();
    available = FUN_01023dec(2);
    room = limit - (uint32_t)offset;
    room &= ~(uint32_t)((int32_t)room >> 31);
    if (available <= room)
        room = available;
    if (FUN_01023ea8(room, 2) == 0)
        offset += (int)room;

    baseline = FUN_0101a130();
    *(volatile uint32_t *)(skip_setup ? 4u : 0x21001120u) =
        FUN_0100f368(object, offset, span);
    FUN_01023d38((offset - 0xb7) - baseline);
}

void FUN_0101ba58(int object, unsigned int event)
{
    uint8_t scratch[12];

    if (object == 0)
        for (;;) FUN_01008d00(0x35, 0x101);

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
        if (FUN_010231c8(*(volatile uint8_t *)(object + 0x301), scratch) == 0)
            for (;;) FUN_01008d00(0x35, 0x2d4);
        return;
    case 4:
        FUN_01020d1c(object);
        return;
    case 6: {
        int result = FUN_01022a30(1);
        FUN_0100b5f8(result);
        return;
    }
    case 7:
        if (*(volatile uint8_t *)(object + 0x300) != 4)
            for (;;) FUN_01008d00(0x35, 0x12f);
        return;
    case 8:
        FUN_01008d00(0x35, 0x134);
        /* Physical fallthrough after the returning panic oracle. */
        FUN_01008d00(0x35, 0x138);
        render_case0(object, 1);
        return;
    default:
        FUN_01008d00(0x35, 0x138);
        /* Out-of-range entries physically continue at 0x101bb68. */
        render_case0(object, 1);
        return;
    }
}
