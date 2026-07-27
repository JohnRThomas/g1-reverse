#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0003b824 @ 0x0003b824
 * public-name: ui_QuickNote_task
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_ui_mode_flag_byte1                   <= FUN_00023ee0 @ 0x00023ee0
 *   gui_screen_fade_out_transition           <= FUN_0004382c @ 0x0004382c
 * address symbols (name @ address):
 *   rodata_a8c57                             @ 0x000a8c57
 *   rodata_a960d                             @ 0x000a960d   [INLINED -- G6 literal batch]
 *   rodata_a9629                             @ 0x000a9629   [INLINED -- G6 literal batch]
 *   rodata_a9654                             @ 0x000a9654   [INLINED -- G6 literal batch]
 *   rodata_a9679                             @ 0x000a9679   [INLINED -- G6 literal batch]
 *   rodata_a9690                             @ 0x000a9690   [INLINED -- G6 literal batch]
 *   rodata_a96ac                             @ 0x000a96ac   [INLINED -- G6 literal batch]
 *   rodata_a96c8                             @ 0x000a96c8   [INLINED -- G6 literal batch]
 *   rodata_a96e0                             @ 0x000a96e0   [INLINED -- G6 literal batch]
 *   rodata_a9709                             @ 0x000a9709   [INLINED -- G6 literal batch]
 *   rodata_a9727                             @ 0x000a9727   [INLINED -- G6 literal batch]
 *   rodata_a974b                             @ 0x000a974b   [INLINED -- G6 literal batch]
 *   rodata_a9775                             @ 0x000a9775   [INLINED -- G6 literal batch]
 *   rodata_a9797                             @ 0x000a9797   [INLINED -- G6 literal batch]
 *   rodata_a97bb                             @ 0x000a97bb   [INLINED -- G6 literal batch]
 *   rodata_a97e4                             @ 0x000a97e4   [INLINED -- G6 literal batch]
 *   rodata_a980b                             @ 0x000a980b   [INLINED -- G6 literal batch]
 *   rodata_a981a                             @ 0x000a981a   [INLINED -- G6 literal batch]
 *   rodata_a9831                             @ 0x000a9831   [INLINED -- G6 literal batch]
 *   rodata_aae20                             @ 0x000aae20
 *   g_log_level                              @ 0x2000230c
 *   g_quicknote_warn_offset_ms               @ 0x200024e8
 *   g_quicknote_info                         @ 0x20004978
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_quicknote_hint_shown                   @ 0x2001b817
 */
/* Reconstructed ui_QuickNote_task @ 0x3b824 (raw: FUN_0003b824). */
#include <stdint.h>
#include "../../headers/g1_log.h"

/* Callee provenance (readable name <- raw identity @ address):
 *   get_device_info                       <- FUN_000167a8 @ 0x000167a8
 *   debug_print                           <- FUN_00019c70 @ 0x00019c70
 *   ui_language_get                       <- FUN_00023ee0 @ 0x00023ee0
 *   dmic_record_start                     <- FUN_0003b78c @ 0x0003b78c
 *   consume_pending_event_and_refresh_flag<- FUN_0003b800 @ 0x0003b800
 *   gui_set_active_canvas                 <- FUN_000431b4 @ 0x000431b4
 *   gui_screen_clear                      <- FUN_000431c0 @ 0x000431c0
 *   gui_canvas_flags_set_bit1             <- FUN_000432d0 @ 0x000432d0
 *   gui_canvas_flags_clear_bit1           <- FUN_000432ec @ 0x000432ec
 *   gui_reset_dynamic_bitmap_frame_state  <- FUN_00043308 @ 0x00043308
 *   gui_bmp_dynamic_bitmap_draw           <- FUN_0004334c @ 0x0004334c
 *   gui_bmp_bitmap_draw                   <- FUN_00043484 @ 0x00043484
 *   quicknote_exit_animation              <- FUN_0004382c @ 0x0004382c
 *   gui_utf_draw                          <- FUN_00043e90 @ 0x00043e90
 *   reflash_fb_data_to_lcd                <- FUN_00047260 @ 0x00047260
 *   getDelayExitValue                     <- FUN_00049040 @ 0x00049040
 *   device_info_text_width_get            <- FUN_0007d3ee @ 0x0007d3ee
 *   device_info_text_height_get_clamped   <- FUN_0007d446 @ 0x0007d446
 *   uptime_ticks_get                      <- FUN_00086698 @ 0x00086698
 *   memset_bytes                          <- FUN_00086c78 @ 0x00086c78
 *   DEBUG_PRINT                                               @ 0x0007dda4
 */
