/* Reconstructed FUN_00076bcc @ 0x76bcc  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void FUN_00051134(uint32_t);
extern void FUN_00076b48(uint32_t,int,int);
extern void FUN_00076bb4(void);
extern uint32_t FUN_00076c3c(int);
extern void FUN_00076bc0(void);
void FUN_00076bcc(int param_1){
  FUN_00076bb4();
  if(*(volatile int*)(param_1+0x18)!=0){ FUN_00076bc0(); return; }
  *(volatile uint32_t*)(param_1+0x48)=0;
  *(volatile uint32_t*)(param_1+0x4c)=0;
  *(volatile uint32_t*)(param_1+0x50)=0;
  int iVar2=*(volatile int*)0x9873cUL;
  *(volatile uint32_t*)(param_1+0x28)=0x76b91;
  if(iVar2==param_1) *(volatile uint32_t*)(param_1+0x18)=1;
  uint32_t u;
  u=FUN_00076c3c(param_1); *(volatile uint32_t*)(param_1+4)=u;
  u=FUN_00076c3c(param_1); *(volatile uint32_t*)(param_1+8)=u;
  u=FUN_00076c3c(param_1); *(volatile uint32_t*)(param_1+0xc)=u;
  FUN_00076b48(*(volatile uint32_t*)(param_1+4),4,0);
  FUN_00076b48(*(volatile uint32_t*)(param_1+8),9,1);
  FUN_00076b48(*(volatile uint32_t*)(param_1+0xc),0x12,2);
  *(volatile uint32_t*)(param_1+0x18)=1;
  FUN_00076bc0();
}

