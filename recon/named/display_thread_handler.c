/* readable reconstruction; identity: FUN_00049090 @ 0x00049090
 * public-name: display_thread_handler
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   __aeabi_uldivmod                         <= FUN_0000e244 @ 0x0000e244
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   gui_set_active_canvas                    <= FUN_000431b4 @ 0x000431b4
 *   display_reflash_handler                  <= FUN_00048e28 @ 0x00048e28
 *   stop_some_timer                          <= FUN_00048ff4 @ 0x00048ff4
 *   setDelayExitValue                        <= FUN_00049000 @ 0x00049000
 *   wake_display_thread_on_reflash           <= FUN_0004906c @ 0x0004906c
 *   k_msgq_get                               <= FUN_00072240 @ 0x00072240
 *   k_sleep                                  <= FUN_00074844 @ 0x00074844
 *   projector_fill_and_sync                  <= FUN_0007d6f4 @ 0x0007d6f4
 *   log_message                              <= FUN_0007dda4 @ 0x0007dda4
 *   k_timer_init                             <= FUN_00086726 @ 0x00086726
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_28000                             @ 0x00028000
 *   rodata_7d86d                             @ 0x0007d86d
 *   rodata_efb2e                             @ 0x000efb2e   [INLINED -- G6 literal batch]
 *   rodata_efb50                             @ 0x000efb50   [INLINED -- G6 literal batch]
 *   rodata_efb7a                             @ 0x000efb7a   [INLINED -- G6 literal batch]
 *   rodata_efb9f                             @ 0x000efb9f   [INLINED -- G6 literal batch]
 *   rodata_efbb7                             @ 0x000efbb7   [INLINED -- G6 literal batch]
 *   rodata_efbe5                             @ 0x000efbe5   [INLINED -- G6 literal batch]
 *   rodata_efc00                             @ 0x000efc00   [INLINED -- G6 literal batch]
 *   rodata_efc2d                             @ 0x000efc2d   [INLINED -- G6 literal batch]
 *   rodata_efc62                             @ 0x000efc62   [INLINED -- G6 literal batch]
 *   rodata_efc92                             @ 0x000efc92   [INLINED -- G6 literal batch]
 *   rodata_efcdf                             @ 0x000efcdf   [INLINED -- G6 literal batch]
 *   rodata_efd03                             @ 0x000efd03   [INLINED -- G6 literal batch]
 *   rodata_efd2d                             @ 0x000efd2d   [INLINED -- G6 literal batch]
 *   rodata_efd6f                             @ 0x000efd6f   [INLINED -- G6 literal batch]
 *   rodata_efe74                             @ 0x000efe74   [INLINED -- G6 literal batch]
 *   rodata_efebc                             @ 0x000efebc   [INLINED -- G6 literal batch]
 *   rodata_eff70                             @ 0x000eff70   [INLINED -- G6 literal batch]
 *   rodata_effaf                             @ 0x000effaf   [INLINED -- G6 literal batch]
 *   rodata_f01aa                             @ 0x000f01aa   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_dashboard_display_level                @ 0x20002544
 *   g_display_msgq                           @ 0x200038c4
 *   g_some_k_timer                           @ 0x20004ce0
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_2001d447                               @ 0x2001d447
 */
/* Reconstructed display_thread_handler @ 0x00049090.
 *
 * Readable identity/back-map:
 *   log_message                         <= FUN_0007dda4 @ 0x0007dda4
 *   debug_print                         <= FUN_00019c70 @ 0x00019c70
 *   unsigned_divide_64                  <= FUN_0000e244 @ 0x0000e244
 *   get_device_info                     <= FUN_000167a8 @ 0x000167a8
 *   gui_set_active_canvas               <= FUN_000431b4 @ 0x000431b4
 *   display_reflash_handler             <= FUN_00048e28 @ 0x00048e28
 *   display_timer_stop                  <= FUN_00048ff4 @ 0x00048ff4
 *   display_delay_set                   <= FUN_00049000 @ 0x00049000
 *   display_thread_service_abort        <= FUN_0004906c @ 0x0004906c
 *   k_msgq_get                          <= FUN_00072240 @ 0x00072240
 *   k_sleep_ticks                       <= FUN_00074844 @ 0x00074844
 *   display_power_set                   <= FUN_0007d6f4 @ 0x0007d6f4
 *   k_timer_init                        <= FUN_00086726 @ 0x00086726
 *   memset_bytes                        <= FUN_00086c78 @ 0x00086c78
 *
 * Exact executable ownership is [0x00049090, 0x00049632).  The halfword at
 * 0x49632 is alignment, 0x49634 is the final literal, and FUN_00049638 is the
 * next independent function.
 */

