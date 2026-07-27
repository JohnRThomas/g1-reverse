#include "g1_app_symbols.h"
struct k_mutex;
/* readable reconstruction; identity: FUN_0003bfe0 @ 0x0003bfe0
 * public-name: ui_even_ai_task
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_ui_mode_flag_byte1                   <= FUN_00023ee0 @ 0x00023ee0
 *   draw_status_icon_by_state                <= FUN_0003be18 @ 0x0003be18
 *   gui_set_active_canvas                    <= FUN_000431b4 @ 0x000431b4
 *   gui_canvas_flags_set_bit1                <= FUN_000432d0 @ 0x000432d0
 *   gui_canvas_flags_clear_bit1              <= FUN_000432ec @ 0x000432ec
 *   gui_reset_dynamic_bitmap_frame_state     <= FUN_00043308 @ 0x00043308
 *   imu_pitch_task_reset_render_state        <= FUN_000436f8 @ 0x000436f8
 *   gui_screen_fade_out_transition           <= FUN_0004382c @ 0x0004382c
 *   ui_render_scroll_text_frame              <= FUN_000440ec @ 0x000440ec
 *   k_mutex_lock                             <= FUN_000723b8 @ 0x000723b8
 *   k_mutex_unlock                           <= FUN_00072558 @ 0x00072558
 *   gui_utf_adv_draw_configure               <= FUN_0007d3dc @ 0x0007d3dc
 *   device_info_text_width_get               <= FUN_0007d3ee @ 0x0007d3ee
 *   device_info_text_height_get_clamped      <= FUN_0007d446 @ 0x0007d446
 *   safe_memcpy_checked                      <= FUN_00086c1e @ 0x00086c1e
 * address symbols (name @ address):
 *   rodata_a8e98                             @ 0x000a8e98
 *   rodata_a9855                             @ 0x000a9855   [INLINED -- G6 literal batch]
 *   rodata_a9879                             @ 0x000a9879   [INLINED -- G6 literal batch]
 *   rodata_a989f                             @ 0x000a989f   [INLINED -- G6 literal batch]
 *   rodata_a98ce                             @ 0x000a98ce   [INLINED -- G6 literal batch]
 *   rodata_aae20                             @ 0x000aae20
 *   rodata_f7b6f                             @ 0x000f7b6f
 *   g_log_level                              @ 0x2000230c
 *   g_even_ai_saved_page_index               @ 0x200024ec
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_ui_state_mutex                         @ 0x20007b3c
 *   g_20009fd4                               @ 0x20009fd4
 *   g_even_ai_frame_idx                      @ 0x20009fd8
 *   g_even_ai_render_state                   @ 0x2000a038
 *   g_even_ai_line_text_buf                  @ 0x2001b818
 *   g_even_ai_active_flag                    @ 0x2001b9a8
 *   g_even_ai_render_state_init_val          @ 0x2001cdd7
 */
/* Reconstructed ui_even_ai_task @ 0x0003bfe0 (raw: FUN_0003bfe0).
 * Executable extent: 0x0003bfe0..0x0003cb2b (0xb4c bytes).
 * Literal islands at 0x3c2dc, 0x3c644 and 0x3c9a8 are jumped over by the
 * original CFG; the final trailing literal pool begins at 0x3cb2c. */
#include <stdint.h>
#include "../../headers/g1_log.h"

#define ALWAYS_INLINE static __attribute__((always_inline)) inline

