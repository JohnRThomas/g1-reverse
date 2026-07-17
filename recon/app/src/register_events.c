/* Reconstructed register_events @ 0x751d0 (raw FUN_000751d0).
 * Reviewed executable extent: 0x1ce bytes; literals begin at 0x753a0. */
#include <stdbool.h>
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"

typedef struct poll_event {
    uint32_t node[2];
    void *poller;
    uint32_t flags;
    void *object;
} poll_event_t;

typedef struct {
    uint8_t is_polling;
} poller_t;

enum {
    POLL_TYPE_IGNORE = 0,
    POLL_TYPE_SIGNAL = 1,
    POLL_TYPE_SEM_AVAILABLE = 2,
    POLL_TYPE_DATA_AVAILABLE = 4,
    POLL_TYPE_MSGQ_DATA_AVAILABLE = 8,
};

#define POLL_EVENT_TYPE(event) (((event)->flags >> 8) & 0x3fu)
#define POLL_EVENT_STATE(event) (((event)->flags >> 14) & 0x7fu)
#define POLL_EVENT_STATE_MASK (0x7fu << 14)

#define POLL_LOCK ((void *)0x2000b4a0u)
#define ASSERT_FAILURE_FORMAT ((const char *)0x00099cbdu)
#define SPINLOCK_SOURCE_FILE ((const char *)0x000f08c7u)
#define POLL_SOURCE_FILE ((const char *)0x000f871du)
#define ASSERT_ZERO_EXPRESSION ((const char *)0x000f7a30u)
#define ASSERT_SPIN_LOCK_VALID ((const char *)0x000f0920u)
#define ASSERT_SPIN_UNLOCK_VALID ((const char *)0x000f08f4u)
#define INVALID_SPIN_LOCK_FORMAT ((const char *)0x000f0935u)
#define INVALID_SPIN_UNLOCK_FORMAT ((const char *)0x000f090bu)
#define INVALID_EVENT_TYPE_FORMAT ((const char *)0x000f873eu)
#define ASSERT_SEMAPHORE_PRESENT ((const char *)0x000f875bu)
#define INVALID_SEMAPHORE_FORMAT ((const char *)0x000f8775u)
#define ASSERT_QUEUE_PRESENT ((const char *)0x000f878au)
#define INVALID_QUEUE_FORMAT ((const char *)0x000f87a6u)
#define ASSERT_SIGNAL_PRESENT ((const char *)0x000f87b7u)
#define INVALID_SIGNAL_FORMAT ((const char *)0x000f87d4u)
#define ASSERT_MSGQ_PRESENT ((const char *)0x000f87ebu)
#define INVALID_MSGQ_FORMAT ((const char *)0x000f8806u)
#define INVALID_EVENT_FORMAT ((const char *)0x000f881fu)

extern bool z_spin_lock_valid(void *lock) __asm__("FUN_00072040");
extern void z_spin_lock_set_owner(void *lock) __asm__("FUN_00072078");
extern bool z_spin_unlock_valid(void *lock) __asm__("FUN_0007205c");
extern void poll_add_event_by_priority(void *event_list, poll_event_t *event,
                                       poller_t *poller)
    __asm__("FUN_00086778");
extern void kernel_print(const char *format, ...) __asm__("FUN_0007e2fa");
extern void assert_post_action(const char *source_file, uint32_t line)
    __attribute__((noreturn));

#define POLL_ASSERT_FAILURE(expression, file, line, detail_call) do { \
    kernel_print(ASSERT_FAILURE_FORMAT, (expression), (file), (line)); \
    detail_call; \
    assert_post_action((file), (line)); \
    __builtin_unreachable(); \
} while (0)

static inline __attribute__((always_inline)) void set_event_ready(
    poll_event_t *event, uint32_t state)
{
    event->poller = 0;
    event->flags = (event->flags & ~POLL_EVENT_STATE_MASK) |
                   ((POLL_EVENT_STATE(event) | state) << 14);
}

