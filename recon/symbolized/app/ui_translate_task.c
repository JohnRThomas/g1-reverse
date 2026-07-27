#include "g1_app_symbols.h"
struct k_mutex;
/* readable reconstruction; identity: FUN_0003fecc @ 0x0003fecc
 * public-name: ui_translate_task
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   gui_set_active_canvas                    <= FUN_000431b4 @ 0x000431b4
 *   gui_screen_clear                         <= FUN_000431c0 @ 0x000431c0
 *   gui_canvas_flags_set_bit1                <= FUN_000432d0 @ 0x000432d0
 *   gui_canvas_flags_clear_bit1              <= FUN_000432ec @ 0x000432ec
 *   gui_reset_dynamic_bitmap_frame_state     <= FUN_00043308 @ 0x00043308
 *   gui_bmp_dynamic_bitmap_draw              <= FUN_0004334c @ 0x0004334c
 *   gui_bmp_bitmap_draw                      <= FUN_00043484 @ 0x00043484
 *   imu_pitch_task_reset_render_state        <= FUN_000436f8 @ 0x000436f8
 *   gui_screen_fade_out_transition           <= FUN_0004382c @ 0x0004382c
 *   gui_utf_draw                             <= FUN_00043e90 @ 0x00043e90
 *   gui_clock_draw                           <= FUN_000442bc @ 0x000442bc
 *   clean_fb_data                            <= FUN_000471cc @ 0x000471cc
 *   reflash_fb_data_to_lcd                   <= FUN_00047260 @ 0x00047260
 *   unix_timestamp_to_datetime               <= FUN_0004a1b8 @ 0x0004a1b8
 *   k_mutex_lock                             <= FUN_000723b8 @ 0x000723b8
 *   k_mutex_unlock                           <= FUN_00072558 @ 0x00072558
 *   snprintf                                 <= FUN_00077914 @ 0x00077914
 *   get_timestamp                            <= FUN_0007d224 @ 0x0007d224
 *   gui_utf_adv_draw_configure               <= FUN_0007d3dc @ 0x0007d3dc
 *   device_info_text_width_get               <= FUN_0007d3ee @ 0x0007d3ee
 *   device_info_text_height_get_clamped      <= FUN_0007d446 @ 0x0007d446
 *   log_message                              <= FUN_0007dda4 @ 0x0007dda4
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_aa487                             @ 0x000aa487   [INLINED -- G6 literal batch]
 *   rodata_aa4ea                             @ 0x000aa4ea
 *   rodata_aa4f0                             @ 0x000aa4f0   [INLINED -- G6 literal batch]
 *   rodata_aa517                             @ 0x000aa517   [INLINED -- G6 literal batch]
 *   rodata_aa53a                             @ 0x000aa53a   [INLINED -- G6 literal batch]
 *   rodata_aa56c                             @ 0x000aa56c   [INLINED -- G6 literal batch]
 *   rodata_aa599                             @ 0x000aa599   [INLINED -- G6 literal batch]
 *   rodata_aae20                             @ 0x000aae20
 *   g_log_level                              @ 0x2000230c
 *   g_translate_lang_string_table            @ 0x200024f4
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_ui_state_mutex                         @ 0x20007b3c
 *   g_even_ai_render_state                   @ 0x2000a038
 *   g_2000f6ec                               @ 0x2000f6ec
 *   g_2001cc3e                               @ 0x2001cc3e
 *   g_even_ai_render_state_init_val          @ 0x2001cdd7
 */
/* CPUAPP ui_translate_task @ 0x0003fecc.
 * Raw/back-map identity: FUN_0003fecc, exact reachable extent 0x818 bytes. */
#include <stdint.h>
#include "../../headers/g1_log.h"

extern uintptr_t get_device_info(void);
extern void gui_set_active_canvas(void *framebuffer);
extern void gui_canvas_flags_set_bit1(void);
extern void gui_screen_clear(void);
extern void imu_pitch_task_reset_render_state(void);
extern void gui_utf_adv_draw_configure(void);
extern void gui_reset_dynamic_bitmap_frame_state(void);
extern void gui_canvas_flags_clear_bit1(void);
extern uint64_t memset_bytes(void *destination, uint32_t value, uint32_t length);
extern void *memcpy(void *destination, const void *source, uint32_t length);
extern uint32_t k_mutex_lock(void *lock, uint32_t key, uint32_t timeout_low,
                            uint32_t timeout_high);
