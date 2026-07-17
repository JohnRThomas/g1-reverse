#include "g1_net_symbols.h"
/* net-core FUN_0102cfbc @ 0x102cfbc  (parity 300 trials PROVEN) */

#include <stdint.h>
typedef unsigned int undefined4;
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"
extern void FUN_010317d4(void);
extern void FUN_0102f4ec(undefined4);
extern void FUN_01039722(undefined4);
extern void FUN_0102e9bc(void);

void FUN_0102cfbc(undefined4 param_1)
{
  __set_BASEPRI_MAX(0x40);
  __ISB();
  FUN_010317d4();
  FUN_0102f4ec(param_1);
  FUN_01039722(((unsigned long)&rodata_103d42c) /*=0x103d42c*/);
  while (1) {
    FUN_0102e9bc();
  }
}
