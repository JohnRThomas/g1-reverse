/* Reconstructed erase_audio_buffer @ 0x2f008  (parity: 300/300 trials, PROVEN) */

typedef int (*fn3)(int,int,int);
extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);
int erase_audio_buffer(void){
  int obj = 0x87bf0;
  fn3 f = *(volatile fn3*)((*(volatile int*)(obj+8)) + 8);
  int iVar1 = f(obj, 0x400000, 0x10000);
  if(iVar1==0){
    int iVar2 = *(volatile int*)0x2000230cUL;
    *(volatile int*)0x20002404UL = 0x400000;
    if(2 < iVar2){ if(*(volatile int*)0x20007554UL==0) DEBUG_PRINT(((unsigned long)"%s(): Flash erase ok \n\n"),((unsigned long)"erase_audio_buffer")); else FUN_00019c70(((unsigned long)"%s(): Flash erase ok \n\n"),((unsigned long)"erase_audio_buffer")); }
  } else if(0 < *(volatile int*)0x2000230cUL){
    if(*(volatile int*)0x20007554UL==0) DEBUG_PRINT(((unsigned long)"%s(): Flash erase failed! %d\n\n"),((unsigned long)"erase_audio_buffer"),iVar1); else FUN_00019c70(((unsigned long)"%s(): Flash erase failed! %d\n\n"),((unsigned long)"erase_audio_buffer"),iVar1);
  }
  return iVar1;
}
