/* Reconstructed FUN_000723b8 @ 0x723b8 */
#include <stdint.h>
#include <cmsis_gcc.h>

extern int FUN_00072040(uint32_t);
extern int FUN_0007205c(uint32_t);
extern void FUN_00072078(uint32_t);
extern void FUN_000739f0(uint32_t, uint32_t);
extern int FUN_00073f6c(uint32_t, uint32_t, void *, uint32_t,
                       void *, uint32_t);
extern void FUN_0007e2fa(uint32_t, ...);
extern void FUN_0007e2ec(uint32_t, uint32_t);
extern int FUN_000864b2(void *, int);

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
  FUN_0007e2fa(0x00099cbd, 0x000f0920, 0x000f08c7, 0x72);
  FUN_0007e2fa(0x000f0935, lock);
  FUN_0007e2ec(0x000f08c7, 0x72);
}

static __attribute__((always_inline)) inline void unlock_failure(uint32_t lock)
{
  FUN_0007e2fa(0x00099cbd, 0x000f08f4, 0x000f08c7, 0xf0);
  FUN_0007e2fa(0x000f090b, lock);
  FUN_0007e2ec(0x000f08c7, 0xf0);
}

int FUN_000723b8(struct queue_entry *entry, uint32_t reserved,
                 void *successor, uint32_t successor_value)
{
  const uint32_t lock = 0x2000b470;
  (void)reserved;

  if (__get_IPSR() != 0) {
    FUN_0007e2fa(0x00099cbd, 0x000f801f, 0x000f813a, 0x65);
    FUN_0007e2fa(0x000f815c);
    FUN_0007e2ec(0x000f813a, 0x65);
  }

  uint32_t previous_priority = __get_BASEPRI();
  __set_BASEPRI_MAX(0x20);
  __ISB();
  if (FUN_00072040(lock) == 0) {
    lock_failure(lock);
  }
  FUN_00072078(lock);

  void *head = *(void *volatile *)0x2000b450;
  if (entry->acquisitions == 0 || entry->item == head) {
    int priority = entry->acquisitions == 0
        ? item_priority(head) : entry->priority;
    entry->acquisitions++;
    entry->priority = priority;
    entry->item = head;
    if (FUN_0007205c(lock) != 0) {
      __set_BASEPRI(previous_priority);
      __ISB();
      return 0;
    }
    unlock_failure(lock);
  }

  if (successor == 0 && successor_value == 0) {
    if (FUN_0007205c(lock) != 0) {
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
    previous_update = FUN_000864b2(entry->item, target_priority);
  }

  /* The fourth formal is unused by FUN_00073f6c; the two successor fields
     are its stacked fifth and sixth arguments. */
  if (FUN_00073f6c(lock, previous_priority, entry, 0,
                   successor, successor_value) == 0) {
    return 0;
  }

  uint32_t reacquire_priority = __get_BASEPRI();
  __set_BASEPRI_MAX(0x20);
  __ISB();
  if (FUN_00072040(lock) == 0) {
    lock_failure(lock);
  }
  FUN_00072078(lock);

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
    if (FUN_000864b2(entry->item, priority) != 0) {
      FUN_000739f0(lock, reacquire_priority);
      return -11;
    }
  }

  if (previous_update != 0) {
    FUN_000739f0(lock, reacquire_priority);
    return -11;
  }
  if (FUN_0007205c(lock) != 0) {
    __set_BASEPRI(reacquire_priority);
    __ISB();
    return -11;
  }
  unlock_failure(lock);
  return -11;
}
