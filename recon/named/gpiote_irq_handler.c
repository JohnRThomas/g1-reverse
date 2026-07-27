/* readable reconstruction; identity: FUN_00065b9c @ 0x00065b9c
 * public-name: gpiote_irq_handler
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_pin_idx                              <= FUN_00065434 @ 0x00065434
 *   gpiote_pin_event_dispatch                <= FUN_000654c4 @ 0x000654c4
 *   gpio_port_base_from_pin                  <= FUN_00065584 @ 0x00065584
 *   gpiote_read_and_clear_pending_events     <= FUN_00065620 @ 0x00065620
 *   gpiote_irq_handler                       <= FUN_00065b9c @ 0x00065b9c
 *   nrf_gpio_cfg_sense_set                   <= FUN_000851ca @ 0x000851ca
 * address symbols (name @ address):
 *   rodata_f6bb7                             @ 0x000f6bb7
 *   g_gpiote_cb                              @ 0x20002bc0
 *   REG_5000d304                             @ 0x5000d304
 */
/* Reconstructed FUN_00065b9c @ 0x65b9c */
#include <stdint.h>
#include "../headers/g1_nrf_regs.h"

extern unsigned long get_pin_idx(unsigned long);
extern void gpiote_pin_event_dispatch(uint32_t, uint32_t);
extern uintptr_t gpio_port_base_from_pin(uint32_t *);
extern uint32_t gpiote_read_and_clear_pending_events(uint32_t);
extern void nrf_gpio_cfg_sense_set(unsigned long, unsigned char);

static inline uint32_t configured_mode(uintptr_t table, uint32_t channel)
{
  return (*(volatile uint32_t *)(table + (channel + 0x80) * 4) >> 16) & 3;
}

void gpiote_irq_handler(void)
{
  uint32_t interrupt_mask =
      gpiote_read_and_clear_pending_events((*(volatile uint32_t *)(G1_NRF_GPIOTE0_S_BASE + 0x304) & 0xff) |
                   0x80000000u);

  if ((int32_t)interrupt_mask < 0) {
    uint32_t pending[2];
    pending[0] = *(volatile uint32_t *)(G1_NRF_P0_S_BASE + 0x20);
    *(volatile uint32_t *)(G1_NRF_P0_S_BASE + 0x20) = pending[0];
    pending[1] = *(volatile uint32_t *)(G1_NRF_P1_S_BASE + 0x20);
    *(volatile uint32_t *)(G1_NRF_P1_S_BASE + 0x20) = pending[1];

    for (;;) {
      for (unsigned group = 0; group < 2; ++group) {
        uint8_t channel_prefix =
            *(const volatile uint8_t *)(0x000f6bb7 + group);
        while (pending[group] != 0) {
          uint32_t channel =
              __builtin_ctz(pending[group]) | ((uint32_t)channel_prefix << 5);
          uint64_t mapping = get_pin_idx(channel);
          uint32_t index = (uint32_t)mapping;
          uint32_t pending_bit = (uint32_t)(mapping >> 32);
          uint16_t settings =
              *(volatile uint16_t *)(0x20002bc0 + (index + 8) * 2);

          uint8_t *pending_bytes = (uint8_t *)&pending[group];
          pending_bytes[pending_bit >> 3] &=
              (uint8_t)~(1u << (pending_bit & 7));

          uint32_t lookup_channel = channel;
          uintptr_t table = gpio_port_base_from_pin(&lookup_channel);
          uint32_t requested_mode = (settings >> 2) & 7;
          uint32_t old_mode = configured_mode(table, lookup_channel);

          if ((settings & 0x10) != 0) {
            gpiote_pin_event_dispatch(channel, requested_mode);
            lookup_channel = channel;
            table = gpio_port_base_from_pin(&lookup_channel);
            if (old_mode == configured_mode(table, lookup_channel)) {
              nrf_gpio_cfg_sense_set(channel, 0);
              nrf_gpio_cfg_sense_set(channel, old_mode);
            }
          } else if (old_mode == 2) {
            nrf_gpio_cfg_sense_set(channel, 3);
            if ((requested_mode & 5) == 1) {
              gpiote_pin_event_dispatch(channel, requested_mode);
            }
          } else {
            nrf_gpio_cfg_sense_set(channel, 2);
            if (requested_mode == 3 ||
                (old_mode == 3 && requested_mode == 2)) {
              gpiote_pin_event_dispatch(channel, requested_mode);
            }
          }

          lookup_channel = channel;
          table = gpio_port_base_from_pin(&lookup_channel);
          *(volatile uint32_t *)(table + 0x20) =
              lookup_channel < 32 ? 1u << lookup_channel : 0;
        }
      }

      gpiote_read_and_clear_pending_events(0x80000000u);
      pending[0] = *(volatile uint32_t *)(G1_NRF_P0_S_BASE + 0x20);
      *(volatile uint32_t *)(G1_NRF_P0_S_BASE + 0x20) = pending[0];
      pending[1] = *(volatile uint32_t *)(G1_NRF_P1_S_BASE + 0x20);
      *(volatile uint32_t *)(G1_NRF_P1_S_BASE + 0x20) = pending[1];
      if ((pending[0] | pending[1]) == 0) {
        break;
      }
    }
    interrupt_mask &= 0x7fffffffu;
  }

  while (interrupt_mask != 0) {
    uint32_t slot = __builtin_ctz(interrupt_mask);
    uintptr_t configuration = (G1_NRF_GPIOTE0_S_BASE + 0x510) + slot * 4;
    uint32_t channel =
        (*(volatile uint32_t *)configuration >> 8) & 0x3f;
    uint32_t mode =
        (*(volatile uint32_t *)configuration >> 16) & 3;
    gpiote_pin_event_dispatch(channel, mode);
    interrupt_mask &= ~(1u << slot);
  }
}
