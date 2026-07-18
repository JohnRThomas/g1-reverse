/* CPUAPP ui_translate_task @ 0x0003fecc.
 * Raw/back-map identity: FUN_0003fecc, exact reachable extent 0x818 bytes. */
#include <stdint.h>

extern uintptr_t FUN_000167a8(void);
extern void FUN_000431b4(void *framebuffer);
extern void FUN_000432d0(void);
extern void FUN_000431c0(void);
extern void FUN_000436f8(void);
extern void FUN_0007d3dc(void);
extern void FUN_00043308(void);
extern void FUN_000432ec(void);
extern uint64_t FUN_00086c78(void *destination, uint32_t value, uint32_t length);
extern void *FUN_00086c04(void *destination, const void *source, uint32_t length);
extern uint32_t FUN_000723b8(void *lock, uint32_t key, uint32_t timeout_low,
                            uint32_t timeout_high);
extern uint32_t FUN_00072558(void *lock);
extern int FUN_00077914(void *destination, uint32_t length,
                       const char *format, ...);
extern uint32_t FUN_0007d224(void);
extern uint32_t FUN_0007d3ee(void);
extern uint32_t FUN_0007d446(void);
extern void FUN_00043e90(uint32_t a0, const void *text, uint32_t a2,
                         uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1,
                         uint32_t style, uint32_t a8, uint32_t a9,
                         uint32_t a10, uint32_t a11);
extern void FUN_000442bc(uint32_t content, uint32_t x0, uint32_t y0,
                         uint32_t x1, uint32_t y1, uint32_t style,
                         uint32_t inverted);
extern void FUN_00043484(uint32_t glyph, uint32_t x, uint32_t y,
                         uint32_t a3, uint32_t a4, uint32_t a5);
extern void FUN_0004334c(uint32_t glyph, uint32_t x, uint32_t y,
                         uint32_t a3, uint32_t a4, uint32_t a5,
                         uint32_t a6);
extern void FUN_000471cc(void *rows, uint32_t a1, uint32_t x0, uint32_t y0,
                         uint32_t x1, uint32_t y1);
extern void FUN_00047260(uintptr_t left, uintptr_t right, uint32_t x0,
                         uint32_t y0, uint32_t x1, uint32_t y1);
extern void FUN_0004a1b8(uint32_t content, void *metrics);
extern void FUN_0004382c(void);
extern void FUN_00019c70(uintptr_t format, ...);
extern void FUN_0007dda4(uintptr_t format, ...);

#define TRANSLATE_STATE ((volatile uint8_t *)0x2000f6ecu)
#define TRANSLATE_TEXT ((char *)0x2001cc3eu)
#define TRANSLATE_LOCK ((void *)0x20007b3cu)
#define UI_CONTEXT ((volatile uint32_t *)0x2000a038u)
#define LANGUAGE_NAMES ((const uintptr_t *)0x200024f4u)
#define LOG_LEVEL (*(volatile int32_t *)0x2000230cu)
#define LOG_ROUTE (*(volatile uint32_t *)0x20007554u)
#define MASK_TABLE ((const uint8_t *)0x000aae20u)

#define TASK_LOG(format, ...) do { \
    if (LOG_ROUTE == 0u) FUN_0007dda4((format), ##__VA_ARGS__); \
    else FUN_00019c70((format), ##__VA_ARGS__); \
} while (0)

#define clear_translate_ui_state() do { \
    UI_CONTEXT[2] = 0u; UI_CONTEXT[3] = 0u; \
    UI_CONTEXT[5] = 0u; UI_CONTEXT[6] = 0u; \
    UI_CONTEXT[1] = 0u; UI_CONTEXT[4] = 0u; \
} while (0)

