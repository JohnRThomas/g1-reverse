/* readable reconstruction; identity: FUN_0004b4fc @ 0x0004b4fc
 * public-name: FUN_0004b4fc
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   notify_one                               <= FUN_0007e1e6 @ 0x0007e1e6
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_4b8a5                             @ 0x0004b8a5
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f0824                             @ 0x000f0824
 *   rodata_f0846                             @ 0x000f0846
 *   rodata_f0852                             @ 0x000f0852
 *   rodata_f0875                             @ 0x000f0875
 *   rodata_f088c                             @ 0x000f088c
 *   rodata_f08a2                             @ 0x000f08a2
 *   rodata_f08b1                             @ 0x000f08b1
 *   rodata_f08c7                             @ 0x000f08c7
 *   rodata_f08f4                             @ 0x000f08f4
 *   rodata_f090b                             @ 0x000f090b
 *   rodata_f0920                             @ 0x000f0920
 *   rodata_f0935                             @ 0x000f0935
 *   rodata_f7a30                             @ 0x000f7a30
 */
/* Full reconstruction of FUN_0004b4fc @ 0x4b4fc (916-byte catalog extent). */
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"

typedef struct pending_node {
    struct pending_node *next;
    void (*notify)(void *owner, struct pending_node *node,
                   uint32_t mode, uint32_t operation);
} pending_node;

typedef struct transition_ops {
    void (*start)(void *owner, uintptr_t reason);
    void (*drain)(void *owner, uintptr_t reason);
    void (*stop)(void *owner, uintptr_t reason);
} transition_ops;

typedef struct transition_state {
    pending_node *head;
    pending_node *tail;
    pending_node *observers;
    uint32_t reserved;
    transition_ops *ops;
    uint8_t lock[4];
    uint32_t operation;
    uint16_t flags;
    int16_t pending_count;
} transition_state;

extern int z_spin_lock_valid(void *lock);
extern int z_spin_unlock_valid(void *lock, ...);
extern void z_spin_lock_set_owner(void *lock);
extern uint64_t FUN_0007e18e(transition_state *state, ...);
extern void notify_one(transition_state *state, pending_node *node,
                         uint32_t mode, uint32_t operation);
extern void printk(uintptr_t format, ...);
extern void assert_post_action(uintptr_t file, uint32_t line) __attribute__((noreturn));

static __attribute__((always_inline)) inline uint32_t enter_critical(void)
{
    uint32_t saved = 0;
    if ((__get_CONTROL() & 1u) == 0)
        saved = __get_BASEPRI();
    if ((__get_CONTROL() & 1u) == 0) {
        uint32_t current = __get_BASEPRI();
        if (current == 0 || current > 0x20)
            __set_BASEPRI(0x20);
    }
    __ISB();
    return saved;
}

static __attribute__((always_inline)) inline void leave_critical(uint32_t saved)
{
    if ((__get_CONTROL() & 1u) == 0)
        __set_BASEPRI(saved);
    __ISB();
}

static __attribute__((always_inline)) inline void fatal(uintptr_t message, uint32_t line)
{
    printk(0x00099cbdu, message, 0x000f0824u, line);
    assert_post_action(0x000f0824u, line);
}

static __attribute__((always_inline)) inline void unlock_failure(void *lock)
{
    printk(0x00099cbdu, 0x000f08f4u, 0x000f08c7u, 0xf0u);
    printk(0x000f090bu, lock);
    assert_post_action(0x000f08c7u, 0xf0u);
}

