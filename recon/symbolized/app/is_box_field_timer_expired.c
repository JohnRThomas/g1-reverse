#include "g1_app_symbols.h"
/* named: is_box_field_timer_expired */
/* globals referenced:
//   0x20007a24  g_box_field_timer            
*/
/* Reconstructed is_box_field_timer_expired @ 0x25458  (parity: 300/300 trials, PROVEN) */

extern void refresh_box_field_timer(void);

unsigned int is_box_field_timer_expired(void)
{
    refresh_box_field_timer();
    return (*(volatile unsigned int*)((uintptr_t)&g_box_field_timer) /*=0x20007a24*/) > 0x13ec;
}

