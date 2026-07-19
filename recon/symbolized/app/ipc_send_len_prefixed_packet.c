#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00025740 @ 0x00025740
 * public-name: ipc_send_len_prefixed_packet
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ipc_send_len_prefixed_packet             <= FUN_00025740 @ 0x00025740
 *   ipc_transport_ops_dispatch               <= FUN_0007c85e @ 0x0007c85e
 *   sleep_fixed_33_ticks                     <= FUN_0007c87a @ 0x0007c87a
 * address symbols (name @ address):
 *   rodata_9f239                             @ 0x0009f239
 */
/* Reconstructed FUN_00025740 @ 0x25740  (parity: 300/300 trials, PROVEN) */

extern int ipc_transport_ops_dispatch(int, void*, int, int);
extern void sleep_fixed_33_ticks(void);
extern void log_message(unsigned int, int);

int ipc_send_len_prefixed_packet(int param_1, int param_2, unsigned int param_3, int param_4, int param_5)
{
  unsigned short local_24 = (unsigned short)(((param_3 & 0xff) << 8) | ((param_3 >> 8) & 0xff));
  struct { unsigned short *p; int a; unsigned char b; int c; int d; unsigned char e; } local_20;
  local_20.p = &local_24;
  local_20.a = 2;
  local_20.b = 0;
  local_20.c = param_4;
  local_20.d = param_5;
  local_20.e = 7;
  int iVar1 = ipc_transport_ops_dispatch(param_1, &local_20, 2, param_2);
  sleep_fixed_33_ticks();
  if (iVar1 < 0) {
    log_message(((unsigned long)&rodata_9f239) /*=0x9f239*/, iVar1);
  }
  return iVar1;
}