#include <stdbool.h>
#include <stdint.h>

#define log_message                  log_message
#define debug_print                  debug_print
#define unsigned_divide_64           __aeabi_uldivmod
#define get_device_info              get_device_info
#define gui_set_active_canvas        gui_set_active_canvas
#define display_reflash_handler      display_reflash_handler
#define display_timer_stop           stop_some_timer
#define display_delay_set            setDelayExitValue
#define display_thread_service_abort wake_display_thread_on_reflash
#define k_msgq_get                    k_msgq_get
#define k_sleep_ticks                 k_sleep
#define display_power_set            projector_fill_and_sync
#define k_timer_init                  k_timer_init
#define memset_bytes                 memset_bytes

extern void log_message(unsigned long, ...);
extern void debug_print(unsigned long, ...);
extern uint64_t unsigned_divide_64(uint64_t dividend, uint64_t divisor);
extern int get_device_info(void);
extern unsigned int gui_set_active_canvas(unsigned int);
extern void display_reflash_handler(void *display, unsigned int panel,
                                    void *frame_state, unsigned int action);
extern void display_timer_stop(void);
extern int display_delay_set(uint32_t delay);
extern void display_thread_service_abort(void);
extern int k_msgq_get(void *queue, void *message, uint64_t timeout);
extern uint32_t k_sleep_ticks(uint64_t timeout);
extern void display_power_set(unsigned int enabled);
extern void k_timer_init(void *timer, uintptr_t expiry, uintptr_t stop);
extern void memset_bytes(void*, int, int);

#define g_log_level              (*(volatile int32_t *)0x2000230cu)
#define g_log_use_alt_sink       (*(volatile int32_t *)0x20007554u)
#define g_dashboard_display_level (*(volatile int32_t *)0x20002544u)
#define g_display_msgq           ((void *)0x200038c4u)
#define g_display_timer          ((void *)0x20004ce0u)

#define DISPLAY_TIMER_EXPIRY     ((uintptr_t)0x0007d86du)
#define DISPLAY_LOG_FUNCTION     ((uintptr_t)0x000f01aau)

struct display_reflash_state {
    volatile uint8_t phase;
    volatile uint8_t panel;
};

#define g_display_reflash_state \
    (*(struct display_reflash_state *)0x2001d447u)
#define g_display_reflash_state_word (*(volatile uint16_t *)0x2001d447u)

struct display_message {
    uint8_t opcode;
    uint8_t reserved;
    uint16_t parameter_kind;
    uint32_t parameter;
    uint8_t payload[16];
};

enum display_message_opcode {
    DISPLAY_MESSAGE_START = 2,
    DISPLAY_MESSAGE_STOP = 3,
    DISPLAY_MESSAGE_SET_DELAY = 4,
    DISPLAY_MESSAGE_ACTION_4 = 5,
    DISPLAY_MESSAGE_ACTION_5 = 6,
    DISPLAY_MESSAGE_ACTION_6 = 7,
    DISPLAY_MESSAGE_ACTION_7 = 8,
};

enum display_reflash_phase {
    DISPLAY_REFLASH_IDLE = 0,
    DISPLAY_REFLASH_ACTIVE = 1,
    DISPLAY_REFLASH_STOPPING = 2,
};

