#include "g1_app_symbols.h"
/* named: gpiote_pin_channel_get */
/* globals referenced:
//   0x20002bc0  g_gpiote_cb                  
*/
/* Reconstructed gpiote_pin_channel_get @ 0x658e8  (parity: 300/300 trials, PROVEN) */

extern unsigned long long get_pin_idx(unsigned int a);
extern int pin_in_use_by_te(void);
extern void assert_post_action(int a,int b);
extern void printk(int a,int b,int c,int d);

unsigned int gpiote_pin_channel_get(unsigned int param_1, int param_2)
{
  int iVar1;
  unsigned int uVar2;
  unsigned long long uVar3;

  if (param_2 == 0) {
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "p_channel" /*=0xf6b7d*/, "WEST_TOPDIR/modules/hal/nordic/nrfx/drivers/src/nrfx_gpiote.c" /*=0xf6b00*/, 0x265);
    assert_post_action("WEST_TOPDIR/modules/hal/nordic/nrfx/drivers/src/nrfx_gpiote.c" /*=0xf6b00*/, 0x265);
  }
  iVar1 = pin_in_use_by_te();
  uVar2 = 0x0bad0004;
  if (iVar1 != 0) {
    uVar3 = get_pin_idx(param_1);
    uVar2 = 0x0bad0000;
    unsigned int lo = (unsigned int)uVar3;
    unsigned int hi = (unsigned int)(uVar3 >> 32);
    *(volatile unsigned char*)(unsigned long)hi = (unsigned char)((*(volatile unsigned short*)(((uintptr_t)&g_gpiote_cb) /*=0x20002bc0*/ + (unsigned long)(lo+8)*2)) >> 0xd);
  }
  return uVar2;
}