int register_events(poll_event_t *events, int event_count, poller_t *poller,
                    bool just_check)
{
    int registered_count = 0;

    for (int index = 0; index < event_count; ++index) {
        poll_event_t *event = &events[index];
        uint32_t ready_state = 0;
        uint32_t interrupt_key = __get_BASEPRI();
        __set_BASEPRI_MAX(0x20);
        __ISB();

        if (!z_spin_lock_valid(POLL_LOCK)) {
            POLL_ASSERT_FAILURE(ASSERT_SPIN_LOCK_VALID, SPINLOCK_SOURCE_FILE,
                                0x72,
                                kernel_print(INVALID_SPIN_LOCK_FORMAT,
                                             POLL_LOCK));
        }
        z_spin_lock_set_owner(POLL_LOCK);

        switch (POLL_EVENT_TYPE(event)) {
        case POLL_TYPE_IGNORE:
            break;
        case POLL_TYPE_SIGNAL:
            if (*(uint32_t *)((uint8_t *)event->object + 8) != 0) {
                ready_state = 1;
            }
            break;
        case POLL_TYPE_SEM_AVAILABLE:
            if (*(uint32_t *)((uint8_t *)event->object + 8) != 0) {
                ready_state = 2;
            }
            break;
        case POLL_TYPE_DATA_AVAILABLE:
            if (*(uint32_t *)event->object != 0) {
                ready_state = 4;
            }
            break;
        case POLL_TYPE_MSGQ_DATA_AVAILABLE:
            if (*(int32_t *)((uint8_t *)event->object + 0x24) > 0) {
                ready_state = 0x10;
            }
            break;
        default:
            POLL_ASSERT_FAILURE(ASSERT_ZERO_EXPRESSION, POLL_SOURCE_FILE, 0x63,
                                kernel_print(INVALID_EVENT_TYPE_FORMAT,
                                             POLL_EVENT_TYPE(event)));
        }

        if (ready_state != 0) {
            set_event_ready(event, ready_state);
            poller->is_polling = false;
        } else if (!just_check && poller->is_polling) {
            void *event_list;

            switch (POLL_EVENT_TYPE(event)) {
            case POLL_TYPE_IGNORE:
                event_list = 0;
                break;
            case POLL_TYPE_SIGNAL:
                if (event->object == 0) {
                    POLL_ASSERT_FAILURE(ASSERT_SIGNAL_PRESENT, POLL_SOURCE_FILE,
                                        0x95,
                                        kernel_print(INVALID_SIGNAL_FORMAT));
                }
                event_list = event->object;
                break;
            case POLL_TYPE_SEM_AVAILABLE:
                if (event->object == 0) {
                    POLL_ASSERT_FAILURE(ASSERT_SEMAPHORE_PRESENT,
                                        POLL_SOURCE_FILE, 0x8d,
                                        kernel_print(INVALID_SEMAPHORE_FORMAT));
                }
                event_list = (uint8_t *)event->object + 0x10;
                break;
            case POLL_TYPE_DATA_AVAILABLE:
                if (event->object == 0) {
                    POLL_ASSERT_FAILURE(ASSERT_QUEUE_PRESENT, POLL_SOURCE_FILE,
                                        0x91,
                                        kernel_print(INVALID_QUEUE_FORMAT));
                }
                event_list = (uint8_t *)event->object + 0x14;
                break;
            case POLL_TYPE_MSGQ_DATA_AVAILABLE:
                if (event->object == 0) {
                    POLL_ASSERT_FAILURE(ASSERT_MSGQ_PRESENT, POLL_SOURCE_FILE,
                                        0x99,
                                        kernel_print(INVALID_MSGQ_FORMAT));
                }
                event_list = (uint8_t *)event->object + 0x28;
                break;
            default:
                POLL_ASSERT_FAILURE(ASSERT_ZERO_EXPRESSION, POLL_SOURCE_FILE,
                                    0xa6,
                                    kernel_print(INVALID_EVENT_FORMAT));
            }

            if (event_list != 0) {
                poll_add_event_by_priority(event_list, event, poller);
            }
            event->poller = poller;
            ++registered_count;
        }

        if (!z_spin_unlock_valid(POLL_LOCK)) {
            POLL_ASSERT_FAILURE(ASSERT_SPIN_UNLOCK_VALID, SPINLOCK_SOURCE_FILE,
                                0xf0,
                                kernel_print(INVALID_SPIN_UNLOCK_FORMAT,
                                             POLL_LOCK));
        }
        __set_BASEPRI(interrupt_key);
        __ISB();
    }

    return registered_count;
}
