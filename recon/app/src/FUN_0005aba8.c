/* Reconstructed FUN_0005aba8 @ 0x5aba8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_0008016a(void*,void*,void*);
extern void FUN_00080294(void); /*unused decl replaced*/
extern int FUN_00080294_i(uint32_t,void*);
extern void FUN_000826e0(uint32_t);
extern void FUN_00082a42(uint32_t,int,void*);
extern void FUN_00082c9c(int,int,uint32_t,void*);
void FUN_0005aba8(void){
  struct {
    uint32_t header[4];
    uint8_t reserved[16];
    struct { uint32_t level, message; } log;
    uint8_t work[96];
    uint8_t scratch[176];
  } frame;
  frame.header[0]=0; frame.header[1]=0; frame.header[2]=0; frame.header[3]=0;
  int iVar2=FUN_0008016a(frame.work,frame.header,frame.scratch);
  if(iVar2!=0){
    FUN_00082c9c(1,0xffff,0x8260d,frame.work);
    iVar2=FUN_00080294_i(0x20006380,frame.work);
    if(iVar2!=0){
      volatile uint8_t* puVar3=(volatile uint8_t*)(0x20006380UL+0x10);
      volatile uint8_t* puVar4=(volatile uint8_t*)0x20006380UL;
      int i=0;
      do{
        uint8_t uVar1=*puVar4;
        puVar3=puVar3-1;
        i=i+1;
        *puVar4=*puVar3;
        *puVar3=uVar1;
        puVar4=puVar4+1;
      }while(i!=8);
      FUN_000826e0(0x20006448);
      return;
    }
  }
  frame.log.level=2;
  frame.log.message=(iVar2==0) ? 0x000f49d4 : 0x000f49ed;
  FUN_00082a42(0x88128,0x1040,&frame.log);
}
