/* net-core FUN_0103448c @ 0x103448c  (parity 300 trials PROVEN) */
#include "../../headers/g1_nrf_regs.h"

extern void FUN_01034368(void *param_1, int param_2);
void FUN_0103448c(int param_1) {
  *(volatile unsigned int *)((param_1 << 3) + (G1_NRF_DPPIC_NS_BASE + 0x4)) = 1;
  FUN_01034368((void *)0x210006a0, param_1);
}