extern int get_device_info(void);
extern int get_ui_mode_flag_byte1(void);
extern void dmic_record_start(void);
extern void consume_pending_event_and_refresh_flag(void);
extern unsigned int gui_set_active_canvas(unsigned int);
extern void gui_screen_clear(void);
extern void gui_canvas_flags_set_bit1(void);
extern void gui_canvas_flags_clear_bit1(void);
extern unsigned int gui_reset_dynamic_bitmap_frame_state(void);
extern void gui_bmp_dynamic_bitmap_draw(unsigned int bitmap_id,
                                        int x, int y,
                                        int arg3, int arg4,
                                        int arg5, int arg6);
extern int gui_bmp_bitmap_draw(unsigned int, int, int, int, int, int);
extern void gui_screen_fade_out_transition(void);
extern void gui_utf_draw(int background, uintptr_t text, int style,
                         int x, int y, int right, int bottom,
                         int line_count, int arg8, int arg9,
                         int arg10, int arg11);
extern void reflash_fb_data_to_lcd(uintptr_t left_framebuffer,
                                   uintptr_t right_framebuffer,
                                   int x, int y, int width, int height);
extern unsigned long getDelayExitValue(void);
extern int device_info_text_width_get(void);
extern int device_info_text_height_get_clamped(void);
extern uint64_t uptime_ticks_get(void); /* FUN_00086698 @ 0x00086698 */
extern void memset_bytes(void*, int, int);

#define ui_language_get          get_ui_mode_flag_byte1
#define quicknote_exit_animation gui_screen_fade_out_transition
#define g_log_level              (*(volatile int32_t *)((unsigned long)&g_log_level) /*=0x2000230c*/)
#define g_quicknote_warn_offset_ms (*(volatile int32_t *)((unsigned long)&g_quicknote_warn_offset_ms) /*=0x200024e8*/)
#define g_quicknote_hint_shown   (*(volatile uint8_t *)((unsigned long)&g_quicknote_hint_shown) /*=0x2001b817*/)

#define LOG_FUNCTION             ((uintptr_t)((unsigned long)"ui_QuickNote_task") /*=0xa9831*/)
#define LOG_INIT                 ((uintptr_t)((unsigned long)"%s(): QUICK NOTE INIT.....\n") /*=0xa960d*/)
#define LOG_ENABLE               ((uintptr_t)((unsigned long)"%s(): GLOBAL->quicknote_info->enable = %d\n") /*=0xa9629*/)
#define LOG_START                ((uintptr_t)((unsigned long)"%s(): quick note function start ...\n") /*=0xa9654*/)
#define LOG_INIT_EXIT            ((uintptr_t)((unsigned long)"%s(): quick init,exec function exit ...\n") /*=0xa96e0*/)
#define LOG_RUNNING              ((uintptr_t)((unsigned long)"%s(): QUICK NOTE RUNING.....\n") /*=0xa9709*/)
#define LOG_FUNCTION_EXIT        ((uintptr_t)((unsigned long)"%s(): quick note function exit ...\n") /*=0xa9727*/)
#define LOG_DELAY_EXIT           ((uintptr_t)((unsigned long)"%s(): quick note function delay exit ...\n") /*=0xa974b*/)
#define LOG_LOGO_REFRESH         ((uintptr_t)((unsigned long)"%s(): exec even logo reflash....\n") /*=0xa9775*/)
#define LOG_PROCESS              ((uintptr_t)((unsigned long)"%s(): quick note process exec.....\n") /*=0xa9797*/)
#define LOG_TIMEOUT_EXIT         ((uintptr_t)((unsigned long)"%s(): quick note function exit -164 ...\n") /*=0xa97bb*/)
#define LOG_EXIT_DISPLAY         ((uintptr_t)((unsigned long)"%s(): exec quick note exit display...\n") /*=0xa97e4*/)

