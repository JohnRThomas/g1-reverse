#include "g1_net_symbols.h"
/* net-core FUN_0102de38 @ 0x0102de38 (true code extent 0x14) */
#include <stdint.h>
uint32_t FUN_0102de38(void){
  return __atomic_exchange_n((uint32_t *)((unsigned long)&g_net_tick_correction_pending) /*=0x21004664*/,0,__ATOMIC_ACQ_REL);
}
