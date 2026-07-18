/* CPUAPP ui_new_message_task @ 0x00036b3c.
 * Raw/back-map identity: FUN_00036b3c, exact reachable extent 0x1fc bytes. */
#include <stdint.h>

extern uintptr_t FUN_000167a8(void);
extern uint32_t FUN_00034410(void);
extern uint32_t FUN_0003483c(uint32_t index);
extern void FUN_000431c0(void);
extern void FUN_000431b4(void *framebuffer);
extern void FUN_000432d0(void);
extern void FUN_000432ec(void);
extern uint32_t FUN_0007d3ee(void);
extern uint32_t FUN_0007d446(void);
extern void FUN_00043484(uint32_t glyph, uint32_t x, uint32_t y,
                         uint32_t a3, uint32_t a4, uint32_t a5);
extern void FUN_00047260(uintptr_t left, uintptr_t right, uint32_t x,
                         uint32_t y, uint32_t width, uint32_t height);
extern void DEBUG_PRINT(uintptr_t format, ...);
extern void FUN_00019c70(uintptr_t format, ...);

#define LOG_ROUTE (*(volatile uint32_t *)0x20007554u)
#define MESSAGE_TASK_ACTIVE (*(volatile uint8_t *)0x2001b813u)
#define MESSAGE_TASK_RENDERED (*(volatile uint8_t *)0x2001b812u)
#define MASK_TABLE ((const uint8_t *)0x000aae20u)
#define MASK_PHASE ((const uint8_t *)0x000a8e98u)

#define TASK_LOG(format, ...) do { \
    if (LOG_ROUTE == 0u) DEBUG_PRINT((format), ##__VA_ARGS__); \
    else FUN_00019c70((format), ##__VA_ARGS__); \
} while (0)

uint32_t ui_new_message_task(uint8_t *canvas, uint32_t unused, uint32_t phase)
{
    uintptr_t state = FUN_000167a8();
    uint32_t mode = FUN_00034410();
    uint8_t was_active = MESSAGE_TASK_ACTIVE;

    (void)unused;
    if (mode == 4u)
        return 0u;
    if (phase == 2u) {
        TASK_LOG(0x000a8e61u);
        FUN_000431c0();
        MESSAGE_TASK_ACTIVE = 0u;
        MESSAGE_TASK_RENDERED = 0u;
        return 0u;
    }
    if (phase == 0u)
        return 0u;

    if (MESSAGE_TASK_ACTIVE == 0u) {
        MESSAGE_TASK_ACTIVE = 1u;
        FUN_000431b4(canvas + 0x24);
        FUN_000432d0();
        FUN_000431c0();
        MESSAGE_TASK_RENDERED = was_active;
    }
    if (*(volatile uint8_t *)(state + 0xf6u) < 2u) {
        MESSAGE_TASK_RENDERED = 0u;
        FUN_000431c0();
        return 0u;
    }

    state = FUN_000167a8();
    uint32_t message_type = FUN_0003483c(
        (uint8_t)(*(volatile uint8_t *)(state + 0xddu) - 1u));
    TASK_LOG(0x000a8e84u, message_type);
    if (MESSAGE_TASK_RENDERED != 0u)
        return 0u;

    FUN_000432ec();
    for (uint32_t frame = 0u; frame != 8u; ++frame) {
        uint32_t glyph;
        switch (message_type) {
        case 1u: glyph = 0x37u; break;
        case 2u: glyph = 0x36u; break;
        case 3u: glyph = 0x3au; break;
        case 4u: glyph = 0x39u; break;
        default: glyph = 0x38u; break;
        }
        uint32_t x = FUN_0007d3ee();
        uint32_t y = FUN_0007d446() + 0x3au;
        FUN_00043484(glyph, x, y, 0u, 0u, 0u);

        for (uint32_t row = 0u; row != 199u; ++row) {
            uint8_t *pixels = *(uint8_t **)(void *)(canvas + 0x24u + row * 4u);
            const uint8_t *mask = MASK_TABLE + (row % 26u) * 0xa00u +
                                  (uint32_t)MASK_PHASE[frame] * 0x140u;
            for (uint32_t column = 0u; column != 0x140u; ++column) {
                uint8_t pixel = pixels[column];
                if (pixel != 0u)
                    pixels[column] = (uint8_t)(pixel & mask[column]);
            }
        }
        state = FUN_000167a8();
        uintptr_t left = *(volatile uintptr_t *)(state + 0xeb4u);
        state = FUN_000167a8();
        FUN_00047260(left, *(volatile uintptr_t *)(state + 0xeb8u),
                     0u, 0u, 0x280u, 199u);
    }
    FUN_000432d0();
    MESSAGE_TASK_RENDERED = 1u;
    return 0u;
}
