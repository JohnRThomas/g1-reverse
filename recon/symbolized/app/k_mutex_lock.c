#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000723b8 @ 0x000723b8
 * public-name: k_mutex_lock
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   k_mutex_lock                             <= FUN_000723b8 @ 0x000723b8
 *   z_reschedule                             <= FUN_000739f0 @ 0x000739f0
 *   z_pend_curr                              <= FUN_00073f6c @ 0x00073f6c
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   k_mutex_owner_prio_check                 <= FUN_000864b2 @ 0x000864b2
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f08c7                             @ 0x000f08c7
 *   rodata_f08f4                             @ 0x000f08f4   [INLINED -- G6 literal batch]
 *   rodata_f090b                             @ 0x000f090b   [INLINED -- G6 literal batch]
 *   rodata_f0920                             @ 0x000f0920   [INLINED -- G6 literal batch]
 *   rodata_f0935                             @ 0x000f0935   [INLINED -- G6 literal batch]
 *   rodata_f801f                             @ 0x000f801f
 *   rodata_f813a                             @ 0x000f813a
 *   rodata_f815c                             @ 0x000f815c
 *   g_current_thread_ptr                     @ 0x2000b450
 *   mutex_spinlock_b470                      @ 0x2000b470
 */
/* Reconstructed FUN_000723b8 @ 0x723b8 */
#include <stdint.h>
#include <cmsis_gcc.h>
#include "../../headers/g1_log.h"

extern int z_spin_lock_valid(uint32_t);
extern int z_spin_unlock_valid(uint32_t);
extern void z_spin_lock_set_owner(uint32_t);
extern void z_reschedule(uint32_t, uint32_t);
extern int z_pend_curr(uint32_t, uint32_t, void *, uint32_t,
                       void *, uint32_t);
extern void assert_post_action(uint32_t, uint32_t);
extern int k_mutex_owner_prio_check(void *, int);

struct queue_entry {
  struct queue_entry *next;
  uint32_t reserved_04;
  void *item;
  uint32_t acquisitions;
  int priority;
};

static inline int item_priority(const void *item)
{
  return *(const volatile int8_t *)((uintptr_t)item + 0x0e);
}

static __attribute__((always_inline)) inline void lock_failure(uint32_t lock)
{
  printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)"z_spin_lock_valid(l)") /*=0xf0920*/, ((unsigned long)&rodata_f08c7) /*=0xf08c7*/, 0x72);
  printk(((unsigned long)"\tInvalid spinlock %p\n") /*=0xf0935*/, lock);
  assert_post_action(((unsigned long)&rodata_f08c7) /*=0xf08c7*/, 0x72);
}

static __attribute__((always_inline)) inline void unlock_failure(uint32_t lock)
{
  printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)"z_spin_unlock_valid(l)") /*=0xf08f4*/, ((unsigned long)&rodata_f08c7) /*=0xf08c7*/, 0xf0);
  printk(((unsigned long)"\tNot my spinlock %p\n") /*=0xf090b*/, lock);
  assert_post_action(((unsigned long)&rodata_f08c7) /*=0xf08c7*/, 0xf0);
}

int k_mutex_lock(struct queue_entry *entry, uint32_t reserved,
                 void *successor, uint32_t successor_value)
{
  const uint32_t lock = ((unsigned long)&mutex_spinlock_b470) /*=0x2000b470*/;
  (void)reserved;

  if (__get_IPSR() != 0) {
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)&rodata_f801f) /*=0xf801f*/, ((unsigned long)&rodata_f813a) /*=0xf813a*/, 0x65);
    printk(((unsigned long)&rodata_f815c) /*=0xf815c*/);
    assert_post_action(((unsigned long)&rodata_f813a) /*=0xf813a*/, 0x65);
  }

  uint32_t previous_priority = __get_BASEPRI();
  __set_BASEPRI_MAX(0x20);
  __ISB();
  if (z_spin_lock_valid(lock) == 0) {
    lock_failure(lock);
  }
  z_spin_lock_set_owner(lock);

  void *head = *(void *volatile *)((unsigned long)&g_current_thread_ptr) /*=0x2000b450*/;
  if (entry->acquisitions == 0 || entry->item == head) {
    int priority = entry->acquisitions == 0
        ? item_priority(head) : entry->priority;
    entry->acquisitions++;
    entry->priority = priority;
    entry->item = head;
    if (z_spin_unlock_valid(lock) != 0) {
      __set_BASEPRI(previous_priority);
      __ISB();
      return 0;
    }
    unlock_failure(lock);
  }

  if (successor == 0 && successor_value == 0) {
    if (z_spin_unlock_valid(lock) != 0) {
      __set_BASEPRI(previous_priority);
      __ISB();
      return -16;
    }
    unlock_failure(lock);
  }

  int head_priority = item_priority(head);
  int current_priority = item_priority(entry->item);
  int target_priority =
      head_priority < current_priority ? head_priority : current_priority;
  if (target_priority < -127) {
    target_priority = -127;
  }

  int previous_update = 0;
  if (current_priority > target_priority) {
    previous_update = k_mutex_owner_prio_check(entry->item, target_priority);
  }

  /* The fourth formal is unused by FUN_00073f6c; the two successor fields
     are its stacked fifth and sixth arguments. */
  if (z_pend_curr(lock, previous_priority, entry, 0,
                   successor, successor_value) == 0) {
    return 0;
  }

  uint32_t reacquire_priority = __get_BASEPRI();
  __set_BASEPRI_MAX(0x20);
  __ISB();
  if (z_spin_lock_valid(lock) == 0) {
    lock_failure(lock);
  }
  z_spin_lock_set_owner(lock);

  if (entry->item != 0) {
    int priority = entry->priority;
    struct queue_entry *next = entry->next;
    if (next != entry && next != 0) {
      int next_priority = item_priority(next);
      if (next_priority <= priority) {
        priority = next_priority;
      }
      if (priority < -127) {
        priority = -127;
      }
    }
    if (k_mutex_owner_prio_check(entry->item, priority) != 0) {
      z_reschedule(lock, reacquire_priority);
      return -11;
    }
  }

  if (previous_update != 0) {
    z_reschedule(lock, reacquire_priority);
    return -11;
  }
  if (z_spin_unlock_valid(lock) != 0) {
    __set_BASEPRI(reacquire_priority);
    __ISB();
    return -11;
  }
  unlock_failure(lock);
  return -11;
}