#define TEXT_RECORDING_EN        ((uintptr_t)((unsigned long)"QuickNote recording...") /*=0xa9679*/)
#define TEXT_RELEASE_EN          ((uintptr_t)((unsigned long)"Release to Finish Recording") /*=0xa9690*/)
#define TEXT_RECORDING_DE        ((uintptr_t)((unsigned long)"Kurznotizen-Aufzeichnung...") /*=0xa96ac*/)
#define TEXT_RELEASE_DE          ((uintptr_t)((unsigned long)"Loslassen zum Abschluss") /*=0xa96c8*/)
#define TEXT_SAVED_EN            ((uintptr_t)((unsigned long)"New Note Saved") /*=0xa980b*/)
#define TEXT_SAVED_DE            ((uintptr_t)((unsigned long)"Neue Notiz gespeichert") /*=0xa981a*/)

#define QUICKNOTE_STATE_ADDRESS  ((uintptr_t)((unsigned long)&g_quicknote_info) /*=0x20004978*/)
#define QUICKNOTE_MASK_FRAMES    ((const uint8_t *)((unsigned long)&rodata_a8c57) /*=0xa8c57*/)
#define QUICKNOTE_MASK_BITMAP    ((const uint8_t *)((unsigned long)&rodata_aae20) /*=0xaae20*/)

enum quicknote_phase {
    QUICKNOTE_PHASE_IDLE = 0,
    QUICKNOTE_PHASE_RENDER = 1,
    QUICKNOTE_PHASE_EXIT = 2,
    QUICKNOTE_PHASE_RELEASE = 3,
};

enum quicknote_screen_state {
    QUICKNOTE_SCREEN_INIT = 0,
    QUICKNOTE_SCREEN_RECORDING = 1,
    QUICKNOTE_SCREEN_REVIEW = 2,
};

struct quicknote_ui_state {
    uint8_t screen;
    uint8_t reserved_01[3];
    int32_t delay_ms;
    uint64_t started_ms;
};

struct quicknote_runtime {
    volatile uint8_t enable;
};

/* Named view of only the device-info fields consumed by this state machine. */
struct quicknote_device_view {
    uint8_t device_type;                         /* +0x000 */
    uint8_t reserved_0001[0xeb3];
    uintptr_t left_framebuffer;                  /* +0xeb4 */
    uintptr_t right_framebuffer;                 /* +0xeb8 */
    uint8_t reserved_0ebc[0x164];
    struct quicknote_runtime *quicknote;          /* +0x1020 */
};

struct quicknote_canvas {
    uint8_t reserved_00[0x24];
    uint8_t *rows[199];
};

static inline __attribute__((always_inline))
struct quicknote_ui_state *quicknote_state(void)
{
    return (struct quicknote_ui_state *)QUICKNOTE_STATE_ADDRESS;
}

static inline __attribute__((always_inline))
const struct quicknote_device_view *device_state(void)
{
    return (const struct quicknote_device_view *)get_device_info();
}

static inline __attribute__((always_inline))
struct quicknote_runtime *quicknote_runtime_state(void)
{
    return device_state()->quicknote;
}