enum display_reflash_action {
    DISPLAY_ACTION_RETRY = 0,
    DISPLAY_ACTION_START = 1,
    DISPLAY_ACTION_STOP = 2,
    DISPLAY_ACTION_SET_DELAY = 3,
    DISPLAY_ACTION_4 = 4,
    DISPLAY_ACTION_5 = 5,
    DISPLAY_ACTION_6 = 6,
    DISPLAY_ACTION_7 = 7,
};

static __attribute__((always_inline)) inline void
display_log(int minimum_level, uintptr_t message, unsigned int argument)
{
    if (g_log_level > minimum_level) {
        if (g_log_use_alt_sink == 0)
            log_message(message, DISPLAY_LOG_FUNCTION, argument);
        else
            debug_print(message, DISPLAY_LOG_FUNCTION, argument);
    }
}

static __attribute__((always_inline)) inline bool
message_panel(const struct display_message *message, uint8_t fallback,
              uint8_t *panel)
{
    if (message->parameter_kind == 0) {
        *panel = fallback;
        return true;
    }
    if (message->parameter_kind == 2 &&
        (uint8_t)message->parameter == 1) {
        *panel = (uint8_t)(message->parameter >> 8);
        return true;
    }
    return false;
}

static __attribute__((always_inline)) inline void
reset_reflash_state(void)
{
    g_display_reflash_state_word = 0;
}

static __attribute__((always_inline)) inline void
shutdown_display(void)
{
    display_power_set(0);
    display_timer_stop();
    reset_reflash_state();
}