/* Callee provenance (readable local name <- raw identity @ address). */
extern uintptr_t get_device_info(void);                         /* FUN_000167a8 @ 0x000167a8 */
/* FUN_0007dda4 @ 0x0007dda4 */
/* FUN_00019c70 @ 0x00019c70 */
extern int get_ui_mode_flag_byte1(void);                                  /* @ 0x00023ee0 */
extern uintptr_t draw_status_icon_by_state(void *, ...);                     /* @ 0x0003be18 */
extern uintptr_t gui_set_active_canvas(uintptr_t);                       /* @ 0x000431b4 */
extern uintptr_t gui_screen_clear(void);                        /* FUN_000431c0 @ 0x000431c0 */
extern uintptr_t gui_canvas_flags_set_bit1(void);                            /* @ 0x000432d0 */
extern uintptr_t gui_canvas_flags_clear_bit1(void);                            /* @ 0x000432ec */
extern uintptr_t gui_reset_dynamic_bitmap_frame_state(void);                            /* @ 0x00043308 */
extern uintptr_t gui_bmp_bitmap_draw(int, ...);                 /* FUN_00043484 @ 0x00043484 */
extern uintptr_t imu_pitch_task_reset_render_state(void);                            /* @ 0x000436f8 */
extern uintptr_t gui_screen_fade_out_transition(void);                            /* @ 0x0004382c */
extern uintptr_t gui_verticalLine_process_bar(int, ...);        /* FUN_0004396c @ 0x0004396c */
extern uintptr_t gui_utf_draw(int, ...);                        /* FUN_00043e90 @ 0x00043e90 */
extern uintptr_t ui_render_scroll_text_frame(int, ...);                        /* @ 0x000440ec */
extern uintptr_t gui_utf_draw_middle(int, ...);                 /* FUN_00044bd8 @ 0x00044bd8 */
extern uintptr_t clean_fb_data(int, ...);                       /* FUN_000471cc @ 0x000471cc */
extern uintptr_t reflash_fb_data_to_lcd(int, ...);              /* FUN_00047260 @ 0x00047260 */
extern int k_mutex_lock(void *, int64_t);                       /* @ 0x000723b8 */
extern int k_mutex_unlock(struct k_mutex *);                          /* @ 0x00072558 */
extern uintptr_t gui_utf_adv_draw_configure(void);                            /* @ 0x0007d3dc */
extern int device_info_text_width_get(void);                                  /* @ 0x0007d3ee */
extern int device_info_text_height_get_clamped(void);                                  /* @ 0x0007d446 */
extern uintptr_t safe_memcpy_checked(void *, const void *, unsigned, unsigned); /* @ 0x00086c1e */
extern uintptr_t memset_bytes(void *, int, unsigned);           /* FUN_00086c78 @ 0x00086c78 */

#define ui_language_get                    get_ui_mode_flag_byte1
#define even_ai_status_icon_render         draw_status_icon_by_state
#define gui_set_active_canvas              gui_set_active_canvas
#define gui_canvas_flags_set_bit1          gui_canvas_flags_set_bit1
#define gui_canvas_flags_clear_bit1        gui_canvas_flags_clear_bit1
#define gui_reset_dynamic_bitmap_state     gui_reset_dynamic_bitmap_frame_state
#define gui_reset_render_offsets           imu_pitch_task_reset_render_state
#define even_ai_exit_animation             gui_screen_fade_out_transition
#define gui_utf_draw_scrolling             ui_render_scroll_text_frame
#define k_mutex_lock_forever               k_mutex_lock
#define k_mutex_unlock                     k_mutex_unlock
#define gui_text_metrics_reset              gui_utf_adv_draw_configure
#define gui_text_left                       device_info_text_width_get
#define gui_text_top                        device_info_text_height_get_clamped
#define memcpy_s                            safe_memcpy_checked

#define G_LOG_LEVEL             (*(volatile int32_t *)((unsigned long)&g_log_level) /*=0x2000230c*/)
#define G_LOGGER_MODE           (*(volatile int32_t *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)
#define G_SAVED_PAGE            (*(volatile int32_t *)((unsigned long)&g_even_ai_saved_page_index) /*=0x200024ec*/)
#define G_FRAME_INDEX           (*(volatile int32_t *)((unsigned long)&g_even_ai_frame_idx) /*=0x20009fd8*/)
#define G_TEXT_RENDERED         (*(volatile int32_t *)((unsigned long)&g_20009fd4) /*=0x20009fd4*/)
#define G_ACTIVE                ((volatile uint8_t *)((unsigned long)&g_even_ai_active_flag) /*=0x2001b9a8*/)
#define G_RENDER_STATE          ((volatile uint32_t *)((unsigned long)&g_even_ai_render_state) /*=0x2000a038*/)
#define G_LINE_TEXT             ((uint8_t *)((unsigned long)&g_even_ai_line_text_buf) /*=0x2001b818*/)
#define G_UI_MUTEX              ((void *)((unsigned long)&g_ui_state_mutex) /*=0x20007b3c*/)

