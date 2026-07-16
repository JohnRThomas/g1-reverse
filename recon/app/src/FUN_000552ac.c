/* Reconstructed FUN_000552ac @ 0x552ac  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_00053d70(int,int,void*);
extern void FUN_0008104a(uint32_t,int,void*);
extern int FUN_00086be4(int,uint32_t,int);
extern void FUN_00080fba(int,int);
extern void FUN_0005f24c(int);
uint32_t FUN_000552ac(uint8_t* param_1){
  struct {
    uint32_t pad;
    int local_34[5];
    struct { uint32_t kind, site; } log;
    uint32_t tail[2];
  } frame;
  if(param_1==0){
    frame.log.kind=2; frame.log.site=0xf3733;
    FUN_0008104a(0x88150,0x1080,&frame.log);
    return 0;
  }
  int iVar1=FUN_00053d70(0x1009,0,frame.local_34);
  if(iVar1!=0){
    frame.log.kind=2; frame.log.site=0xf374c;
    FUN_0008104a(0x88150,0x1080,&frame.log);
    return 0;
  }
  int iVar2=*(volatile int*)(frame.local_34[0]+0xc)+1;
  int r=FUN_00086be4(iVar2,0xf2b47,6);
  if(r!=0){
    r=FUN_00086be4(iVar2,0xf2b41,6);
    if(r!=0){
      FUN_00080fba((int)param_1+1,iVar2);
      *param_1=0;
      FUN_0005f24c(frame.local_34[0]);
      return 1;
    }
  }
  FUN_0005f24c(frame.local_34[0]);
  return 0;
}
