#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01034d8c @ 0x01034d8c
 * public-name: FUN_01034d8c
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103e700                           @ 0x0103e700
 *   g_sdc_radio_context_area                 @ 0x21004aec
 */
/* net-core FUN_01034d8c @ 0x1034d8c  (parity 300 trials PROVEN) */

extern void FUN_0102eb2c(int);
extern void assert_print(unsigned int, unsigned int, unsigned int);
extern void FUN_01039bb0(unsigned int, unsigned int);
unsigned int FUN_01034d8c(unsigned int param_1, int param_2, int param_3)
{
  if (param_2 == 0) {
    assert_print(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103e700) /*=0x103e700*/, 0x34);
    FUN_01039bb0(((unsigned long)&rodata_103e700) /*=0x103e700*/, 0x34);
  }
  int *piVar1 = (int*)((unsigned long)&g_sdc_radio_context_area) /*=0x21004aec*/;
  unsigned int uVar2;
  if (*(char*)((char*)piVar1+4) == 0) {
    FUN_0102eb2c(0x12);
    uVar2 = 0x0bad0000;
    *(unsigned char*)((char*)piVar1+4) = 1;
    *piVar1 = param_2;
    piVar1[2] = param_3;
  } else {
    uVar2 = 0x0bad000c;
  }
  return uVar2;
}
