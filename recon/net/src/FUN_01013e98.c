/* net-core FUN_01013e98 @ 0x1013e98 */
#include <stdint.h>

extern void FUN_01020634(void);
extern void FUN_01022a84(void);
extern uint32_t FUN_010202e4(void);
extern uint32_t FUN_010209e0(uint32_t);
extern uint32_t FUN_010209f0(uint32_t);
extern uint32_t FUN_01029638(void);
extern uint32_t FUN_01024678(uint32_t, uint32_t);
extern void FUN_0102a1e0(void);
extern int FUN_01012f18(void *, uint16_t, uint32_t, uint32_t, uint32_t);
extern void FUN_01012c08(void);
extern void FUN_01008d00(uint32_t, uint32_t);
extern void FUN_0100f48c(void *, uint32_t);

static inline uint8_t r8(uint8_t *p, unsigned o) { return *(volatile uint8_t *)(p + o); }
static inline uint16_t r16(uint8_t *p, unsigned o) { return *(volatile uint16_t *)(p + o); }
static inline uint32_t r32(uint8_t *p, unsigned o) { return *(volatile uint32_t *)(p + o); }
static inline void w8(uint8_t *p, unsigned o, uint8_t v) { *(volatile uint8_t *)(p + o) = v; }
static inline void w16(uint8_t *p, unsigned o, uint16_t v) { *(volatile uint16_t *)(p + o) = v; }
static inline void w32(uint8_t *p, unsigned o, uint32_t v) { *(volatile uint32_t *)(p + o) = v; }

void FUN_01013e98(uint8_t *ctx, uint32_t event)
{
    if (event > 5) {
        FUN_01008d00(0x30, 0x7a3);
        return;
    }

    if (event == 1) {
        w8(ctx, 0x31c, 3);
        return;
    }
    if (event == 3)
        return;
    if (event == 4) {
        uint32_t now = FUN_010202e4();
        w32(ctx, 0x36c, now);
        uint32_t base = FUN_010209e0(r8(ctx, 0x6f));
        if (now < base) {
            FUN_01008d00(0x30, 0x3da);
            return;
        }
        volatile uint32_t *clock_adjust = (volatile uint32_t *)0x21000f60;
        *clock_adjust = *clock_adjust + now - FUN_010209e0(r8(ctx, 0x6f));
        return;
    }
    if (event == 5) {
        uint32_t mode = r8(ctx, 0x6f);
        uint32_t v = FUN_010209f0(mode) + 0xdf41u;
        uint32_t scaled = (uint32_t)(((uint64_t)0x10624dd3u * v) >> 38);
        if (mode & 0x0c)
            scaled += 0x28;
        FUN_0100f48c(ctx, scaled + 0xc5);
        return;
    }

    if (event == 2) {
        w8(ctx, 0x31c, 4);
    } else {
        if (r32(ctx, 0x36c) && r8(ctx, 0x332) && r8(ctx, 0x31c) == 3) {
            uint32_t mode = r8(ctx, 0x6f);
            uint32_t tick = FUN_01029638();
            uint32_t index = r8(ctx, 0x2d8);
            if (index > 11) {
                FUN_01012c08();
                FUN_01008d00(0x30, 0x7a3);
                return;
            }
            volatile uint16_t *table = (volatile uint16_t *)0x0103c1f8;
            uint32_t slot = table[index];
            uint32_t width = (tick + slot) & 0xffff;
            uint32_t center = r32(ctx, 0x36c) - FUN_010209e0(mode);
            int32_t remaining;
            uint32_t floor;
            if ((mode & 0x0c) == 0) {
                uint32_t q = (uint32_t)(((uint64_t)0x10624dd3u * (FUN_010209f0(mode) + 999u)) >> 38);
                center -= q;
                remaining = (int32_t)(r32(ctx, 0x2f0) - FUN_010209e0(mode));
                floor = (uint32_t)(((uint64_t)0x10624dd3u * (FUN_010209f0(mode) + 0xa3a1u)) >> 38);
            } else {
                center -= 0x3c;
                remaining = (int32_t)(r32(ctx, 0x2f0) - FUN_010209e0(mode));
                floor = 0x65;
            }
            int32_t delta = remaining - (int32_t)floor;
            uint32_t span = (width * (uint32_t)(delta - 0x60)) / ((slot + 0x640) & 0xffff) + 0x60;
            uint32_t midpoint = (uint32_t)(delta / 2 + 0x29);
            if (center < midpoint - span / 2 || center > midpoint + span / 2)
                FUN_0102a1e0();
            uint32_t next = FUN_01024678(r32(ctx, 0x14), width);
            if (r32(ctx, 0x14) <= 0x1d4b)
                next += 2;
            w8(ctx, 0x332, 0);
            w32(ctx, 0x324, next);
        }
        if (*(volatile uint8_t *)0x21000f64) {
            w8(ctx, 0x31c, 4);
        } else if (FUN_01012f18(ctx, r16(ctx, 0x2e4), 0, 1, 0) != 0) {
            FUN_01008d00(0x30, 0x717);
            return;
        }
    }

    FUN_01020634();
    FUN_01022a84();
    w16(ctx, 0x362, 0);
    w16(ctx, 0x32e, r16(ctx, 0xbc));
    w8(ctx, 0x331, 0);
}
