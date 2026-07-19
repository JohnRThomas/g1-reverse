#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000753ec @ 0x000753ec
 * public-name: clear_event_registrations
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f08c7                             @ 0x000f08c7
 *   rodata_f08f4                             @ 0x000f08f4
 *   rodata_f090b                             @ 0x000f090b
 *   rodata_f0920                             @ 0x000f0920
 *   rodata_f0935                             @ 0x000f0935
 *   rodata_f7a30                             @ 0x000f7a30
 *   rodata_f871d                             @ 0x000f871d
 *   rodata_f875b                             @ 0x000f875b
 *   rodata_f8775                             @ 0x000f8775
 *   rodata_f878a                             @ 0x000f878a
 *   rodata_f87a6                             @ 0x000f87a6
 *   rodata_f87b7                             @ 0x000f87b7
 *   rodata_f87d4                             @ 0x000f87d4
 *   rodata_f87eb                             @ 0x000f87eb
 *   rodata_f8806                             @ 0x000f8806
 *   rodata_f881f                             @ 0x000f881f
 *   poll_spinlock                            @ 0x2000b4a0
 */
/* Reconstructed clear_event_registrations @ 0x753ec (raw FUN_000753ec).
 * Reviewed executable extent: 0x140 bytes; literals begin at 0x7552c. */
#include <stdbool.h>
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"

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
#define POLL_LOCK ((void *)((unsigned long)&poll_spinlock) /*=0x2000b4a0*/)
#define ASSERT_FAILURE_FORMAT ((const char *)((unsigned long)&rodata_99cbd) /*=0x99cbd*/)
#define SPINLOCK_SOURCE_FILE ((const char *)((unsigned long)&rodata_f08c7) /*=0xf08c7*/)
#define POLL_SOURCE_FILE ((const char *)((unsigned long)&rodata_f871d) /*=0xf871d*/)
#define ASSERT_ZERO_EXPRESSION ((const char *)((unsigned long)&rodata_f7a30) /*=0xf7a30*/)
#define ASSERT_SPIN_LOCK_VALID ((const char *)((unsigned long)&rodata_f0920) /*=0xf0920*/)
#define ASSERT_SPIN_UNLOCK_VALID ((const char *)((unsigned long)&rodata_f08f4) /*=0xf08f4*/)
#define INVALID_SPIN_LOCK_FORMAT ((const char *)((unsigned long)&rodata_f0935) /*=0xf0935*/)
#define INVALID_SPIN_UNLOCK_FORMAT ((const char *)((unsigned long)&rodata_f090b) /*=0xf090b*/)
#define ASSERT_SEMAPHORE_PRESENT ((const char *)((unsigned long)&rodata_f875b) /*=0xf875b*/)
#define INVALID_SEMAPHORE_FORMAT ((const char *)((unsigned long)&rodata_f8775) /*=0xf8775*/)
#define ASSERT_QUEUE_PRESENT ((const char *)((unsigned long)&rodata_f878a) /*=0xf878a*/)
#define INVALID_QUEUE_FORMAT ((const char *)((unsigned long)&rodata_f87a6) /*=0xf87a6*/)
#define ASSERT_SIGNAL_PRESENT ((const char *)((unsigned long)&rodata_f87b7) /*=0xf87b7*/)
#define INVALID_SIGNAL_FORMAT ((const char *)((unsigned long)&rodata_f87d4) /*=0xf87d4*/)
#define ASSERT_MSGQ_PRESENT ((const char *)((unsigned long)&rodata_f87eb) /*=0xf87eb*/)
#define INVALID_MSGQ_FORMAT ((const char *)((unsigned long)&rodata_f8806) /*=0xf8806*/)
#define INVALID_EVENT_FORMAT ((const char *)((unsigned long)&rodata_f881f) /*=0xf881f*/)

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