extern int k_mutex_unlock(struct k_mutex *);
extern int snprintf(void *destination, uint32_t length,
                       const char *format, ...);
extern uint32_t get_timestamp(void);
extern uint32_t device_info_text_width_get(void);
extern uint32_t device_info_text_height_get_clamped(void);
extern void gui_utf_draw(uint32_t a0, const void *text, uint32_t a2,
                         uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1,
                         uint32_t style, uint32_t a8, uint32_t a9,
                         uint32_t a10, uint32_t a11);
extern void gui_clock_draw(uint32_t content, uint32_t x0, uint32_t y0,
                         uint32_t x1, uint32_t y1, uint32_t style,
                         uint32_t inverted);
extern void gui_bmp_bitmap_draw(uint32_t glyph, uint32_t x, uint32_t y,
                         uint32_t a3, uint32_t a4, uint32_t a5);
extern void gui_bmp_dynamic_bitmap_draw(uint32_t glyph, uint32_t x, uint32_t y,
                         uint32_t a3, uint32_t a4, uint32_t a5,
                         uint32_t a6);
extern void clean_fb_data(void *rows, uint32_t a1, uint32_t x0, uint32_t y0,
                         uint32_t x1, uint32_t y1);
extern void reflash_fb_data_to_lcd(uintptr_t left, uintptr_t right, uint32_t x0,
                         uint32_t y0, uint32_t x1, uint32_t y1);
extern void unix_timestamp_to_datetime(uint32_t content, void *metrics);
extern void gui_screen_fade_out_transition(void);

#define TRANSLATE_STATE ((volatile uint8_t *)((unsigned long)&g_2000f6ec) /*=0x2000f6ec*/)
#define TRANSLATE_TEXT ((char *)((unsigned long)&g_2001cc3e) /*=0x2001cc3e*/)
#define TRANSLATE_LOCK ((void *)((unsigned long)&g_ui_state_mutex) /*=0x20007b3c*/)
#define UI_CONTEXT ((volatile uint32_t *)((unsigned long)&g_even_ai_render_state) /*=0x2000a038*/)
#define LANGUAGE_NAMES ((const uintptr_t *)((unsigned long)&g_translate_lang_string_table) /*=0x200024f4*/)
#define LOG_LEVEL (*(volatile int32_t *)((unsigned long)&g_log_level) /*=0x2000230c*/)
#define LOG_ROUTE (*(volatile uint32_t *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)
#define MASK_TABLE ((const uint8_t *)((unsigned long)&rodata_aae20) /*=0xaae20*/)

#define TASK_LOG(format, ...) do { \
    if (LOG_ROUTE == 0u) log_message((format), ##__VA_ARGS__); \
    else debug_print((format), ##__VA_ARGS__); \
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
    snprintf((task_label), 10u, (const char *)((unsigned long)&rodata_aa4ea) /*=0xaa4ea*/, \
                 LANGUAGE_NAMES[_dlp_original - 1u], \
                 LANGUAGE_NAMES[_dlp_translated - 1u]); \
    if (LOG_LEVEL > 3) TASK_LOG(((unsigned long)"%s(): draw translate type content\n") /*=0xaa517*/, ((unsigned long)"ui_translate_task") /*=0xaa599*/); \
    _dlp_x0 = device_info_text_width_get(); _dlp_y0 = device_info_text_height_get_clamped(); \
    _dlp_x1 = device_info_text_width_get(); _dlp_y1 = device_info_text_height_get_clamped(); \
    gui_utf_draw(0u, (task_label), 3u, _dlp_x0, _dlp_y0 + 0x6eu, \
                 _dlp_x1 + 0x50u, _dlp_y1 + 0x89u, 1u, 0u, 0u, 0u, 0u); \
    TRANSLATE_STATE[0x11] = (uint8_t)_dlp_original; \
    TRANSLATE_STATE[0x10] = (uint8_t)_dlp_translated; \
} while (0)

#define draw_translation_content(task_state) do { \
    uintptr_t _dtc_settings = get_device_info(); \
    uint32_t _dtc_inverted = (*(volatile uint8_t *)( \
        *(volatile uintptr_t *)(_dtc_settings + 0xfecu) + 0x5eu) != 1u); \
    uint32_t _dtc_content = get_timestamp(); \
    uint32_t _dtc_x0 = device_info_text_width_get(), _dtc_y0 = device_info_text_height_get_clamped(); \
    uint32_t _dtc_x1 = device_info_text_width_get(), _dtc_y1 = device_info_text_height_get_clamped(); \
    (void)(task_state); \
    gui_clock_draw(_dtc_content, _dtc_x0, _dtc_y0 + 2u, _dtc_x1 + 0x50u, \
                 _dtc_y1 + 0x1du, 3u, _dtc_inverted); \
} while (0)

