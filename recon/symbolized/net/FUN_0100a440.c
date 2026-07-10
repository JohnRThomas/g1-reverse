#include "g1_net_symbols.h"
/* net-core FUN_0100a440 @ 0x100a440  (parity 300 trials PROVEN) */
#define P_0100a4c8 ((uintptr_t)&g_net_bufpool_base_ptr) /*=0x21000bbc*/
#define P_0100a4cc ((uintptr_t)&g_net_bufpool_slot_cnt) /*=0x21000bb8*/

extern void FUN_01008d00(int, int);
extern void FUN_0100a31c(unsigned char *, int);

unsigned char *FUN_0100a440(void)
{
  unsigned char local_d;
  unsigned char *local_c;

  local_c = (unsigned char *)0;
  local_d = 0;
  for (;;) {
    if (*(volatile unsigned char *)P_0100a4cc <= local_d) break;
    if (*(unsigned char *)((unsigned int)local_d * 0x28 + *(volatile unsigned int *)P_0100a4c8) != 0) {
      local_c = (unsigned char *)((unsigned int)local_d * 0x28 + *(volatile unsigned int *)P_0100a4c8);
      break;
    }
    local_d = local_d + 1;
  }
  if (local_c == (unsigned char *)0) {
    FUN_01008d00(9, 0xa9);
  }
  if (local_c != (unsigned char *)0) {
    local_c[2] = 0;
    FUN_0100a31c(local_c, 1);
    *local_c = 0;
  }
  return local_c;
}

