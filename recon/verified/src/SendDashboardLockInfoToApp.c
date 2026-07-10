/* Reconstructed SendDashboardLockInfoToApp @ 0x25e2c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int DEBUG_PRINT(int,...);
extern int FUN_00019c70(void);
extern int FUN_00047b1c(void*,...);
extern int FUN_00047ba8(void);
extern int FUN_0007ca4e(int,...);
void SendDashboardLockInfoToApp(unsigned p1, unsigned p2, unsigned p3){
  volatile unsigned buf[3];
  buf[0]=p1; buf[1]=p2; buf[2]=p3;
  int iVar1 = FUN_0007ca4e(0x20007570);
  if((iVar1<<0x1e)<0){
    iVar1 = FUN_0007ca4e(0x20007aa0);
    if(-1 < (iVar1<<0x1e)){
      iVar1 = FUN_0007ca4e(0x2000756c);
      unsigned bit = (unsigned)(iVar1>>1)&1u;
      if(-1 < (iVar1<<0x1e)){
        iVar1 = FUN_0007ca4e(0x20007570);
        if((iVar1<<0x1e)<0){
          buf[0]=bit;
          *(volatile uint16_t*)&buf[0] = 0x650;
          *(volatile uint16_t*)((char*)&buf[1]) = 0x101;
          if(*(volatile int*)0x2000230c > 2){
            if(*(volatile int*)0x20007554==0){
              DEBUG_PRINT(0x9f73d,0x9fa9c,1);
            } else {
              FUN_00019c70();
            }
          }
          FUN_00047b1c((void*)buf,6);
          FUN_00047ba8();
          *(volatile uint32_t*)0x2000756c |= 2u;
        }
      }
    }
  }
}

