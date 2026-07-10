#include "g1_net_symbols.h"
/* net-core FUN_01009d18 @ 0x1009d18  (parity 300 trials PROVEN) */
/* net-core FUN_01009d18 @ 0x1009d18  (parity 300 trials PROVEN) */
/* net-core FUN_01009d18 @ 0x1009d18  (parity 300 trials PROVEN) */
/* net-core FUN_01009d18 @ 0x1009d18  (parity 300 trials PROVEN) */

static volatile int *const P_1009d60 = (volatile int *)((uintptr_t)&g_net_ctx_ptr_table) /*=0x21000b7c*/;
extern signed char FUN_01027470(int, unsigned short);
extern int FUN_010274ea(int, unsigned char);
unsigned int FUN_01009d18(unsigned short param_1, unsigned char param_2)
{
  int val = P_1009d60[param_2];
  signed char c = FUN_01027470(val, param_1);
  unsigned int r;
  if ((unsigned char)c == 0xff) {
    r = 0;
  } else {
    r = (unsigned int)FUN_010274ea(val, (unsigned char)c);
  }
  return r;
}




