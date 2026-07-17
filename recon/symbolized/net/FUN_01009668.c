#include "g1_net_symbols.h"
/* net-core FUN_01009668 @ 0x1009668  (parity 300 trials PROVEN) */
#define P_010096f8 ((unsigned long)&g_net_bump_alloc_state) /*=0x21000ba8*/
#define P_010096fc ((unsigned long)&g_net_bump_alloc_cursor) /*=0x21000bac*/
#define P_01009700 ((unsigned long)&g_net_bump_alloc_offset) /*=0x21000bb0*/
#define P_01009704 0x21000b7c

extern void FUN_01008d00(int, int);
extern void FUN_01025a84(void *, int, int);

void FUN_01009668(unsigned int *param_1)
{
  unsigned int uVar1;

  if (param_1 == (unsigned int *)0) {
    *(volatile unsigned char *)P_010096f8 = 1;
    *(volatile unsigned int *)P_01009700 = 0;
    *(volatile unsigned int *)P_010096fc = *(volatile unsigned int *)P_01009700;
  } else {
    if (*(volatile unsigned char *)P_010096f8 != 2) {
      FUN_01008d00(0x17, 0x106);
    }
    *(volatile unsigned char *)P_010096f8 = 3;
    if ((*param_1 & 7) != 0) {
      FUN_01008d00(0x17, 0x10b);
    }
    uVar1 = *(volatile unsigned int *)P_010096fc;
    *(volatile unsigned int *)P_01009700 = *param_1;
    *(volatile unsigned int *)P_010096fc = *(volatile unsigned int *)P_01009700;
    *(volatile unsigned int *)P_01009700 = uVar1 + *(volatile unsigned int *)P_01009700;
    *param_1 = *(volatile unsigned int *)P_01009700;
    FUN_01025a84((void *)P_01009704, 0, 0x2c);
  }
  return;
}
