#include "g1_net_symbols.h"
/* net-core FUN_01039fb6 @ 0x01039fb6 (true code extent 0x0e) */
#include <stdint.h>
uint32_t *FUN_01039fb6(uint32_t *p,uint32_t value){
  (void)__atomic_exchange_n(p,value,__ATOMIC_ACQ_REL);
  return p;
}