static inline __attribute__((always_inline))
void quicknote_log(uintptr_t format)
{
    if (*(volatile int32_t *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
        log_message(format, LOG_FUNCTION);
    } else {
        debug_print(format, LOG_FUNCTION);
    }
}

static inline __attribute__((always_inline))
void quicknote_log_value(uintptr_t format, unsigned int value)
{
    if (*(volatile int32_t *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
        log_message(format, LOG_FUNCTION, value);
    } else {
        debug_print(format, LOG_FUNCTION, value);
    }
}

static inline __attribute__((always_inline))
uint64_t quicknote_uptime_ms(void)
{
    return (uptime_ticks_get() * UINT64_C(1000)) >> 15;
}

static inline __attribute__((always_inline))
void draw_dynamic_bitmap(unsigned int bitmap_id)
{
    int x = device_info_text_width_get();
    int y = device_info_text_height_get_clamped();
    gui_bmp_dynamic_bitmap_draw(bitmap_id, x, y + 0x36, 0, 0, 0, 0);
}

static inline __attribute__((always_inline))
void draw_recording_line(uintptr_t text, int x_offset, int y_offset,
                         int bottom_offset)
{
    int x = device_info_text_width_get();
    int y = device_info_text_height_get_clamped();
    int right = device_info_text_width_get();
    int bottom = device_info_text_height_get_clamped();
    gui_utf_draw(0, text, 0, x + x_offset, y + y_offset,
                 right + 0x236, bottom + bottom_offset,
                 1, 0, 0, 0, 0);
}

static inline __attribute__((always_inline))
void draw_recording_screen(struct quicknote_canvas *canvas,
                           unsigned int language)
{
    gui_canvas_flags_clear_bit1();
    for (unsigned int frame = 0; frame != 4; ++frame) {
        if (language == 6) {
            draw_recording_line(TEXT_RECORDING_DE, 0xa0, 0x36, 0x51);
            draw_recording_line(TEXT_RELEASE_DE, 0xaa, 0x6c, 0x87);
        } else {
            draw_recording_line(TEXT_RECORDING_EN, 0xbc, 0x36, 0x51);
            draw_recording_line(TEXT_RELEASE_EN, 0xa4, 0x6c, 0x87);
        }

        unsigned int mask_frame = QUICKNOTE_MASK_FRAMES[frame];
        for (unsigned int row = 0; row != 199; ++row) {
            uint8_t *destination = canvas->rows[row];
            const uint8_t *mask = QUICKNOTE_MASK_BITMAP +
                (row % 26u) * 0xa00u + mask_frame * 0x140u;
            for (unsigned int column = 0; column != 0x140; ++column) {
                if (destination[column] != 0) {
                    destination[column] &= mask[column];
                }
            }
        }

        uintptr_t left = device_state()->left_framebuffer;
        uintptr_t right = device_state()->right_framebuffer;
        reflash_fb_data_to_lcd(left, right, 0, 0, 0x280, 199);
    }
    gui_canvas_flags_set_bit1();
}

static inline __attribute__((always_inline))
void disable_quicknote(void)
{
    quicknote_runtime_state()->enable = 0;
    memset_bytes(quicknote_state(), 0, sizeof(struct quicknote_ui_state));
}

static inline __attribute__((always_inline))
void leave_quicknote_screen(void)
{
    if (device_state()->device_type == 1) {
        consume_pending_event_and_refresh_flag();
    }
    gui_screen_clear();
    disable_quicknote();
}

static inline __attribute__((always_inline))
void draw_saved_note_message(void)
{
    gui_screen_clear();

    int icon_x = device_info_text_width_get();
    int icon_y = device_info_text_height_get_clamped();
    gui_bmp_bitmap_draw(0x3b, icon_x, icon_y + 0x36, 0, 0, 0);

    unsigned int language = ui_language_get();
    uintptr_t text = language == 6 ? TEXT_SAVED_DE : TEXT_SAVED_EN;
    int x_offset = language == 6 ? 0xb8 : 0xd6;
    int x = device_info_text_width_get();
    int y = device_info_text_height_get_clamped();
    int right = device_info_text_width_get();
    int bottom = device_info_text_height_get_clamped();
    gui_utf_draw(0, text, 0, x + x_offset, y + 0x36,
                 right + 0x236, bottom + 0x6c,
                 2, 0, 0, 0, 0);
    g_quicknote_hint_shown = 1;
}

uint32_t ui_QuickNote_task(struct quicknote_canvas *canvas,
                           uint32_t unused, int phase)
{
    (void)unused;
    struct quicknote_ui_state *state = quicknote_state();

    gui_set_active_canvas(canvas->rows);
    gui_canvas_flags_set_bit1();

    switch (state->screen) {
    case QUICKNOTE_SCREEN_INIT:
        if (g_log_level > 2) {
            quicknote_log(LOG_INIT);
        }
        memset_bytes(state, 0, sizeof(*state));
        if (g_log_level > 2) {
            quicknote_log_value(LOG_ENABLE, quicknote_runtime_state()->enable);
        }

        if (phase == QUICKNOTE_PHASE_RENDER) {
            if (quicknote_runtime_state()->enable != 1) {
                return 0;
            }
            if (g_log_level > 2) {
                quicknote_log(LOG_START);
            }
            gui_screen_clear();
            state->screen = QUICKNOTE_SCREEN_RECORDING;
            gui_reset_dynamic_bitmap_frame_state();
            unsigned int language = ui_language_get();
            draw_recording_screen(canvas, language);
            if (device_state()->device_type == 1) {
                dmic_record_start();
            }
            return 0;
        }

        if (phase == QUICKNOTE_PHASE_EXIT) {
            if (g_log_level > 0) {
                quicknote_log(LOG_INIT_EXIT);
            }
            leave_quicknote_screen();
        }
        return 0;

    case QUICKNOTE_SCREEN_RECORDING:
        if (g_log_level > 2) {
            quicknote_log(LOG_RUNNING);
        }
        if (phase == QUICKNOTE_PHASE_EXIT) {
            if (g_log_level > 2) {
                quicknote_log(LOG_FUNCTION_EXIT);
            }
            leave_quicknote_screen();
            return 0;
        }
        if (phase == QUICKNOTE_PHASE_RELEASE) {
            if (g_log_level > 2) {
                quicknote_log(LOG_DELAY_EXIT);
            }
            if (device_state()->device_type == 1) {
                consume_pending_event_and_refresh_flag();
            }
            state->delay_ms = getDelayExitValue();
            state->started_ms = quicknote_uptime_ms();
            gui_screen_clear();
            state->screen = QUICKNOTE_SCREEN_REVIEW;
            g_quicknote_hint_shown = 0;
            gui_reset_dynamic_bitmap_frame_state();
            if (g_log_level > 2) {
                quicknote_log(LOG_LOGO_REFRESH);
            }
            return 0;
        }
        if (phase == QUICKNOTE_PHASE_IDLE) {
            draw_dynamic_bitmap(1);
        }
        return 0;

    case QUICKNOTE_SCREEN_REVIEW: {
        if (g_log_level > 2) {
            quicknote_log(LOG_PROCESS);
        }
        if (phase == QUICKNOTE_PHASE_EXIT) {
            if (g_log_level > 2) {
                quicknote_log(LOG_FUNCTION_EXIT);
            }
            if (device_state()->device_type == 1) {
                consume_pending_event_and_refresh_flag();
            }
            quicknote_exit_animation();
            disable_quicknote();
            return 0;
        }

        uint64_t now_ms = quicknote_uptime_ms();
        uint64_t deadline_ms = state->started_ms +
            (uint64_t)(int64_t)state->delay_ms;
        if ((int64_t)deadline_ms < (int64_t)now_ms) {
            if (g_log_level > 2) {
                quicknote_log(LOG_TIMEOUT_EXIT);
            }
            quicknote_exit_animation();
            disable_quicknote();
            g_quicknote_hint_shown = 0;
            return 0;
        }

        uint64_t warning_ms = deadline_ms -
            (uint64_t)(int64_t)g_quicknote_warn_offset_ms;
        if ((int64_t)warning_ms >= (int64_t)now_ms) {
            if (g_quicknote_hint_shown == 0) {
                draw_dynamic_bitmap(9);
            }
            return 0;
        }

        if (g_quicknote_hint_shown != 0) {
            return 0;
        }
        if (g_log_level > 2) {
            quicknote_log(LOG_EXIT_DISPLAY);
        }
        draw_saved_note_message();
        return 0;
    }

    default:
        return 0;
    }
}
