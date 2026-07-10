#include "g1_net_symbols.h"
/* net-core FUN_010333b4 @ 0x10333b4  (parity 300 trials PROVEN) */
/* net-core FUN_010333b4 @ 0x10333b4  (parity 300 trials PROVEN) */

extern uint32_t FUN_01033354(void);

unsigned int zero_val = 0;

uint32_t FUN_010333b4(uint32_t *param_1)
{
  volatile unsigned char *G_pcVar2 = (volatile unsigned char*)(unsigned long)zero_val;
  volatile uint32_t *G_e4 = (volatile uint32_t*)(unsigned long)zero_val;
  volatile uint32_t *G_dest = (volatile uint32_t*)(unsigned long)zero_val;

  if (param_1 == (uint32_t*)0) {
    return FUN_01033354();
  }
  if (*G_pcVar2 != 0) {
    return FUN_01033354();
  }
  *G_e4 = param_1[1];
  G_dest[0] = param_1[0];
  G_dest[1] = param_1[1];
  return FUN_01033354();
}



