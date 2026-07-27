/* Reconstructed FUN_00036558 @ 0x36558  (parity: 300/300 trials, PROVEN) */

extern int FUN_00076d6c(int);
extern void FUN_00086c78(int,int,int);
extern void DEBUG_PRINT(unsigned long, ...);
void FUN_00036558(int param_1,int param_2,int param_3,int param_4){
  if(*(volatile int*)0x20009fccUL==0){
    int iVar4=FUN_00076d6c(0x140);
    *(volatile int*)0x20009fccUL=iVar4;
    if(iVar4==0){ DEBUG_PRINT(0xa8d69,0xa8e48,0x28,param_4); return; }
    FUN_00086c78(iVar4,0,0x140);
  }
  unsigned uVar5=0;
  do{
    int iVar4=*(volatile int*)0x20009fc4UL;
    if(param_2<=iVar4) return;
    *(volatile int*)0x20009fc4UL=iVar4+2;
    unsigned uVar7=((unsigned)param_1<<(uVar5&0xff))&0xc0;
    unsigned char uVar6=(unsigned char)uVar7;
    if(uVar7==0xc0) uVar6=0xff;
    else if(uVar7==0x80) uVar6=0xf0;
    else if(uVar7==0x40) uVar6=0xf;
    else if(uVar7!=0) uVar6=0x99;
    *(volatile unsigned char*)((unsigned)(*(volatile int*)0x20009fccUL)+(unsigned)(*(volatile int*)0x20009fc8UL))=uVar6;
    uVar5+=2;
    *(volatile int*)0x20009fc8UL=(*(volatile int*)0x20009fc8UL)+1;
  }while(uVar5!=8);
}