uint32_t ui_translate_task(uint8_t *canvas, uint32_t unused, uint32_t phase)
{
    uintptr_t state = get_device_info();
    uint8_t label[10];
    (void)unused;

    gui_set_active_canvas(canvas + 0x24u);
    gui_canvas_flags_set_bit1();

    if (TRANSLATE_STATE[0] == 0u) {
        if (phase == 1u) {
            if (LOG_LEVEL > 3)
                TASK_LOG(((unsigned long)"%s(): translate language type error! trans_info->original_type %d trans_info->translation_type %d\n") /*=0xaa487*/, ((unsigned long)"ui_translate_task") /*=0xaa599*/);
            if (TRANSLATE_STATE[1] != 0u)
                return 0u;
            if (LOG_LEVEL > 2)
                TASK_LOG(((unsigned long)"%s(): ENTER translate INIT process...\n") /*=0xaa4f0*/, ((unsigned long)"ui_translate_task") /*=0xaa599*/);
            gui_utf_adv_draw_configure();
            gui_screen_clear();
            imu_pitch_task_reset_render_state();
            memset_bytes((void *)(TRANSLATE_STATE + 2), 0u, 0x10u);
            UI_CONTEXT[7] = 0x80u;
            UI_CONTEXT[2] = 0u;
            UI_CONTEXT[3] = 0u;
            UI_CONTEXT[0] = ((unsigned long)&g_even_ai_render_state_init_val) /*=0x2001cdd7*/;
            UI_CONTEXT[5] = 0u;
            UI_CONTEXT[6] = 0u;
            UI_CONTEXT[1] = 0u;
            UI_CONTEXT[4] = 0u;
            *(volatile uint16_t *)TRANSLATE_STATE = 0x0101u;
            gui_reset_dynamic_bitmap_frame_state();
            gui_canvas_flags_clear_bit1();
            for (uint32_t frame = 0u; frame != 4u; ++frame) {
                uint32_t original = *(volatile uint8_t *)(state + 0xf0u);
                uint32_t translated = *(volatile uint8_t *)(state + 0xefu);
                if (original != 0u && original < 0x13u &&
                    translated != 0u && translated < 0x13u)
                    draw_language_pair(state, (char *)label);
                else if (LOG_LEVEL > 0)
                    TASK_LOG(((unsigned long)"%s(): translate process received exit packet ...\n") /*=0xaa53a*/, ((unsigned long)"ui_translate_task") /*=0xaa599*/, original, translated);

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
                uintptr_t context = get_device_info();
                uintptr_t left = *(volatile uintptr_t *)(context + 0xeb4u);
                context = get_device_info();
                reflash_fb_data_to_lcd(left, *(volatile uintptr_t *)(context + 0xeb8u),
                             0u, 0u, 0x280u, 199u);
            }
            gui_canvas_flags_set_bit1();
            return 0u;
        }
        if (phase != 2u)
            return 0u;
        if (LOG_LEVEL > 2)
            TASK_LOG(((unsigned long)"%s(): suspend_en is 1, reflash suspend icon\n") /*=0xaa56c*/, ((unsigned long)"ui_translate_task") /*=0xaa599*/);
        gui_screen_clear();
        gui_utf_adv_draw_configure();
        clear_translate_ui_state();
        memset_bytes((void *)TRANSLATE_STATE, 0u, 0x12u);
        return 0u;
    }

    if (TRANSLATE_STATE[0] != 1u)
        return 0u;
    if (phase == 0u) {
        if (TRANSLATE_STATE[2] == 0u) {
            uint32_t x = device_info_text_width_get();
            uint32_t y = device_info_text_height_get_clamped();
            gui_bmp_dynamic_bitmap_draw(1u, x, y + 0x36u, 0u, 0u, 0u, 0u);
        }
        *(uint64_t *)(void *)label = 0u;
        *(uint16_t *)(void *)(label + 8) = 0u;
        unix_timestamp_to_datetime(get_timestamp(), label);
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
            TASK_LOG(((unsigned long)"%s(): suspend_en is 1, reflash suspend icon\n") /*=0xaa56c*/, ((unsigned long)"ui_translate_task") /*=0xaa599*/);
        gui_screen_fade_out_transition();
        gui_utf_adv_draw_configure();
        clear_translate_ui_state();
        memset_bytes((void *)TRANSLATE_STATE, 0u, 0x12u);
        return 0u;
    }
    if (phase != 1u)
        return 0u;

    /* The lock call consumes r1 returned by the preceding clear routine in
     * the shipped ABI; model its two-register result explicitly. */
    uint64_t clear_result = memset_bytes(TRANSLATE_TEXT, 0u, 400u);
    k_mutex_lock(TRANSLATE_LOCK, (uint32_t)(clear_result >> 32),
                 0xffffffffu, 0xffffffffu);
    TRANSLATE_STATE[2] = *(volatile uint8_t *)(state + 0xf1u);
    uint32_t presentation = *(volatile uint8_t *)(state + 0xf2u);
    memcpy(TRANSLATE_TEXT, (const void *)(state + 0xf5u), 400u);
    k_mutex_unlock(TRANSLATE_LOCK);

    if (TRANSLATE_STATE[2] == 1u) {
        if (LOG_LEVEL > 2)
            TASK_LOG(((unsigned long)"%s(): suspend_en is 1, reflash suspend icon\n") /*=0xaa56c*/, ((unsigned long)"ui_translate_task") /*=0xaa599*/);
        uint32_t x = device_info_text_width_get();
        uint32_t y = device_info_text_height_get_clamped();
        gui_bmp_bitmap_draw(0x1bu, x, y + 0x36u, 0u, 0u, 0u);
    }

    uint32_t original = *(volatile uint8_t *)(state + 0xf0u);
    uint32_t translated = *(volatile uint8_t *)(state + 0xefu);
    if (original != 0u && original < 0x13u && translated != 0u && translated < 0x13u) {
        if (TRANSLATE_STATE[0x11] != original || TRANSLATE_STATE[0x10] != translated)
            draw_language_pair(state, (char *)label);
    } else if (LOG_LEVEL > 0) {
        TASK_LOG(((unsigned long)"%s(): translate process received exit packet ...\n") /*=0xaa53a*/, ((unsigned long)"ui_translate_task") /*=0xaa599*/, original, translated);
    }

    if (presentation == 3u || presentation == 4u) {
        uintptr_t context = get_device_info();
        uint8_t **rows = (uint8_t **)(context + 0xb90u);
        for (uint32_t mask_phase = 0x640u;; mask_phase = 0x500u) {
            int32_t first_row = (int32_t)device_info_text_height_get_clamped();
            int32_t last_row = (int32_t)device_info_text_height_get_clamped() + 0x87;
            for (int32_t row = first_row; row < last_row; ++row) {
                int32_t first_column = (int32_t)device_info_text_width_get() + 0x58;
                int32_t last_column = ((int32_t)device_info_text_width_get() + 0x240) / 2;
                const uint8_t *mask = MASK_TABLE + (row % 26) * 0xa00 + mask_phase;
                for (int32_t column = first_column; column < last_column; ++column) {
                    uint8_t pixel = rows[row][column];
                    if (pixel != 0u)
                        rows[row][column] = (uint8_t)(pixel & mask[column]);
                }
            }
            context = get_device_info();
            uintptr_t left = *(volatile uintptr_t *)(context + 0xeb4u);
            context = get_device_info();
            uintptr_t right = *(volatile uintptr_t *)(context + 0xeb8u);
            uint32_t x0 = device_info_text_width_get(), y0 = device_info_text_height_get_clamped();
            uint32_t x1 = device_info_text_width_get(), y1 = device_info_text_height_get_clamped();
            reflash_fb_data_to_lcd(left, right, x0 + 0x58u, y0, x1 + 0x240u, y1 + 0x88u);
            if (mask_phase == 0x500u)
                break;
        }
        uint32_t x0 = device_info_text_width_get(), y0 = device_info_text_height_get_clamped();
        uint32_t x1 = device_info_text_width_get(), y1 = device_info_text_height_get_clamped();
        clean_fb_data(rows, 0u, x0 + 0x58u, y0, x1 + 0x240u, y1 + 0x88u);
        if (TRANSLATE_STATE[2] == 0u) {
            uint32_t x = device_info_text_width_get(), y = device_info_text_height_get_clamped();
            gui_bmp_dynamic_bitmap_draw(1u, x, y + 0x36u, 0u, 0u, 0u, 0u);
        }
        gui_canvas_flags_clear_bit1();
        for (uint32_t frame = 2u; frame != 4u; ++frame) {
            uint32_t x0a = device_info_text_width_get(), y0a = device_info_text_height_get_clamped();
            uint32_t x1a = device_info_text_width_get(), y1a = device_info_text_height_get_clamped();
            gui_utf_draw(0u, TRANSLATE_TEXT, 0u, x0a + 0x58u, y0a,
                         x1a + 0x240u, y1a + 0x88u, 5u, 0u, 0u, 0u, 0u);
            int32_t first_column = ((int32_t)device_info_text_width_get() + 0x58) / 2;
            int32_t column_count = ((int32_t)device_info_text_width_get() + 0x240 -
                                    ((int32_t)device_info_text_width_get() + 0x58)) / 2;
            int32_t first_row = (int32_t)device_info_text_height_get_clamped();
            int32_t row_count = (int32_t)device_info_text_height_get_clamped() + 0x88 - first_row;
            for (int32_t row = 0; row < row_count; ++row) {
                const uint8_t *mask = MASK_TABLE + (row % 26) * 0xa00 + frame * 0x140u;
                for (int32_t column = 0; column < column_count; ++column) {
                    uint8_t pixel = rows[first_row + row][first_column + column];
                    if (pixel != 0u)
                        rows[first_row + row][first_column + column] =
                            (uint8_t)(pixel & mask[column]);
                }
            }
            context = get_device_info();
            uintptr_t left = *(volatile uintptr_t *)(context + 0xeb4u);
            context = get_device_info();
            reflash_fb_data_to_lcd(left, *(volatile uintptr_t *)(context + 0xeb8u),
                         (uint32_t)first_column, (uint32_t)first_row,
                         (uint32_t)(first_column + column_count),
                         (uint32_t)(first_row + row_count));
        }
        gui_canvas_flags_set_bit1();
        if (TRANSLATE_STATE[2] == 0u) {
            uint32_t x = device_info_text_width_get(), y = device_info_text_height_get_clamped();
            gui_bmp_dynamic_bitmap_draw(1u, x, y + 0x36u, 0u, 0u, 0u, 0u);
        }
    } else {
        uint32_t x0 = device_info_text_width_get(), y0 = device_info_text_height_get_clamped();
        uint32_t x1 = device_info_text_width_get(), y1 = device_info_text_height_get_clamped();
        gui_utf_draw(0u, TRANSLATE_TEXT, 0u, x0 + 0x58u, y0,
                     x1 + 0x240u, y1 + 0x88u, 5u, 0u, 0u, 0u, 0u);
    }
    return 0u;
}
