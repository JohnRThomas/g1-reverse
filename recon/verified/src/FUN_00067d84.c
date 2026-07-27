/* Full reconstruction FUN_00067d84 @ 0x67d84, exact extent 102 bytes. */
#include <stdint.h>
extern uint64_t FUN_0000e244(uint32_t,uint32_t,uint32_t,uint32_t);
extern void FUN_0007e2fa(unsigned long, ...);
extern __attribute__((noreturn)) void FUN_0007e2ec(uintptr_t,uint32_t);
extern void FUN_000500ac(int32_t,uint32_t,uint32_t,uint32_t);
void FUN_00067d84(uintptr_t *device,const uint32_t *ticks){
 uint32_t upper=ticks[1]>>17;
 uint64_t scaled=FUN_0000e244(ticks[1]<<15,upper,1000,0);
 if(upper>=1000){FUN_0007e2fa(0x00099cbdu,0x000f7a03u,0x000f79c8u,0x3f);FUN_0007e2ec(0x000f79c8u,0x3f);}
 uintptr_t registers=*device;*(volatile uint32_t*)(registers+0x50c)=ticks[0];
 *(volatile uint32_t*)(registers+0x504)=(uint32_t)scaled;
 uint32_t channel=((const uint8_t*)device)[4];
 if(*(volatile uint32_t*)(0x2000b41cu+channel*8u+4)!=0){
  *(volatile uint32_t*)(registers+0x100)=0;
  FUN_000500ac((int32_t)(registers<<12)>>24,(uint32_t)(scaled>>32),channel,0);
  *(volatile uint32_t*)(registers+0x304)=1;
 }
}
