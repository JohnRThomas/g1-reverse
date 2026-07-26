#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_3          => struct g1_layout_gpiote_trigger_ctx__param_0331         [param_0331; G1-original]
 *   local_19         => struct g1_layout_gpiote_trigger_locals__stack_1302      [stack_1302; G1-original]
 * Raw function identity: 0x000657e4.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_000657e4 @ 0x000657e4
 * public-name: gpiote_trigger_enable
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_pin_idx                              <= FUN_00065434 @ 0x00065434
 *   pin_in_use_by_te                         <= FUN_00065460 @ 0x00065460
 *   gpiote_pin_sense_is_enabled              <= FUN_00065478 @ 0x00065478
 *   pin_is_output                            <= FUN_00065494 @ 0x00065494
 *   gpiote_trigger_enable                    <= FUN_000657e4 @ 0x000657e4
 *   gpio_pin_cnf_build_fields                <= FUN_00085130 @ 0x00085130
 * address symbols (name @ address):
 *   g_gpiote_cb                              @ 0x20002bc0
 */
/* Reconstructed FUN_000657e4 @ 0x657e4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../../../headers/g1_nrf_regs.h"
typedef unsigned long long u64;
extern u64 get_pin_idx(unsigned);
extern int pin_in_use_by_te(unsigned);
extern u64 gpiote_pin_sense_is_enabled(unsigned);
extern int pin_is_output(unsigned);
extern void gpio_pin_cnf_build_fields(unsigned,void*,int,int,int,int);
unsigned gpiote_trigger_enable(unsigned param_1, unsigned param_2, unsigned char *param_3)
{
  unsigned char bVar1,bVar2,bVar3;
  int iVar4,iVar6,iVar7;
  unsigned uVar5;
  unsigned short uVar8;
  u64 uVar9, uVar10;
  unsigned char enable = 1;
  uVar9 = get_pin_idx(param_1);
  if ((int)(uVar9 >> 0x20) != 0) {
    iVar4 = pin_is_output(param_1);
    if ((iVar4 == 0) && (iVar4 = pin_in_use_by_te(param_1), iVar4 != 0)) {
      return 0x0bad0004;
    }
    uVar10 = gpiote_pin_sense_is_enabled(param_1);
    iVar4 = (int)(uVar10 >> 0x20);
    if (((int)uVar10 != 0) && (*(char*)(iVar4 + 1) == 1)) {
      return 0x0bad0004;
    }
    gpio_pin_cnf_build_fields(param_1, &enable, iVar4 + 1, iVar4 + 2, iVar4, 0);
    iVar4 = (int)uVar9 + 8;
    *(volatile unsigned short*)(((unsigned long)g_gpiote_cb) /*=0x20002bc0*/ + iVar4 * 2) =
        *(volatile unsigned short*)(((unsigned long)g_gpiote_cb) /*=0x20002bc0*/ + iVar4 * 2) | 3;
  }
  uVar5 = 0x0bad0000;
  if ((param_3 != 0) &&
      (iVar6 = pin_is_output(param_1), iVar4 = ((unsigned long)g_gpiote_cb) /*=0x20002bc0*/, uVar5 = 0x0bad0004, iVar6 != 0)) {
    bVar3 = *param_3;
    iVar6 = (int)uVar9 + 8;
    iVar7 = (unsigned)bVar3 * 4;
    uVar8 = *(volatile unsigned short*)(((unsigned long)g_gpiote_cb) /*=0x20002bc0*/ + iVar6 * 2) & 0x1fdf;
    *(volatile unsigned*)(iVar7 + (G1_NRF_GPIOTE0_S_BASE + 0x510)) = 0;
    *(volatile unsigned short*)(iVar4 + iVar6 * 2) = uVar8;
    *(volatile unsigned*)(iVar7 + (G1_NRF_GPIOTE0_S_BASE + 0x510)) = 0;
    bVar1 = param_3[1];
    uVar5 = 0x0bad0000;
    if (bVar1 != 0) {
      bVar2 = param_3[2];
      *(volatile unsigned*)(iVar7 + (G1_NRF_GPIOTE0_S_BASE + 0x510)) = *(volatile unsigned*)(iVar7 + (G1_NRF_GPIOTE0_S_BASE + 0x510)) & 0xffecc0ff;
      *(volatile unsigned*)(iVar7 + (G1_NRF_GPIOTE0_S_BASE + 0x510)) =
          (param_1 & 0x3f) << 8 | (bVar1 & 3) << 0x10 | *(volatile unsigned*)(iVar7 + (G1_NRF_GPIOTE0_S_BASE + 0x510)) |
          (bVar2 & 1) << 0x14;
      *(volatile unsigned short*)(iVar4 + iVar6 * 2) = uVar8 | (unsigned short)bVar3 << 0xd | 0x20;
      uVar5 = 0x0bad0000;
    }
  }
  return uVar5;
}
