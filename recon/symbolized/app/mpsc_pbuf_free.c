#include "g1_app_symbols.h"
/* named: mpsc_pbuf_free */
/* globals referenced:
//   0x2000a0cc  g_log_msg_pool_ptr           
*/
/* Reconstructed mpsc_pbuf_free @ 0x4d578  (parity: 200/200 trials, PROVEN) */

#include <stdint.h>
extern int FUN_0004bfc8(uint32_t, uint32_t);
void mpsc_pbuf_free(uint32_t param_1){ FUN_0004bfc8(*(volatile uint32_t*)((uintptr_t)&g_log_msg_pool_ptr) /*=0x2000a0cc*/, param_1); }