void FUN_0004b4fc(transition_state *state, uint32_t request,
                  uint32_t saved_priority, uint32_t unused,
                  uint32_t call_context)
{
    uint32_t flags = state->flags;
    uint32_t desired = flags & 7u;
    (void)unused;

    if (flags & 8u) {
        state->flags = (uint16_t)(flags | (request == 1 ? 0x10u : 0x20u));
        if (z_spin_unlock_valid(state->lock, state->flags, saved_priority, flags) == 0)
            unlock_failure(state->lock);
        leave_critical(saved_priority);
        return;
    }

again:
    if (request == 2) {
        uint64_t result = FUN_0007e18e(state, desired, saved_priority,
                                      flags, call_context);
        uint32_t next_mode = (uint32_t)(result >> 32);
        uint32_t action = (uint32_t)result;

        if (action == 0) {
            if (z_spin_unlock_valid(state->lock) == 0)
                unlock_failure(state->lock);
            leave_critical(saved_priority);
            return;
        }

        pending_node *released = 0;
        void (*completion)(void *, uintptr_t) = 0;
        uint32_t operation = state->operation;
        uint32_t notify_mode = next_mode;

        if (action == 1) {
process_current:
            flags = state->flags;
            operation = state->operation;
            desired = flags & 7u;

            if ((int32_t)operation < 0) {
                released = state->head;
                state->head = 0;
                state->tail = 0;
                state->flags = (uint16_t)((flags & ~7u) | 1u);
            } else if (desired == 5 || desired == 6) {
                released = state->head;
                state->head = 0;
                state->tail = 0;
                if (desired == 6) {
                    for (pending_node *p = released; p; p = p->next)
                        state->pending_count++;
                    state->flags = (uint16_t)((flags & ~7u) | 2u);
                } else {
                    state->flags = (uint16_t)(flags & ~7u);
                }
                flags = state->flags;
                result = FUN_0007e18e(state);
                next_mode = (uint32_t)(result >> 32);
                if ((uint32_t)result != 0)
                    state->flags = (uint16_t)(flags | 0x20u);
            } else if (desired == 4) {
                state->flags = (uint16_t)(flags & ~7u);
                flags = state->flags;
                result = FUN_0007e18e(state);
                if ((uint32_t)result != 0)
                    state->flags = (uint16_t)(flags | 0x20u);
                next_mode = (uint32_t)(result >> 32);
            } else {
                fatal(0x000f7a30u, 0x11bu);
            }

            flags = state->flags;
            notify_mode = flags & 7u;
            if (notify_mode != next_mode) {
                completion = 0;
            } else if (released == 0) {
                goto after_callbacks;
            }
        } else if (action == 3) {
            if (next_mode != 0)
                fatal(0x000f0846u, 0x156u);
            if (state->head == 0)
                fatal(0x000f0852u, 0x157u);
            completion = state->ops->start;
            if (!completion)
                fatal(0x000f0875u, 0x15au);
            state->flags = (uint16_t)((state->flags & ~7u) | 6u);
            notify_mode = 6;
            operation = next_mode;
        } else if (action == 4) {
            if (next_mode != 2)
                fatal(0x000f088cu, 0x15du);
            if (state->pending_count != 0)
                fatal(0x000f08a2u, 0x15eu);
            completion = state->ops->drain;
            if (!completion)
                fatal(0x000f0875u, 0x161u);
            state->flags = (uint16_t)((state->flags & ~7u) | 4u);
            notify_mode = 4;
            operation = 0;
        } else if (action == 5) {
            if (next_mode != 1)
                fatal(0x000f08b1u, 0x164u);
            if (state->head == 0)
                fatal(0x000f0852u, 0x165u);
            completion = state->ops->stop;
            if (!completion)
                fatal(0x000f0875u, 0x168u);
            state->flags = (uint16_t)((state->flags & ~7u) | 5u);
            notify_mode = 5;
            operation = 0;
        } else {
            fatal(0x000f7a30u, 0x16bu);
        }

        {
            int notify_observers = state->observers != 0;
            if (!notify_observers && released == 0 && completion == 0)
                goto after_callbacks;

            state->flags |= 8u;
            if (z_spin_unlock_valid(state->lock) == 0)
                unlock_failure(state->lock);
            leave_critical(saved_priority);

            if (notify_observers) {
                for (pending_node *p = state->observers; p; ) {
                    pending_node *next = p->next;
                    p->notify(state, p, notify_mode, operation);
                    p = next;
                }
            }
            while (released) {
                pending_node *next = released->next;
                notify_one(state, released, notify_mode, operation);
                released = next;
            }
            if (completion)
                completion(state, 0x0004b8a5u);

            saved_priority = enter_critical();
            if (z_spin_lock_valid(state->lock) == 0) {
                printk(0x00099cbdu, 0x000f0920u, 0x000f08c7u, 0x72u);
                printk(0x000f0935u, state->lock);
                assert_post_action(0x000f08c7u, 0x72u);
            }
            z_spin_lock_set_owner(state->lock);
            state->flags &= (uint16_t)~8u;
        }

after_callbacks:
        flags = state->flags;
        if (flags & 0x10u) {
            state->flags = (uint16_t)(flags & ~0x10u);
            desired = flags & 7u;
            request = 1;
            goto process_current;
        }
        if (flags & 0x20u) {
            state->flags = (uint16_t)(flags & ~0x20u);
            desired = flags & 7u;
            request = 2;
            flags = state->flags;
            goto again;
        }
    } else {
        goto process_current;
    }

    if (z_spin_unlock_valid(state->lock) == 0)
        unlock_failure(state->lock);
    leave_critical(saved_priority);
}
