#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_2          => struct g1_layout_adc_channel_cfg__param_0290            [param_0290; library]
 * Raw function identity: 0x0005f654.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0005f654 @ 0x0005f654
 * public-name: adc_channel_config
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_log_msg_runtime_create                 <= FUN_0004d944 @ 0x0004d944
 *   adc_channel_config                       <= FUN_0005f654 @ 0x0005f654
 * address symbols (name @ address):
 *   rodata_880e0                             @ 0x000880e0
 *   rodata_f5503                             @ 0x000f5503
 *   rodata_f5522                             @ 0x000f5522
 *   rodata_f5546                             @ 0x000f5546
 *   adc_context                              @ 0x20002190
 */
/* Reconstructed FUN_0005f654 @ 0x5f654  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../../../headers/g1_nrf_regs.h"
extern void z_log_msg_runtime_create(unsigned int, unsigned int, unsigned int, unsigned int);
unsigned adc_channel_config(unsigned param_1, unsigned char *param_2)
{
  unsigned short uVar1;
  int iVar2, iVar5;
  unsigned uVar3, uVar4;
  struct { unsigned count, format; } error;
  uVar4 = param_2[4] & 0x1f;
  if (7 < uVar4) return 0xffffffea;
  uVar3 = (unsigned)*param_2;
  switch(uVar3) {
  case 0: case 1: case 2: case 3: break;
  default: error.format = ((unsigned long)&rodata_f5503) /*=0xf5503*/; goto LAB;
  case 5: uVar3 = 4; break;
  case 8: uVar3 = 5; break;
  case 9: uVar3 = 6; break;
  case 0xb: uVar3 = 7;
  }
  if (param_2[1] == 3) { iVar5 = 1; }
  else {
    error.format = ((unsigned long)&rodata_f5522) /*=0xf5522*/;
    if (param_2[1] != 4) goto LAB;
    iVar5 = 0;
  }
  uVar1 = *(unsigned short*)(param_2 + 2);
  if (uVar1 != 0x400a) {
    error.format = ((unsigned long)&rodata_f5546) /*=0xf5546*/;
    if (0x400a < uVar1) {
      if (uVar1 == 0x4014) iVar2 = 4;
      else if (uVar1 == 0x4028) iVar2 = 5;
      else { if (uVar1 != 0x400f) goto LAB; iVar2 = 3; }
      goto LAB2;
    }
    if (uVar1 == 0x4003) { iVar2 = 0; goto LAB2; }
    if (uVar1 == 0x4005) { iVar2 = 1; goto LAB2; }
    if (uVar1 != 0) {
LAB:
      error.count = 2;
      z_log_msg_runtime_create(((unsigned long)&rodata_880e0) /*=0x880e0*/, 0x1040, &error, 0);
      return 0xffffffea;
    }
  }
  iVar2 = 2;
LAB2:
  *(volatile unsigned*)(uVar4 * 0x10 + (G1_NRF_SAADC_S_BASE + 0x518)) =
      uVar3 << 8 | (((unsigned)param_2[4] << 0x1a) >> 0x1f) << 0x14 | iVar5 << 0xc | iVar2 << 0x10;
  *(volatile unsigned*)(uVar4 * 0x10 + (G1_NRF_SAADC_S_BASE + 0x514)) = (unsigned)param_2[6];
  *(volatile unsigned*)(uVar4 * 0x10 + (G1_NRF_SAADC_S_BASE + 0x510)) = 0;
  *(volatile unsigned char*)(((unsigned long)&adc_context) /*=0x20002190*/ + uVar4 + 0xa0) = param_2[5];
  return 0;
}
