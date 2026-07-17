#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010313a8 @ 0x010313a8
 * public-name: z_nrf_rtc_timer_read
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   z_nrf_rtc_timer_read                     <= FUN_010313a8 @ 0x010313a8
 * address symbols (name @ address):
 *   g_sdc_rtc_wrap_limit                     @ 0x21002b88
 *   g_rtc_overflow_cnt                       @ 0x21004970
 */
/* net-core FUN_010313a8 @ 0x10313a8  (parity 300 trials PROVEN) */
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"

unsigned long long z_nrf_rtc_timer_read(void)
{
  volatile unsigned int *g1 = (volatile unsigned int*)((unsigned long)&g_rtc_overflow_cnt) /*=0x21004970*/;
  unsigned int raw = *g1;
  unsigned int hi = raw >> 8;
  unsigned int lo = raw << 24;
  __DMB();
  volatile unsigned int *g2 = (volatile unsigned int*)0x41016000;
  unsigned int uVar3 = *(volatile unsigned int*)((char*)g2 + 0x504);
  unsigned int sum = uVar3 + lo;
  int carry = sum < uVar3;
  unsigned int uVar1 = hi + carry;
  if (uVar3 < 0x100000) {
    volatile unsigned int *g3 = (volatile unsigned int*)((unsigned long)&g_sdc_rtc_wrap_limit) /*=0x21002b88*/;
    unsigned int lim0 = g3[0];
    unsigned int lim1 = g3[1];
    if (uVar1 <= lim1 && sum <= (lim0)) {
      /* actual cmp emulate: below check original odd condition */
    }
  }
  volatile unsigned int *g3b = (volatile unsigned int*)((unsigned long)&g_sdc_rtc_wrap_limit) /*=0x21002b88*/;
  unsigned int lim0 = g3b[0];
  unsigned int lim1 = g3b[1];
  unsigned int uVar2 = sum;
  if (uVar3 < 0x100000) {
    /* signed/unsigned compare per asm: cmp r0,r2; sbcs r3,r1,r3; bhs skip */
    unsigned long long a = ((unsigned long long)uVar1<<32) | uVar2;
    unsigned long long b = ((unsigned long long)lim1<<32) | lim0;
    if (a < b) {
      int bVar4 = uVar2 > 0xfeffffff;
      uVar2 = uVar2 + 0x1000000;
      uVar1 = uVar1 + bVar4;
    }
  }
  return ((unsigned long long)uVar1 << 32) | uVar2;
}
