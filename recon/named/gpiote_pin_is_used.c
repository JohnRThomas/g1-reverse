/* named: gpiote_pin_is_used */
/* globals referenced:
//   0x20002bc0  g_gpiote_cb                  
*/
/* Reconstructed gpiote_pin_is_used @ 0x65448  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int get_pin_idx(void);

unsigned short gpiote_pin_is_used(void)
{
    int iVar1 = get_pin_idx();
    volatile uint16_t *base = (volatile uint16_t *)0x20002bc0UL;
    return base[iVar1 + 8] & 1;
}

