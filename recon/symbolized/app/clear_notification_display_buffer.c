#include "g1_app_symbols.h"
/* named: clear_notification_display_buffer */
/* globals referenced:
//   0x20004988  g_notification_display_buffer 
*/
/* Reconstructed clear_notification_display_buffer @ 0x3cf34  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void memset_bytes(void*,int,int);
void clear_notification_display_buffer(void)
{
  memset_bytes((void*)((uintptr_t)&g_notification_display_buffer) /*=0x20004988*/,0,0x230);
  return;
}

