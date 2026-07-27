/* Reconstructed FUN_00067600 @ 0x67600 */
#include <stdint.h>

extern void FUN_0007e2ec(uint32_t, uint32_t);
extern void FUN_0007e2fa(unsigned long, ...);
extern int FUN_00085316(uintptr_t, void *);
extern int FUN_0008539a(uintptr_t, uint32_t);

struct callback_payload {
  uint8_t event;
  uint8_t reserved_01[3];
  uint16_t status;
  uint16_t reserved_06;
  uint32_t value_10;
  uint32_t value_18;
  uint32_t value_0c;
  uint32_t value_14;
};

struct callback_state {
  void (*handler)(const struct callback_payload *, void *);
  void *user_data;
  uint32_t state;
  uint32_t value_0c;
  uint32_t value_10;
  uint32_t value_14;
  uint32_t value_18;
  uint32_t flags;
  uint16_t status;
  uint8_t reserved_22;
  uint8_t active;
  uint8_t acknowledged;
  uint8_t enabled;
};

static inline volatile uint32_t *register32(uintptr_t base, unsigned offset)
{
  return (volatile uint32_t *)(base + offset);
}

void FUN_00067600(uintptr_t peripheral, struct callback_state *callback)
{
  if (callback->handler == 0) {
    FUN_0007e2fa(0x00099cbd, 0x000f6e2c, 0x000f6fef, 0x297);
    FUN_0007e2ec(0x000f6fef, 0x297);
  }

  int has_event_2 = FUN_0008539a(peripheral, 2);
  int has_event_200 = FUN_0008539a(peripheral, 0x200);

  if (has_event_200 != 0 && has_event_2 == 0) {
    *register32(peripheral, 0x308) = callback->state;
    callback->state = 2;
    *register32(peripheral, 0x304) = callback->state;
    if (FUN_0008539a(peripheral, 0x1000000) == 0 ||
        (*register32(peripheral, 0x200) & 0x200) == 0) {
      *register32(peripheral, 0x20) = 1;
      *register32(peripheral, 0x14) = 1;
    }
    callback->active = 1;
    return;
  }

  if (has_event_200 == 0 && has_event_2 == 0) {
    FUN_0008539a(peripheral, 0x40000);
    if ((uint8_t)callback->status != 0) {
      *register32(peripheral, 0x200) = 0x200;
      callback->state = 0x202;
      *register32(peripheral, 0x308) = 0x019c0202;
      *register32(peripheral, 0x304) = callback->state;
      *register32(peripheral, 8) = 1;
      *register32(peripheral, 0x20) = 1;
      return;
    }
    if (callback->enabled == 0) {
      goto clear_state;
    }
  } else {
    if ((callback->flags & 0x40) == 0 && callback->active == 0) {
      callback->active =
          (uint8_t)(FUN_00085316(peripheral, callback) ^ 1);
    }
    if ((callback->flags & 4) != 0) {
      goto publish;
    }

    *register32(peripheral, 0x160) = 0;
    *register32(peripheral, 0x15c) = 0;
    if (callback->enabled == 0 || callback->active != 0) {
clear_state:
      *register32(peripheral, 0x200) = 0;
      callback->state = 0;
      *register32(peripheral, 0x308) = 0x019c0202;

      uint32_t irq_field = ((uint32_t)peripheral >> 12) & 0xffu;
      int irq = irq_field < 0x80u
          ? (int)irq_field : (int)irq_field - 0x100;
      if (irq >= 0) {
        volatile uint32_t *nvic_icpr =
            (volatile uint32_t *)(0xe000e280u + ((unsigned)irq >> 5) * 4);
        *nvic_icpr = 1u << ((unsigned)irq & 31);
      }
    }
  }

publish:
  struct callback_payload payload = {
    .status = callback->status,
    .value_10 = callback->value_10,
    .value_18 = callback->value_18,
    .value_0c = callback->value_0c,
    .value_14 = callback->value_14,
  };

  uint32_t event_flags = *register32(peripheral, 0x4c4);
  *register32(peripheral, 0x4c4) = event_flags;
  if ((event_flags & 2) != 0) {
    payload.event = 1;
  } else if ((event_flags & 4) != 0) {
    payload.event = 2;
  } else if ((event_flags & 1) != 0) {
    payload.event = 3;
  } else {
    payload.event = (uint8_t)(callback->active << 2);
  }

  if (callback->enabled == 0) {
    callback->acknowledged = 0;
  }
  if ((callback->flags & 4) == 0 || callback->active != 0) {
    callback->handler(&payload, callback->user_data);
  }
}
