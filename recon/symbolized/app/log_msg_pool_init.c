#include "g1_app_symbols.h"
/* named: log_msg_pool_init */
/* globals referenced:
//   0x20003648  g_log_msg_mpsc_buffer        
//   0x2000a0cc  g_log_msg_pool_ptr           
*/
/* Reconstructed log_msg_pool_init @ 0x4d508  (parity: 300/300 trials, PROVEN) */

extern void mpsc_pbuf_init(unsigned int, unsigned int);
void log_msg_pool_init(void)
{
  mpsc_pbuf_init(((uintptr_t)&g_log_msg_mpsc_buffer) /*=0x20003648*/, ((uintptr_t)&tbl_8ac20) /*=0x8aca0*/);
  *(volatile unsigned int *)((uintptr_t)&g_log_msg_pool_ptr) /*=0x2000a0cc*/ = ((uintptr_t)&g_log_msg_mpsc_buffer) /*=0x20003648*/;
}

