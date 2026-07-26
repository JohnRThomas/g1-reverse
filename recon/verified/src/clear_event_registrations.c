/* Reconstructed clear_event_registrations @ 0x753ec (raw FUN_000753ec).
 * Reviewed executable extent: 0x140 bytes; literals begin at 0x7552c. */
#include <stdbool.h>
#include <stdint.h>
#include <cmsis_gcc.h>

typedef struct poll_event {
    uint32_t node[2];
    void *poller;
    uint32_t flags;
    void *object;
} poll_event_t;

enum {
    POLL_TYPE_IGNORE = 0,
    POLL_TYPE_SIGNAL = 1,
    POLL_TYPE_SEM_AVAILABLE = 2,
    POLL_TYPE_DATA_AVAILABLE = 4,
    POLL_TYPE_MSGQ_DATA_AVAILABLE = 8,
};

#define POLL_EVENT_TYPE(event) (((event)->flags >> 8) & 0x3fu)
#define POLL_LOCK ((void *)0x2000b4a0u)
#define ASSERT_FAILURE_FORMAT ((const char *)0x00099cbdu)
#define SPINLOCK_SOURCE_FILE ((const char *)0x000f08c7u)
#define POLL_SOURCE_FILE ((const char *)0x000f871du)
#define ASSERT_ZERO_EXPRESSION ((const char *)0x000f7a30u)
#define ASSERT_SPIN_LOCK_VALID ((const char *)0x000f0920u)
#define ASSERT_SPIN_UNLOCK_VALID ((const char *)0x000f08f4u)
#define INVALID_SPIN_LOCK_FORMAT ((const char *)0x000f0935u)
#define INVALID_SPIN_UNLOCK_FORMAT ((const char *)0x000f090bu)
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
extern void kernel_print(const char *format, ...) __asm__("FUN_0007e2fa");
extern void assert_post_action(const char *source_file, uint32_t line)
    __attribute__((noreturn));

#define POLL_ASSERT_FAILURE(expression, file, line, detail_call) do { \
    kernel_print(ASSERT_FAILURE_FORMAT, (expression), (file), (line)); \
    detail_call; \
    assert_post_action((file), (line)); \
    __builtin_unreachable(); \
} while (0)

static inline __attribute__((always_inline)) void unlink_event_node(
    poll_event_t *event)
{
    uint32_t successor = event->node[0];

    if (successor != 0) {
        uint32_t predecessor = event->node[1];
        *(uint32_t *)predecessor = successor;
        *(uint32_t *)(successor + 4) = predecessor;
        event->node[0] = 0;
        event->node[1] = 0;
    }
}

void clear_event_registrations(poll_event_t *events, int event_count,
                               uint32_t interrupt_key)
{
    while (event_count != 0) {
        poll_event_t *event = &events[event_count - 1];

        event->poller = 0;
        switch (POLL_EVENT_TYPE(event)) {
        case POLL_TYPE_IGNORE:
            break;
        case POLL_TYPE_SIGNAL:
            if (event->object == 0) {
                POLL_ASSERT_FAILURE(ASSERT_SIGNAL_PRESENT, POLL_SOURCE_FILE,
                                    0xbe,
                                    kernel_print(INVALID_SIGNAL_FORMAT));
            }
            unlink_event_node(event);
            break;
        case POLL_TYPE_SEM_AVAILABLE:
            if (event->object == 0) {
                POLL_ASSERT_FAILURE(ASSERT_SEMAPHORE_PRESENT, POLL_SOURCE_FILE,
                                    0xb6,
                                    kernel_print(INVALID_SEMAPHORE_FORMAT));
            }
            unlink_event_node(event);
            break;
        case POLL_TYPE_DATA_AVAILABLE:
            if (event->object == 0) {
                POLL_ASSERT_FAILURE(ASSERT_QUEUE_PRESENT, POLL_SOURCE_FILE,
                                    0xba,
                                    kernel_print(INVALID_QUEUE_FORMAT));
            }
            unlink_event_node(event);
            break;
        case POLL_TYPE_MSGQ_DATA_AVAILABLE:
            if (event->object == 0) {
                POLL_ASSERT_FAILURE(ASSERT_MSGQ_PRESENT, POLL_SOURCE_FILE,
                                    0xc2,
                                    kernel_print(INVALID_MSGQ_FORMAT));
            }
            unlink_event_node(event);
            break;
        default:
            POLL_ASSERT_FAILURE(ASSERT_ZERO_EXPRESSION, POLL_SOURCE_FILE, 0xcf,
                                kernel_print(INVALID_EVENT_FORMAT));
        }

        if (!z_spin_unlock_valid(POLL_LOCK)) {
            POLL_ASSERT_FAILURE(ASSERT_SPIN_UNLOCK_VALID, SPINLOCK_SOURCE_FILE,
                                0xf0,
                                kernel_print(INVALID_SPIN_UNLOCK_FORMAT,
                                             POLL_LOCK));
        }
        __set_BASEPRI(interrupt_key);
        __ISB();

        interrupt_key = __get_BASEPRI();
        __set_BASEPRI_MAX(0x20);
        __ISB();
        if (!z_spin_lock_valid(POLL_LOCK)) {
            POLL_ASSERT_FAILURE(ASSERT_SPIN_LOCK_VALID, SPINLOCK_SOURCE_FILE,
                                0x72,
                                kernel_print(INVALID_SPIN_LOCK_FORMAT,
                                             POLL_LOCK));
        }
        z_spin_lock_set_owner(POLL_LOCK);
        --event_count;
    }
}
