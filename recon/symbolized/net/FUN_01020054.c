#include "g1_net_symbols.h"
/* net-core FUN_01020054 @ 0x1020054  (parity 300 trials PROVEN) */

extern void FUN_0101ff4c(void);
static void DataSynchronizationBarrier(int opt) { (void)opt; }
static void InstructionSynchronizationBarrier(int opt) { (void)opt; }

void FUN_01020054(void)
{
  unsigned int iVar1;

  *(volatile unsigned int *)(0xe000e100u + 0x80) = 0x4000;
  iVar1 = REG_4100e000 /*=0x4100e000*/;
  DataSynchronizationBarrier(0xf);
  InstructionSynchronizationBarrier(0xf);
  *(volatile unsigned int *)(REG_4100e000 /*=0x4100e000*/ + 0x500) = 0;
  *(volatile unsigned int *)(iVar1 + 0x500) = 0;
  FUN_0101ff4c();
  *(volatile unsigned int *)(iVar1 + 0x80) = 0;
  return;
}
