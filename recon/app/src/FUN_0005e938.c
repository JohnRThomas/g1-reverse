/* Reconstructed FUN_0005e938 @ 0x5e938  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_0007e2ec(int,int);
extern void FUN_0007e2fa(unsigned long, ...);
extern int FUN_00086be4(int,int,int);
unsigned char *FUN_0005e938(uint32_t param_1, int param_2){
  unsigned char *pbVar1 = (unsigned char*)0x2000af4cUL;
  int iVar2;
  if(param_2==0){
    FUN_0007e2fa(0x00099cbd, 0x000f52ac, 0x000f5268, 0x11a);
    FUN_0007e2ec(0x000f5268, 0x11a);
    return (unsigned char *)0x5c;
  }
  if((uint32_t)*(volatile uint8_t*)pbVar1 != param_1 ||
     FUN_00086be4((int)(pbVar1+1), param_2, 7) != 0){
    if((uint32_t)*(volatile uint8_t*)(pbVar1+0x5c) != param_1 ||
       FUN_00086be4(0x2000afa9, param_2, 7) != 0){
      return (unsigned char*)0;
    }
    iVar2 = 1;
  } else {
    iVar2 = 0;
  }
  return pbVar1 + iVar2*0x5c;
}
