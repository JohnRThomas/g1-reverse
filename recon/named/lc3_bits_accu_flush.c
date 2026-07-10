/* named: lc3_bits_accu_flush */
/* Reconstructed lc3_bits_accu_flush @ 0x68908  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
static uint LSL(uint v,uint n){ n&=0xff; return n<32?(v<<n):0; }
static uint LSR(uint v,uint n){ n&=0xff; return n<32?(v>>n):0; }
void lc3_bits_accu_flush(int param_1, uint param_2, uint param_3){
  uint uVar1=*(volatile uint*)(param_1+0x20);
  uint uVar3=0x20-uVar1;
  if((int)param_3 <= (int)(0x20-uVar1)) uVar3=param_3;
  uint uVar5;
  if(uVar3==0){ uVar5=(uint)((int)uVar1>>3); }
  else {
    uint uVar4b=uVar1&0xff;
    uVar5=4;
    uVar1=0x20;
    *(volatile uint*)(param_1+0x1c)=*(volatile uint*)(param_1+0x1c) | LSL(param_2,uVar4b);
  }
  int iVar2=*(volatile int*)(param_1+0x34);
  uint uVar4=(uint)(iVar2-*(volatile int*)(param_1+0x30));
  uVar4=uVar4 & ~((uint)((int)uVar4>>0x1f));
  if((int)uVar5<=(int)uVar4) uVar4=uVar5;
  *(volatile uint*)(param_1+0x20)=uVar1+uVar4*(uint)(-8);
  if(uVar4!=0){
    *(volatile int*)(param_1+0x34)=iVar2-1;
    *(volatile char*)(iVar2-1)=(char)*(volatile uint*)(param_1+0x1c);
    while(1){
      uint uVar1b=*(volatile uint*)(param_1+0x1c);
      uVar4=uVar4-1;
      *(volatile uint*)(param_1+0x1c)=uVar1b>>8;
      if(uVar4==0) break;
      iVar2=*(volatile int*)(param_1+0x34);
      *(volatile int*)(param_1+0x34)=iVar2-1;
      *(volatile char*)(iVar2-1)=(char)(uVar1b>>8);
    }
  }
  *(volatile uint*)(param_1+0x1c)=LSR(param_2,uVar3&0xff);
  *(volatile uint*)(param_1+0x20)=param_3-uVar3;
}