#define LANGUAGE_PRIMARY_TABLE ((const uintptr_t *)0x0008a3a8UL)
#define LANGUAGE_DETAIL_TABLE  ((const uintptr_t *)0x0008a370UL)
#define MASK_BITMAP_BASE       ((const uint8_t *)((unsigned long)&rodata_aae20) /*=0xaae20*/)
#define MASK_FRAME_SEQUENCE    ((const uint8_t *)((unsigned long)&rodata_a8e98) /*=0xa8e98*/)
#define RENDER_STATE_INITIAL   ((uint32_t)((unsigned long)&g_even_ai_render_state_init_val) /*=0x2001cdd7*/)
#define SPACE_TEXT             ((uintptr_t)((unsigned long)&rodata_f7b6f) /*=0xf7b6f*/)
#define LOG_FUNCTION           ((uintptr_t)((unsigned long)"ui_even_ai_task") /*=0xa98ce*/)
#define LOG_INIT               ((uintptr_t)((unsigned long)"%s(): ENTER evenai INIT process...\n") /*=0xa9855*/)
#define LOG_SYNC_REFRESH       ((uintptr_t)((unsigned long)"%s(): SYNC_AREA_REFALSH Upgrade ....\n") /*=0xa9879*/)
#define LOG_EXIT               ((uintptr_t)((unsigned long)"%s(): evenai process received exit packet ...\n") /*=0xa989f*/)

ALWAYS_INLINE uint8_t field8(uintptr_t device, unsigned offset)
{
    return *(volatile uint8_t *)(device + offset);
}

ALWAYS_INLINE uint16_t field16(uintptr_t device, unsigned offset)
{
    return *(volatile uint16_t *)(device + offset);
}

ALWAYS_INLINE uintptr_t field32(uintptr_t device, unsigned offset)
{
    return *(volatile uint32_t *)(device + offset);
}

ALWAYS_INLINE void log_event(uintptr_t format, int threshold)
{
    if (G_LOG_LEVEL > threshold) {
        if (G_LOGGER_MODE == 0)
            log_message(format, LOG_FUNCTION, -1, 0);
        else
            debug_print(format, LOG_FUNCTION, -1, 1);
    }
}

ALWAYS_INLINE void refresh_region(int x, int y, int width, int height)
{
    uintptr_t left = field32(get_device_info(), 0xeb4);
    uintptr_t right = field32(get_device_info(), 0xeb8);
    reflash_fb_data_to_lcd(left, right, x, y, width, height);
}

ALWAYS_INLINE void mask_full_canvas(uint32_t *rows, unsigned frame)
{
    const unsigned mask_frame = MASK_FRAME_SEQUENCE[frame];
    for (unsigned y = 0; y != 199; ++y) {
        uint8_t *row = (uint8_t *)(uintptr_t)rows[y];
        const uint8_t *mask = MASK_BITMAP_BASE + (y % 26u) * 0xa00u
                            + mask_frame * 0x140u;
        for (unsigned x = 0; x != 0x140; ++x)
            if (row[x] != 0)
                row[x] &= mask[x];
    }
}

ALWAYS_INLINE void draw_detail_text(uintptr_t text, int lines)
{
    int left = gui_text_left();
    int top = gui_text_top();
    int right = gui_text_left();
    int bottom = gui_text_top();
    gui_utf_draw(0, text, 0, left + 0x58, top + (lines == 3 ? 0x36 : 0),
                 right + (lines == 3 ? 0x230 : 0x240),
                 bottom + (lines == 3 ? 0x87 : 0x88), lines, 0, 0, 0, 0);
}

ALWAYS_INLINE void draw_primary_centered(uintptr_t text)
{
    int left = gui_text_left();
    int top = gui_text_top();
    int right = gui_text_left();
    int bottom = gui_text_top();
    gui_utf_draw_middle(0, text, 0, left, top + 0x36,
                        right + 0x236, bottom + 0x87, 3, 0, 0, 0, 0);
}