#define draw_language_pair(task_state, task_label) do { \
    uint32_t _dlp_original = *(volatile uint8_t *)((task_state) + 0xf0u); \
    uint32_t _dlp_translated = *(volatile uint8_t *)((task_state) + 0xefu); \
    uint32_t _dlp_x0, _dlp_y0, _dlp_x1, _dlp_y1; \
    (task_label)[0] = '\0'; (task_label)[1] = '\0'; \
    (task_label)[2] = '\0'; (task_label)[3] = '\0'; \
    (task_label)[4] = '\0'; (task_label)[5] = '\0'; \
    (task_label)[6] = '\0'; (task_label)[7] = '\0'; \
    (task_label)[8] = '\0'; (task_label)[9] = '\0'; \
    FUN_00077914((task_label), 10u, (const char *)0x000aa4eau, \
                 LANGUAGE_NAMES[_dlp_original - 1u], \
                 LANGUAGE_NAMES[_dlp_translated - 1u]); \
    if (LOG_LEVEL > 3) TASK_LOG(0x000aa517u, 0x000aa599u); \
    _dlp_x0 = FUN_0007d3ee(); _dlp_y0 = FUN_0007d446(); \
    _dlp_x1 = FUN_0007d3ee(); _dlp_y1 = FUN_0007d446(); \
    FUN_00043e90(0u, (task_label), 3u, _dlp_x0, _dlp_y0 + 0x6eu, \
                 _dlp_x1 + 0x50u, _dlp_y1 + 0x89u, 1u, 0u, 0u, 0u, 0u); \
    TRANSLATE_STATE[0x11] = (uint8_t)_dlp_original; \
    TRANSLATE_STATE[0x10] = (uint8_t)_dlp_translated; \
} while (0)

#define draw_translation_content(task_state) do { \
    uintptr_t _dtc_settings = FUN_000167a8(); \
    uint32_t _dtc_inverted = (*(volatile uint8_t *)( \
        *(volatile uintptr_t *)(_dtc_settings + 0xfecu) + 0x5eu) != 1u); \
    uint32_t _dtc_content = FUN_0007d224(); \
    uint32_t _dtc_x0 = FUN_0007d3ee(), _dtc_y0 = FUN_0007d446(); \
    uint32_t _dtc_x1 = FUN_0007d3ee(), _dtc_y1 = FUN_0007d446(); \
    (void)(task_state); \
    FUN_000442bc(_dtc_content, _dtc_x0, _dtc_y0 + 2u, _dtc_x1 + 0x50u, \
                 _dtc_y1 + 0x1du, 3u, _dtc_inverted); \
} while (0)

