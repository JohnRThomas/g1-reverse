/* Reconstructed FUN_00065b9c @ 0x65b9c */
#include <stdint.h>

extern uint64_t FUN_00065434(uint32_t);
extern void FUN_000654c4(uint32_t, uint32_t);
extern uintptr_t FUN_00065584(uint32_t *);
extern uint32_t FUN_00065620(uint32_t);
extern void FUN_000851ca(uint32_t, uint32_t);

static inline uint32_t configured_mode(uintptr_t table, uint32_t channel)
{
  return (*(volatile uint32_t *)(table + (channel + 0x80) * 4) >> 16) & 3;
}

void FUN_00065b9c(void)
{
  uint32_t interrupt_mask =
      FUN_00065620((*(volatile uint32_t *)0x5000d304 & 0xff) |
                   0x80000000u);

  if ((int32_t)interrupt_mask < 0) {
    uint32_t pending[2];
    pending[0] = *(volatile uint32_t *)0x50842520;
    *(volatile uint32_t *)0x50842520 = pending[0];
    pending[1] = *(volatile uint32_t *)0x50842820;
    *(volatile uint32_t *)0x50842820 = pending[1];

    for (;;) {
      for (unsigned group = 0; group < 2; ++group) {
        uint8_t channel_prefix =
            *(const volatile uint8_t *)(0x000f6bb7 + group);
        while (pending[group] != 0) {
          uint32_t channel =
              __builtin_ctz(pending[group]) | ((uint32_t)channel_prefix << 5);
          uint64_t mapping = FUN_00065434(channel);
          uint32_t index = (uint32_t)mapping;
          uint32_t pending_bit = (uint32_t)(mapping >> 32);
          uint16_t settings =
              *(volatile uint16_t *)(0x20002bc0 + (index + 8) * 2);

          uint8_t *pending_bytes = (uint8_t *)&pending[group];
          pending_bytes[pending_bit >> 3] &=
              (uint8_t)~(1u << (pending_bit & 7));

          uint32_t lookup_channel = channel;
          uintptr_t table = FUN_00065584(&lookup_channel);
          uint32_t requested_mode = (settings >> 2) & 7;
          uint32_t old_mode = configured_mode(table, lookup_channel);

          if ((settings & 0x10) != 0) {
            FUN_000654c4(channel, requested_mode);
            lookup_channel = channel;
            table = FUN_00065584(&lookup_channel);
            if (old_mode == configured_mode(table, lookup_channel)) {
              FUN_000851ca(channel, 0);
              FUN_000851ca(channel, old_mode);
            }
          } else if (old_mode == 2) {
            FUN_000851ca(channel, 3);
            if ((requested_mode & 5) == 1) {
              FUN_000654c4(channel, requested_mode);
            }
          } else {
            FUN_000851ca(channel, 2);
            if (requested_mode == 3 ||
                (old_mode == 3 && requested_mode == 2)) {
              FUN_000654c4(channel, requested_mode);
            }
          }

          lookup_channel = channel;
          table = FUN_00065584(&lookup_channel);
          *(volatile uint32_t *)(table + 0x20) =
              lookup_channel < 32 ? 1u << lookup_channel : 0;
        }
      }

      FUN_00065620(0x80000000u);
      pending[0] = *(volatile uint32_t *)0x50842520;
      *(volatile uint32_t *)0x50842520 = pending[0];
      pending[1] = *(volatile uint32_t *)0x50842820;
      *(volatile uint32_t *)0x50842820 = pending[1];
      if ((pending[0] | pending[1]) == 0) {
        break;
      }
    }
    interrupt_mask &= 0x7fffffffu;
  }

  while (interrupt_mask != 0) {
    uint32_t slot = __builtin_ctz(interrupt_mask);
    uintptr_t configuration = 0x5000d510 + slot * 4;
    uint32_t channel =
        (*(volatile uint32_t *)configuration >> 8) & 0x3f;
    uint32_t mode =
        (*(volatile uint32_t *)configuration >> 16) & 3;
    FUN_000654c4(channel, mode);
    interrupt_mask &= ~(1u << slot);
  }
}
