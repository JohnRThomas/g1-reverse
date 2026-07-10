#include "g1_app_symbols.h"
/* named: gpiote_trigger_enable */
/* globals referenced:
//   0x20002bc0  g_gpiote_cb                  
*/
/* Reconstructed gpiote_trigger_enable @ 0x657e4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned long long u64;
extern u64 get_pin_idx(void);
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
  unsigned char local_19[5];
  uVar9 = get_pin_idx();
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
    local_19[0] = 1;
    gpio_pin_cnf_build_fields(param_1, local_19, iVar4 + 1, iVar4 + 2, iVar4, 0);
    iVar4 = (int)uVar9 + 8;
    *(volatile unsigned short*)(((uintptr_t)&g_gpiote_cb) /*=0x20002bc0*/ + iVar4 * 2) =
        *(volatile unsigned short*)(((uintptr_t)&g_gpiote_cb) /*=0x20002bc0*/ + iVar4 * 2) | 3;
  }
  uVar5 = 0x0bad0000;
  if ((param_3 != 0) &&
      (iVar6 = pin_is_output(param_1), iVar4 = ((uintptr_t)&g_gpiote_cb) /*=0x20002bc0*/, uVar5 = 0x0bad0004, iVar6 != 0)) {
    bVar3 = *param_3;
    iVar6 = (int)uVar9 + 8;
    iVar7 = (unsigned)bVar3 * 4;
    uVar8 = *(volatile unsigned short*)(((uintptr_t)&g_gpiote_cb) /*=0x20002bc0*/ + iVar6 * 2) & 0x1fdf;
    *(volatile unsigned*)(iVar7 + REG_5000d510 /*=0x5000d510*/) = 0;
    *(volatile unsigned short*)(iVar4 + iVar6 * 2) = uVar8;
    *(volatile unsigned*)(iVar7 + REG_5000d510 /*=0x5000d510*/) = 0;
    bVar1 = param_3[1];
    uVar5 = 0x0bad0000;
    if (bVar1 != 0) {
      bVar2 = param_3[2];
      *(volatile unsigned*)(iVar7 + REG_5000d510 /*=0x5000d510*/) = *(volatile unsigned*)(iVar7 + REG_5000d510 /*=0x5000d510*/) & 0xffecc0ff;
      *(volatile unsigned*)(iVar7 + REG_5000d510 /*=0x5000d510*/) =
          (param_1 & 0x3f) << 8 | (bVar1 & 3) << 0x10 | *(volatile unsigned*)(iVar7 + REG_5000d510 /*=0x5000d510*/) |
          (bVar2 & 1) << 0x14;
      *(volatile unsigned short*)(iVar4 + iVar6 * 2) = uVar8 | (unsigned short)bVar3 << 0xd | 0x20;
      uVar5 = 0x0bad0000;
    }
  }
  return uVar5;
}