uint32_t ui_translate_task(uint8_t *canvas, uint32_t unused, uint32_t phase)
{
    uintptr_t state = FUN_000167a8();
    uint8_t label[10];
    (void)unused;

    FUN_000431b4(canvas + 0x24u);
    FUN_000432d0();

    if (TRANSLATE_STATE[0] == 0u) {
        if (phase == 1u) {
            if (LOG_LEVEL > 3)
                TASK_LOG(0x000aa487u, 0x000aa599u);
            if (TRANSLATE_STATE[1] != 0u)
                return 0u;
            if (LOG_LEVEL > 2)
                TASK_LOG(0x000aa4f0u, 0x000aa599u);
            FUN_0007d3dc();
            FUN_000431c0();
            FUN_000436f8();
            FUN_00086c78((void *)(TRANSLATE_STATE + 2), 0u, 0x10u);
            UI_CONTEXT[7] = 0x80u;
            UI_CONTEXT[2] = 0u;
            UI_CONTEXT[3] = 0u;
            UI_CONTEXT[0] = 0x2001cdd7u;
            UI_CONTEXT[5] = 0u;
            UI_CONTEXT[6] = 0u;
            UI_CONTEXT[1] = 0u;
            UI_CONTEXT[4] = 0u;
            *(volatile uint16_t *)TRANSLATE_STATE = 0x0101u;
            FUN_00043308();
            FUN_000432ec();
            for (uint32_t frame = 0u; frame != 4u; ++frame) {
                uint32_t original = *(volatile uint8_t *)(state + 0xf0u);
                uint32_t translated = *(volatile uint8_t *)(state + 0xefu);
                if (original != 0u && original < 0x13u &&
                    translated != 0u && translated < 0x13u)
                    draw_language_pair(state, (char *)label);
                else if (LOG_LEVEL > 0)
                    TASK_LOG(0x000aa53au, 0x000aa599u, original, translated);

                draw_translation_content(state);
                for (uint32_t row = 0u; row != 199u; ++row) {
                    uint8_t *pixels = *(uint8_t **)(void *)(canvas + 0x24u + row * 4u);
                    const uint8_t *mask = MASK_TABLE + (row % 26u) * 0xa00u +
                                          (uint32_t)((const uint8_t[]){1,3,5,7})[frame] * 0x140u;
                    for (uint32_t column = 0u; column != 0x140u; ++column) {
                        uint8_t pixel = pixels[column];
                        if (pixel != 0u)
                            pixels[column] = (uint8_t)(pixel & mask[column]);
                    }
                }
                uintptr_t context = FUN_000167a8();
                uintptr_t left = *(volatile uintptr_t *)(context + 0xeb4u);
                context = FUN_000167a8();
                FUN_00047260(left, *(volatile uintptr_t *)(context + 0xeb8u),
                             0u, 0u, 0x280u, 199u);
            }
            FUN_000432d0();
            return 0u;
        }
        if (phase != 2u)
            return 0u;
        if (LOG_LEVEL > 2)
            TASK_LOG(0x000aa56cu, 0x000aa599u);
        FUN_000431c0();
        FUN_0007d3dc();
        clear_translate_ui_state();
        FUN_00086c78((void *)TRANSLATE_STATE, 0u, 0x12u);
        return 0u;
    }

    if (TRANSLATE_STATE[0] != 1u)
        return 0u;
    if (phase == 0u) {
        if (TRANSLATE_STATE[2] == 0u) {
            uint32_t x = FUN_0007d3ee();
            uint32_t y = FUN_0007d446();
            FUN_0004334c(1u, x, y + 0x36u, 0u, 0u, 0u, 0u);
        }
        *(uint64_t *)(void *)label = 0u;
        *(uint16_t *)(void *)(label + 8) = 0u;
        FUN_0004a1b8(FUN_0007d224(), label);
        if (*(volatile uint16_t *)(TRANSLATE_STATE + 0x0cu) == *(uint16_t *)(void *)(label + 8) &&
            *(volatile uint16_t *)(TRANSLATE_STATE + 0x0au) == *(uint16_t *)(void *)(label + 6))
            return 0u;
        *(volatile uint16_t *)(TRANSLATE_STATE + 0x0cu) = *(uint16_t *)(void *)(label + 8);
        *(volatile uint16_t *)(TRANSLATE_STATE + 0x0au) = *(uint16_t *)(void *)(label + 6);
        draw_translation_content(state);
        return 0u;
    }
    if (phase == 2u) {
        if (LOG_LEVEL > 2)
            TASK_LOG(0x000aa56cu, 0x000aa599u);
        FUN_0004382c();
        FUN_0007d3dc();
        clear_translate_ui_state();
        FUN_00086c78((void *)TRANSLATE_STATE, 0u, 0x12u);
        return 0u;
    }
    if (phase != 1u)
        return 0u;

    /* The lock call consumes r1 returned by the preceding clear routine in
     * the shipped ABI; model its two-register result explicitly. */
    uint64_t clear_result = FUN_00086c78(TRANSLATE_TEXT, 0u, 400u);
    FUN_000723b8(TRANSLATE_LOCK, (uint32_t)(clear_result >> 32),
                 0xffffffffu, 0xffffffffu);
    TRANSLATE_STATE[2] = *(volatile uint8_t *)(state + 0xf1u);
    uint32_t presentation = *(volatile uint8_t *)(state + 0xf2u);
    FUN_00086c04(TRANSLATE_TEXT, (const void *)(state + 0xf5u), 400u);
    FUN_00072558(TRANSLATE_LOCK);

    if (TRANSLATE_STATE[2] == 1u) {
        if (LOG_LEVEL > 2)
            TASK_LOG(0x000aa56cu, 0x000aa599u);
        uint32_t x = FUN_0007d3ee();
        uint32_t y = FUN_0007d446();
        FUN_00043484(0x1bu, x, y + 0x36u, 0u, 0u, 0u);
    }

    uint32_t original = *(volatile uint8_t *)(state + 0xf0u);
    uint32_t translated = *(volatile uint8_t *)(state + 0xefu);
    if (original != 0u && original < 0x13u && translated != 0u && translated < 0x13u) {
        if (TRANSLATE_STATE[0x11] != original || TRANSLATE_STATE[0x10] != translated)
            draw_language_pair(state, (char *)label);
    } else if (LOG_LEVEL > 0) {
        TASK_LOG(0x000aa53au, 0x000aa599u, original, translated);
    }

    if (presentation == 3u || presentation == 4u) {
        uintptr_t context = FUN_000167a8();
        uint8_t **rows = (uint8_t **)(context + 0xb90u);
        for (uint32_t mask_phase = 0x640u;; mask_phase = 0x500u) {
            int32_t first_row = (int32_t)FUN_0007d446();
            int32_t last_row = (int32_t)FUN_0007d446() + 0x87;
            for (int32_t row = first_row; row < last_row; ++row) {
                int32_t first_column = (int32_t)FUN_0007d3ee() + 0x58;
                int32_t last_column = ((int32_t)FUN_0007d3ee() + 0x240) / 2;
                const uint8_t *mask = MASK_TABLE + (row % 26) * 0xa00 + mask_phase;
                for (int32_t column = first_column; column < last_column; ++column) {
                    uint8_t pixel = rows[row][column];
                    if (pixel != 0u)
                        rows[row][column] = (uint8_t)(pixel & mask[column]);
                }
            }
            context = FUN_000167a8();
            uintptr_t left = *(volatile uintptr_t *)(context + 0xeb4u);
            context = FUN_000167a8();
            uintptr_t right = *(volatile uintptr_t *)(context + 0xeb8u);
            uint32_t x0 = FUN_0007d3ee(), y0 = FUN_0007d446();
            uint32_t x1 = FUN_0007d3ee(), y1 = FUN_0007d446();
            FUN_00047260(left, right, x0 + 0x58u, y0, x1 + 0x240u, y1 + 0x88u);
            if (mask_phase == 0x500u)
                break;
        }
        uint32_t x0 = FUN_0007d3ee(), y0 = FUN_0007d446();
        uint32_t x1 = FUN_0007d3ee(), y1 = FUN_0007d446();
        FUN_000471cc(rows, 0u, x0 + 0x58u, y0, x1 + 0x240u, y1 + 0x88u);
        if (TRANSLATE_STATE[2] == 0u) {
            uint32_t x = FUN_0007d3ee(), y = FUN_0007d446();
            FUN_0004334c(1u, x, y + 0x36u, 0u, 0u, 0u, 0u);
        }
        FUN_000432ec();
        for (uint32_t frame = 2u; frame != 4u; ++frame) {
            uint32_t x0a = FUN_0007d3ee(), y0a = FUN_0007d446();
            uint32_t x1a = FUN_0007d3ee(), y1a = FUN_0007d446();
            FUN_00043e90(0u, TRANSLATE_TEXT, 0u, x0a + 0x58u, y0a,
                         x1a + 0x240u, y1a + 0x88u, 5u, 0u, 0u, 0u, 0u);
            int32_t first_column = ((int32_t)FUN_0007d3ee() + 0x58) / 2;
            int32_t column_count = ((int32_t)FUN_0007d3ee() + 0x240 -
                                    ((int32_t)FUN_0007d3ee() + 0x58)) / 2;
            int32_t first_row = (int32_t)FUN_0007d446();
            int32_t row_count = (int32_t)FUN_0007d446() + 0x88 - first_row;
            for (int32_t row = 0; row < row_count; ++row) {
                const uint8_t *mask = MASK_TABLE + (row % 26) * 0xa00 + frame * 0x140u;
                for (int32_t column = 0; column < column_count; ++column) {
                    uint8_t pixel = rows[first_row + row][first_column + column];
                    if (pixel != 0u)
                        rows[first_row + row][first_column + column] =
                            (uint8_t)(pixel & mask[column]);
                }
            }
            context = FUN_000167a8();
            uintptr_t left = *(volatile uintptr_t *)(context + 0xeb4u);
            context = FUN_000167a8();
            FUN_00047260(left, *(volatile uintptr_t *)(context + 0xeb8u),
                         (uint32_t)first_column, (uint32_t)first_row,
                         (uint32_t)(first_column + column_count),
                         (uint32_t)(first_row + row_count));
        }
        FUN_000432d0();
        if (TRANSLATE_STATE[2] == 0u) {
            uint32_t x = FUN_0007d3ee(), y = FUN_0007d446();
            FUN_0004334c(1u, x, y + 0x36u, 0u, 0u, 0u, 0u);
        }
    } else {
        uint32_t x0 = FUN_0007d3ee(), y0 = FUN_0007d446();
        uint32_t x1 = FUN_0007d3ee(), y1 = FUN_0007d446();
        FUN_00043e90(0u, TRANSLATE_TEXT, 0u, x0 + 0x58u, y0,
                     x1 + 0x240u, y1 + 0x88u, 5u, 0u, 0u, 0u, 0u);
    }
    return 0u;
}
