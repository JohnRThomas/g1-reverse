#include "g1_net_symbols.h"
/* net-core FUN_01034328 @ 0x1034328  (parity 300 trials PROVEN) */

#include <stdatomic.h>
int FUN_01034328(_Atomic unsigned int *param_1, unsigned char *param_2)
{
  unsigned int r4 = atomic_load(param_1);
  if (r4 == 0) {
    return 0xbad0002;
  }
  for (;;) {
    int bit = 31 - __builtin_clz(r4);
    unsigned int newval = r4 & ~(1u << bit);
    if (atomic_compare_exchange_strong(param_1, &r4, newval)) {
      *param_2 = (unsigned char)bit;
      return 0xbad0000;
    }
    if (r4 == 0) {
      return 0xbad0002;
    }
  }
}
