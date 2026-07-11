/* Reconstructed FUN_0005f24c @ 0x5f24c  (parity: 60/60 trials, PROVEN) */
#include <stdint.h>
extern void FUN_0007e2fa(unsigned int,...);
extern void FUN_0007e2ec(unsigned int,...);
extern void FUN_00086518(int,int);
typedef void (*release_fn_t)(int object);

void FUN_0005f24c(int param_1){
  const uintptr_t class_table = 0x20003a7c;
  unsigned char refs;
  int next;
  release_fn_t release;
  if(param_1==0){
    FUN_0007e2fa(0x00099cbd,0x000f45be,0x000f539a,0x1d3);
    FUN_0007e2ec(0x000f539a,0x1d3);
    FUN_00086518(0x20003a7c, 0);
    return;
  }
  do{
    next=*(int*)(param_1+4);
    refs=(unsigned char)(*(unsigned char*)(param_1+8)-1);
    *(unsigned char*)(param_1+8)=refs;
    if(refs!=0) return;
    if(*(int*)(param_1+0x14)!=0){
      if((*(unsigned char*)(param_1+9)&1)==0){
        uintptr_t ops=*(uintptr_t*)((unsigned int)*(unsigned char*)(param_1+10)*0x34+class_table+0x2c);
        release=*(release_fn_t*)(ops+8);
        release(param_1);
      }
      *(int*)(param_1+0x14)=0;
    }
    *(int*)(param_1+0xc)=0;
    *(int*)(param_1+4)=0;
    release=*(release_fn_t*)((unsigned int)*(unsigned char*)(param_1+10)*0x34+class_table+0x28);
    if(release==0) FUN_00086518((int)((unsigned int)*(unsigned char*)(param_1+10)*0x34+class_table),param_1);
    else release(param_1);
    param_1=next;
  }while(next!=0);
}