ALWAYS_INLINE void draw_status_11(uintptr_t detail)
{
    int left = gui_text_left();
    int top = gui_text_top();
    gui_bmp_bitmap_draw(0x49, left, top + 0x36, 0, 0, 0);
    draw_detail_text(detail, 3);
}

ALWAYS_INLINE void copy_and_draw_device_text(uintptr_t device)
{
    memcpy_s(G_LINE_TEXT, (const void *)(device + 0xf6), field16(device, 0x286), 400);
    draw_detail_text((uintptr_t)G_LINE_TEXT, 5);
}

ALWAYS_INLINE void draw_status_16_text(uintptr_t device)
{
    memcpy_s(G_LINE_TEXT, (const void *)(device + 0xf6), field16(device, 0x286), 400);
    int left = gui_text_left();
    int top = gui_text_top();
    int right = gui_text_left();
    int bottom = gui_text_top();
    gui_utf_draw(0, (uintptr_t)G_LINE_TEXT, 0, left, top,
                 right + 0x240, bottom + 0x88, 5, 0, 0, 0, 0);
}

ALWAYS_INLINE void draw_progress_if_visible(uintptr_t device)
{
    if (field8(device, 0xf4) != 1) {
        int left = gui_text_left();
        int top = gui_text_top();
        int right = gui_text_left();
        int bottom = gui_text_top();
        gui_verticalLine_process_bar(left + 0x23c, top, right + 0x23c,
                                     bottom + 0x88, 1,
                                     field8(device, 0xf3), 0);
    }
}

ALWAYS_INLINE uintptr_t render_static_status(uintptr_t device, unsigned status,
                                      uintptr_t primary, uintptr_t detail,
                                      uintptr_t prior_result)
{
    if (status < 6) {
        draw_primary_centered(primary);
    } else if (status == 11) {
        draw_status_11(detail);
    } else if (status >= 12 && status < 15) {
        if (status != 14)
            return prior_result;
        refresh_region(0, 0, 0x27f, 199);
    } else if (status >= 15 && status < 17) {
        if (status != 16)
            return prior_result;
        copy_and_draw_device_text(device);
    } else {
        draw_primary_centered(primary);
    }
    return 0;
}

ALWAYS_INLINE void reset_render_state(void)
{
    gui_text_metrics_reset();
    *(volatile uint16_t *)G_ACTIVE = 0;
    G_RENDER_STATE[2] = 0;
    G_RENDER_STATE[3] = 0;
    G_RENDER_STATE[5] = 0;
    G_RENDER_STATE[6] = 0;
    G_RENDER_STATE[1] = 0;
    G_RENDER_STATE[4] = 0;
}

ALWAYS_INLINE void mask_transition_half(uintptr_t device, unsigned mask_offset)
{
    /* The original deliberately re-reads the live text bounds in both loop
     * conditions; retain those calls because another UI task may update the
     * metrics while this transition is in progress. */
    for (int y = gui_text_top(); y <= gui_text_top() + 0x87; ++y) {
        uint8_t *row = (uint8_t *)(uintptr_t)field32(device, 0xb90 + y * 4);
        const uint8_t *mask = MASK_BITMAP_BASE + mask_offset + (y % 26) * 0xa00;
        for (int x = gui_text_left() + 0x58;
             x < (gui_text_left() + 0x230) / 2; ++x)
            if (row[x] != 0)
                row[x] &= mask[x];
    }
}

ALWAYS_INLINE void refresh_text_bounds(void)
{
    uintptr_t left_fb = field32(get_device_info(), 0xeb4);
    uintptr_t right_fb = field32(get_device_info(), 0xeb8);
    int left = gui_text_left();
    int top = gui_text_top();
    int right = gui_text_left();
    int bottom = gui_text_top();
    reflash_fb_data_to_lcd(left_fb, right_fb, left + 0x58, top,
                           right + 0x230, bottom + 0x88);
}

