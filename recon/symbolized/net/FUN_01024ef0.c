#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01024ef0 @ 0x01024ef0
 * public-name: FUN_01024ef0
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_radio_timer_sync_state             @ 0x21001bf8
 */
/* net-core FUN_01024ef0 @ 0x1024ef0  (parity 300 trials PROVEN) */
#include <stdint.h>
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"

#define PC6 ((unsigned long)&g_net_radio_timer_sync_state) /*=0x21001bf8*/
#define NP  0x41011000u
#define CC  0x4100c000u
#define FF  0x4100f000u

static inline u32 RW(u32 a){return *(volatile u32*)a;}
static inline void WW(u32 a,u32 v){*(volatile u32*)a=v;}
static inline u8 RB(u32 a){return *(volatile u8*)a;}
static inline void WB(u32 a,u8 v){*(volatile u8*)a=v;}
static inline void WH(u32 a,u16 v){*(volatile u16*)a=v;}

extern void FUN_010256dc(unsigned,unsigned,unsigned,unsigned);
extern void FUN_01024c6c(void);

void FUN_01024ef0(void)
{
  u8 cVar1 = RB(PC6);
  if (cVar1 == 0) {
    WW(NP+0x348,0x30000);
    WW(NP+0x308,0x30000);
    WW(NP+0x140,0);
    FUN_010256dc(0x6c,0x337,NP,cVar1);
    __builtin_unreachable();
  }
  WW(NP+0x348,0x20000);
  WW(NP+0x308,0x20000);
  if (cVar1 != 2) {
    FUN_010256dc(0x6c,0x337,NP,cVar1);
    __builtin_unreachable();
  }

  u32 primask = __get_PRIMASK();
  __disable_irq();

  u32 r0 = RW(NP+0x504);
  u32 r3 = RW(NP+0x104);
  if (r3 != 0) {
    do {
      WW(PC6+0x10, RW(PC6+0x10)+1);
      WW(NP+0x104,0);
      r0 = RW(NP+0x504);
      r3 = RW(NP+0x104);
    } while (r3 != 0);
  }
  u32 r2 = RW(PC6+0x10);

  if (primask == 0) {
    __enable_irq();
  }

  u32 r5 = 0x1000000u;
  unsigned long long acc = 3ull + (unsigned long long)r2 * (unsigned long long)r5;
  u32 lo = (u32)acc;
  u32 hi = (u32)(acc >> 32);
  unsigned long long addres = (unsigned long long)lo + (unsigned long long)r0;
  u32 r0b = (u32)addres;
  u32 carry = (u32)(addres >> 32) & 1u;
  u32 r1 = hi + carry;

  u32 r5b = RW(PC6+8);
  u32 r7b = RW(PC6+0xc);

  u32 r3f;
  if (r7b == r1 && r5b == r0b) {
    r3f = r0b;
    goto L_9a;
  }
  r3f = r5b;
  {
    u32 t2 = RW(NP+0x504);
    u32 diffr2 = r5b - t2;
    u32 maskr6 = diffr2 & 0x00fffffcu;
    if (maskr6 == 0) {
      goto L_9a;
    }
    u32 bicv = diffr2 & 0x00ffffffu;
    if (bicv > 0x800000u) {
      goto L_9a;
    }
    FUN_01024c6c();
    WW(CC+0x200, RW(PC6+0x1c));
    return;
  }
L_9a:;
  {
    u32 t0 = RW(NP+0x504);
    u32 r3c = r3f - t0;
    u32 r2c = r3c & 0x00fffffeu;
    if (r2c != 0) {
      u32 bicv2 = r3c & 0x00ffffffu;
      if (bicv2 <= 0x800000u) {
        goto L_9c8;
      }
    }
    WW(PC6+0x1c, 1);
    WB(PC6+2, 0);
    WW(CC+0x200, 1);
    return;
  }
L_9c8:
  WW(PC6+8, r5b);
  WW(PC6+0xc, r7b);
  WW(FF+0x508, 2);
  WW(PC6+0x1c, 1);
  WB(PC6+2, 0);
  WW(CC+4, 1);
  WW(CC+0xc, 1);
  WW(NP+0x1c0, 0x80000002u);
  WW(CC+0x80, 0x80000002u);
  WW(FF+0x504, 4);
  WH(PC6, 0x401);
  WW(CC+0x200, 1);
  return;
}
