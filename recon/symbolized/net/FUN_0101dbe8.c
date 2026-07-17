#include "g1_net_symbols.h"
/* net-core FUN_0101dbe8 @ 0x101dbe8  (parity 300 trials PROVEN) */

void FUN_0101dbe8(void) {
  *(volatile unsigned int *)(0x21000354 + 0x50) = 0x010103bd;
  *(volatile unsigned int *)(0x21000354 + 0x54) = 0x01010305;
  *(volatile unsigned int *)(0x21000400 + 0x50) = ((unsigned long)&rodata_10102c1) /*=0x10102c1*/;
  *(volatile unsigned int *)(0x21000400 + 0x54) = 0x0101cae5;
}