void display_thread_handler(void *display)
{
    uint8_t *context = display;
    struct display_message message;
    void *frame_state = context + 0xd4;
    uint8_t *current_panel = context + 0xd5;

    display_log(2, 0x000efb2eu, 0);
    memset_bytes(&message, 0, sizeof(message));
    display_log(2, 0x000efb50u, 0);
    k_timer_init(g_display_timer, DISPLAY_TIMER_EXPIRY, 0);
    gui_set_active_canvas(context + 0xb90);
    reset_reflash_state();

    for (;;) {
        while (context[1] == 1 || context[1] == 8) {
            display_log(2, 0x000efb7au, 0);
            k_sleep_ticks(0x28000u);
        }

        memset_bytes(&message, 0, sizeof(message));
        int32_t level = g_dashboard_display_level;
        uint64_t interval = (uint64_t)(level & ~(level >> 31)) * 0x8000u + 999u;
        uint64_t timeout = unsigned_divide_64(interval, 1000u);
        bool received = k_msgq_get(g_display_msgq, &message, timeout) == 0;
        uint8_t phase = g_display_reflash_state.phase;
        uint8_t panel;

        if (phase == DISPLAY_REFLASH_ACTIVE) {
            if (!received) {
                if (*current_panel != 0) {
                    display_reflash_handler(display, *current_panel,
                                             frame_state,
                                             DISPLAY_ACTION_RETRY);
                } else {
                    display_log(3, 0x000efebcu, *current_panel);
                    display_log(0, 0x000eff0eu, 0);
                    shutdown_display();
                }
                display_thread_service_abort();
                continue;
            }

            switch (message.opcode) {
            case DISPLAY_MESSAGE_START:
                display_log(2, 0x000efcdfu, 0);
                if (message.parameter_kind == 0)
                    display_log(3, 0x000efd03u, 0);
                else if (message.parameter_kind == 2 &&
                         (uint8_t)message.parameter == 1)
                    display_log(3, 0x000efd2du,
                                (uint8_t)(message.parameter >> 8));
                else
                    display_log(0, 0x000efd45u, 0);
                if (message_panel(&message, *current_panel, &panel))
                    display_reflash_handler(display, panel, frame_state,
                                             DISPLAY_ACTION_START);
                break;

            case DISPLAY_MESSAGE_STOP:
                display_log(2, 0x000efd6fu, 0);
                g_display_reflash_state.phase = DISPLAY_REFLASH_STOPPING;
                if (message.parameter_kind == 0)
                    display_log(3, 0x000efd03u, 0);
                else if (message.parameter_kind == 2 &&
                         (uint8_t)message.parameter == 1)
                    display_log(3, 0x000efd2du,
                                (uint8_t)(message.parameter >> 8));
                else
                    display_log(0, 0x000efd45u, 0);
                if (!message_panel(&message, *current_panel, &panel))
                    panel = *current_panel;
                display_reflash_handler(display, panel, frame_state,
                                         DISPLAY_ACTION_STOP);
                display_timer_stop();
                display_log(2, 0x000eff70u, 0);
                break;

            case DISPLAY_MESSAGE_SET_DELAY:
                display_log(2, 0x000efe74u, message.parameter);
                display_delay_set(message.parameter);
                display_reflash_handler(display, *current_panel, frame_state,
                                         DISPLAY_ACTION_SET_DELAY);
                break;

            case DISPLAY_MESSAGE_ACTION_4:
                display_log(2, 0x000efebcu, 0);
                display_reflash_handler(display, *current_panel, frame_state,
                                         DISPLAY_ACTION_4);
                break;

            case DISPLAY_MESSAGE_ACTION_5:
                display_log(2, 0x000efef4u, 0);
                display_reflash_handler(display, *current_panel, frame_state,
                                         DISPLAY_ACTION_5);
                break;

            case DISPLAY_MESSAGE_ACTION_6:
                display_log(2, 0x000eff2cu, 0);
                display_reflash_handler(display, *current_panel, frame_state,
                                         DISPLAY_ACTION_6);
                break;

            case DISPLAY_MESSAGE_ACTION_7:
                display_log(2, 0x000eff5cu, 0);
                display_reflash_handler(display, *current_panel, frame_state,
                                         DISPLAY_ACTION_7);
                break;
            default:
                break;
            }
        } else if (phase == DISPLAY_REFLASH_STOPPING) {
            display_log(2, 0x000eff70u, 0);
        } else if (phase == DISPLAY_REFLASH_IDLE) {
            if (received && message.opcode == DISPLAY_MESSAGE_START) {
                if (*current_panel == 0x10) {
                    uintptr_t info = get_device_info();
                    uintptr_t version = *(uintptr_t *)(info + 0x100c);
                    if (*(uint8_t *)version < 12)
                        display_power_set(0);
                }
                display_log(2, 0x000efb9fu, 0);
                if (message.parameter_kind == 0)
                    display_log(3, 0x000efbb7u, 0);
                else if (message.parameter_kind == 2 &&
                         (uint8_t)message.parameter == 1)
                    display_log(3, 0x000efbe5u,
                                (uint8_t)(message.parameter >> 8));
                else
                    display_log(0, 0x000efc00u, 0);
                if (message_panel(&message, *current_panel, &panel)) {
                    g_display_reflash_state.panel = panel;
                    display_reflash_handler(display, panel, frame_state,
                                             DISPLAY_ACTION_START);
                    g_display_reflash_state.phase = DISPLAY_REFLASH_ACTIVE;
                }
            } else if (received && message.opcode == DISPLAY_MESSAGE_STOP) {
                display_log(2, 0x000efc2du, 0);
                reset_reflash_state();
                if (message.parameter_kind == 0)
                    display_log(3, 0x000efc62u, 0);
                else if (message.parameter_kind == 2 &&
                         (uint8_t)message.parameter == 1)
                    display_log(3, 0x000efc92u,
                                (uint8_t)(message.parameter >> 8));
                else
                    display_log(0, 0x000efcafu, 0);
                if (!message_panel(&message, *current_panel, &panel))
                    panel = *current_panel;
                display_reflash_handler(display, panel, frame_state,
                                         DISPLAY_ACTION_STOP);
            }
        } else {
            display_log(0, 0x000effafu, 0);
            display_reflash_handler(display, *current_panel, frame_state,
                                     DISPLAY_ACTION_STOP);
            shutdown_display();
        }

        display_thread_service_abort();
    }
}
