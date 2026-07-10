/* Reconstructed FUN_0003af04 @ 0x3af04  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_000167a8(void);
extern int FUN_00037060(void);
extern int FUN_000370bc(void);
extern int FUN_0003719c(void);
extern void FUN_00047b1c(void*,int);
extern void FUN_00047ba8(void);
void FUN_0003af04(uint32_t p1,uint32_t p2,uint32_t p3,uint32_t p4){
  char* pcVar3=(char*)FUN_000167a8();
  if(*(volatile int8_t*)pcVar3==2) return;
  int iVar4=FUN_000167a8();
  volatile uint8_t cVar2b=*(volatile uint8_t*)(*(volatile int*)(iVar4+0xfec)+0x64);
  (void)cVar2b;
  int cVar2=*(volatile int8_t*)0x2000496aUL;
  if(cVar2==0){ (void)FUN_00037060(); }
  else if(cVar2==1){ (void)FUN_000370bc(); }
  else if(cVar2==2){ (void)FUN_0003719c(); }
  FUN_00047b1c((void*)0,8);
  FUN_00047ba8();
}

