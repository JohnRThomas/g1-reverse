#include "g1_net_symbols.h"
/* net-core FUN_01035028 @ 0x1035028  (parity 300 trials PROVEN) */

extern void FUN_01039bbe(unsigned int, unsigned int, unsigned int);
extern unsigned int FUN_01039bb0(unsigned int, unsigned int);
void FUN_01035028(int *param_1)
{
  unsigned int base = ((unsigned long)&g_net_gpiote_evt_handler_table) /*=0x21004af8*/;
  unsigned int r0 = (unsigned int)(unsigned long)param_1;
  unsigned int r1 = 0xc;
  unsigned char idx = *(unsigned char*)((char*)param_1 + 4);
  unsigned int entryAddr = base + idx * 0xc;
  if (*(char*)(unsigned long)(entryAddr + 8) == 0) {
    FUN_01039bbe(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103e73b) /*=0x103e73b*/, 0xca);
    r0 = FUN_01039bb0(((unsigned long)&rodata_103e73b) /*=0x103e73b*/, 0xca);
    r1 = 0xca;
  }
  int *r4 = *(int**)(unsigned long)r0;
  *(int*)((char*)r4 + 0x10) = 1;
  unsigned int b2 = *(unsigned char*)(unsigned long)(r0 + 4);
  unsigned int r3 = r1 * b2 + base;
  *(char*)(unsigned long)(r3 + 8) = 1;
}
