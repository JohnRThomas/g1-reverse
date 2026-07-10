#include "g1_app_symbols.h"
/* named: refresh_box_field_timer */
/* globals referenced:
//   0x20007a24  g_box_field_timer            
//   0x20007a34  g_box_field_raw_timestamp    
*/
/* Reconstructed refresh_box_field_timer @ 0x2542c  (parity: 300/300 trials, PROVEN) */

extern void FUN_0007c830(unsigned int);
void refresh_box_field_timer(void)
{
  unsigned int *puVar1 = (unsigned int *)((uintptr_t)&g_box_field_raw_timestamp) /*=0x20007a34*/;
  FUN_0007c830(((uintptr_t)&g_box_field_raw_timestamp) /*=0x20007a34*/);
  *(volatile unsigned int *)((uintptr_t)&g_box_field_timer) /*=0x20007a24*/ = *(volatile unsigned int *)puVar1;
}