ALWAYS_INLINE void mask_text_region_frames(uintptr_t device,
                                           int *published_x,
                                           int *published_y)
{
    for (unsigned frame = 0; frame != 8; ++frame) {
        int first_x = gui_text_left() + 0x58;
        int last_x = gui_text_left();
        int first_y = gui_text_top();
        int last_y = gui_text_top();
        int height = (last_y + 0x88) - first_y;
        int width = ((last_x + 0x230) - first_x) / 2;
        *published_x = first_x;
        *published_y = first_y;
        for (int dy = 0; dy < height; ++dy) {
            uint8_t *row = (uint8_t *)(uintptr_t)
                field32(device, 0xb90 + (first_y + dy) * 4);
            const uint8_t *mask = MASK_BITMAP_BASE + (dy % 26) * 0xa00
                                + MASK_FRAME_SEQUENCE[frame] * 0x140;
            for (int dx = 0; dx < width; ++dx) {
                int x = first_x / 2 + dx;
                if (row[x] != 0)
                    row[x] &= mask[dx];
            }
        }
        refresh_region(first_x, first_y, last_x + 0x230, last_y + 0x88);
    }
}

uintptr_t ui_even_ai_task(uint32_t *canvas, uintptr_t unused, int phase)
{
    (void)unused;
    uintptr_t device = get_device_info();
    uint32_t *canvas_rows = (uint32_t *)((uintptr_t)canvas + 0x24);
    unsigned language = (unsigned)(ui_language_get() - 1) & 0xffu;
    unsigned status = field8(device, 0xef);
    if (status != 7)
        G_SAVED_PAGE = -1;

    uintptr_t primary = 0;
    uintptr_t detail = 0;
    if (language < 14) {
        primary = LANGUAGE_PRIMARY_TABLE[language];
        detail = LANGUAGE_DETAIL_TABLE[language];
    }

    gui_set_active_canvas((uintptr_t)canvas_rows);
    gui_canvas_flags_set_bit1();

    if (G_ACTIVE[0] == 0) {
        if (phase == 1) {
            memset_bytes(G_LINE_TEXT, 0, 400);
            log_event(LOG_INIT, 0);
            if (G_ACTIVE[1] != 0)
                return 0;
            log_event(LOG_SYNC_REFRESH, 0);
            gui_text_metrics_reset();
            if (field8(device, 0xef) < 12)
                gui_screen_clear();
            G_FRAME_INDEX = 0;
            gui_reset_render_offsets();
            G_RENDER_STATE[7] = 0x80;
            G_RENDER_STATE[2] = 0;
            G_RENDER_STATE[3] = 0;
            G_RENDER_STATE[0] = RENDER_STATE_INITIAL;
            G_RENDER_STATE[5] = 0;
            G_RENDER_STATE[6] = 0;
            G_RENDER_STATE[1] = 0;
            G_RENDER_STATE[4] = 0;
            G_ACTIVE[1] = 1;
            G_ACTIVE[0] = 1;
            gui_reset_dynamic_bitmap_state();
            uintptr_t result = gui_canvas_flags_clear_bit1();
            for (unsigned frame = 0; frame != 8; ++frame) {
                status = field8(device, 0xef);
                if ((status >= 12 && status < 15 && status != 14) ||
                    (status >= 15 && status < 17 && status != 16))
                    return result;
                if (status == 11)
                    draw_status_11(detail);
                else if (status == 14) {
                    refresh_region(0, 0, 0x27f, 199);
                    break;
                } else if (status == 16)
                    draw_status_16_text(device);
                else
                    draw_primary_centered(primary);
                mask_full_canvas(canvas_rows, frame);
                refresh_region(0, 0, 0x280, 199);
            }
            gui_canvas_flags_set_bit1();
            return 0;
        }
        if (phase != 2)
            return 0;
        log_event(LOG_EXIT, 2);
        gui_screen_clear();
        reset_render_state();
        return 0;
    }

    if (G_ACTIVE[0] != 1)
        return 0;
    if (phase == 0) {
        even_ai_status_icon_render((void *)(device + 0xef), 1, -1,
                                   (void *)(device + 0xef));
        return 0;
    }
    if (phase == 2) {
        log_event(LOG_EXIT, 2);
        even_ai_exit_animation();
        reset_render_state();
        return 0;
    }
    if (phase != 1)
        return 0;

    memset_bytes(G_LINE_TEXT, 0, 400);
    k_mutex_lock_forever(G_UI_MUTEX, -1);
    uint8_t substate = field8(device, 0xf0);
    uintptr_t result = k_mutex_unlock(G_UI_MUTEX);
    status = field8(device, 0xef);

    if (status == 7 && G_SAVED_PAGE == -1 && substate == 3) {
        G_SAVED_PAGE = field8(device, 0xf5);
        gui_canvas_flags_clear_bit1();
        for (unsigned frame = 0; frame != 8; ++frame) {
            copy_and_draw_device_text(device);
            draw_progress_if_visible(device);
            mask_full_canvas(canvas_rows, frame);
            refresh_region(0, 0, 0x280, 199);
        }
        gui_canvas_flags_set_bit1();
        return 0;
    }

    if (substate == 4) {
        G_SAVED_PAGE = field8(device, 0xf5);
        uintptr_t display = get_device_info();
        mask_transition_half(display, 0x640);
        refresh_text_bounds();
        mask_transition_half(display, 0x500);
        refresh_text_bounds();
        clean_fb_data(display + 0xb90, 0, 0, 0x10, 0x280, 0xb8);
        even_ai_status_icon_render((void *)(device + 0xef));
        result = gui_canvas_flags_clear_bit1();
        status = field8(device, 0xef);
        if ((status >= 12 && status < 15 && status != 14) ||
            (status >= 15 && status < 17 && status != 16))
            return result;
        if (status < 6)
            draw_primary_centered(primary);
        else if (status == 11)
            draw_status_11(detail);
        else if (status == 14)
            refresh_region(0, 0, 0x27f, 199);
        else if (status == 16)
            draw_status_16_text(device);
        else {
            copy_and_draw_device_text(device);
            draw_progress_if_visible(device);
        }
        int published_x = 0;
        int published_y = 0;
        mask_text_region_frames(display, &published_x, &published_y);
        result = gui_canvas_flags_set_bit1();
        /* The original one-formal call leaves the flag result and final LCD
         * x/y live in r1-r3.  Spell them out so differential call tracing is
         * codegen-independent while the callee continues to use only r0. */
        even_ai_status_icon_render((void *)(device + 0xef), result,
                                   published_x, published_y);
        G_FRAME_INDEX = 1;
        return 0;
    }

    if (status < 5) {
        if (G_FRAME_INDEX != 0) {
            G_FRAME_INDEX = 0;
            gui_screen_clear();
        }
        draw_primary_centered(primary);
        return 0;
    }
    if (status == 11) {
        if (G_FRAME_INDEX != 0) {
            G_FRAME_INDEX = 0;
            gui_screen_clear();
        }
        draw_status_11(detail);
        return 0;
    }
    if (status >= 12 && status < 15) {
        if (status == 14) {
            refresh_region(0, 0, 0x27f, 199);
            return 0;
        }
        return result;
    }
    if (status >= 15 && status < 17) {
        if (status == 16) {
            draw_status_16_text(device);
            return 0;
        }
        return result;
    }
    if (status < 7) {
        int left = gui_text_left();
        int top = gui_text_top();
        int right = gui_text_left();
        int bottom = gui_text_top();
        gui_utf_draw(0, SPACE_TEXT, 0, left + 0x58, top + 0x36,
                     right + 0x230, bottom + 0x87, 5, 0, 0, 0, 0);
        G_FRAME_INDEX = 1;
        G_TEXT_RENDERED = 0;
        return 0;
    }

    memset_bytes(G_LINE_TEXT, 0, 400);
    memcpy_s(G_LINE_TEXT, (const void *)(device + 0xf6),
             field16(device, 0x286), 400);
    if ((status >= 8 && status < 10) || G_TEXT_RENDERED == 0) {
        draw_detail_text((uintptr_t)G_LINE_TEXT, 5);
        if (G_TEXT_RENDERED == 0)
            G_TEXT_RENDERED = 1;
    } else {
        int left = gui_text_left();
        int top = gui_text_top();
        int right = gui_text_left();
        int bottom = gui_text_top();
        gui_utf_draw_scrolling(0, (uintptr_t)G_LINE_TEXT, 0,
                               left + 0x58, top + 1,
                               right + 0x230, bottom + 0x88, 5, 0);
    }
    draw_progress_if_visible(device);
    G_FRAME_INDEX = 1;
    return 0;
}
