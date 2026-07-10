#include "g1_app_symbols.h"
/* named: gpiote_in_event_reg_offset */
/* Reconstructed gpiote_in_event_reg_offset @ 0x655ec  (parity: 300/300 trials, PROVEN) */

extern int printk(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);
extern int assert_post_action(unsigned int a, unsigned int b);

int gpiote_in_event_reg_offset(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned int r0 = param_1;
  if (param_1 > 7) {
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "index < 8" /*=0xf6b73*/, "WEST_TOPDIR/modules/hal/nordic/nrfx/hal/nrf_gpiote.h" /*=0xf6b3e*/, 0x2aa, param_4);
    r0 = assert_post_action("WEST_TOPDIR/modules/hal/nordic/nrfx/hal/nrf_gpiote.h" /*=0xf6b3e*/, 0x2aa);
  }
  return r0 * 4 + 0x100;
}

