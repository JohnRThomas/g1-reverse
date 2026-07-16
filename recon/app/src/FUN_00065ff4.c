/* Full reconstruction FUN_00065ff4 @ 0x65ff4, exact extent 72 bytes. */
#include <stdint.h>
extern void FUN_0007e2fa(uintptr_t,uintptr_t,uintptr_t,uint32_t,...);
extern __attribute__((noreturn)) void FUN_0007e2ec(uintptr_t,uint32_t);
uintptr_t FUN_00065ff4(uint32_t *descriptor,uint32_t a,uint32_t b,uint32_t context){
 (void)a;(void)b; uint32_t v=*descriptor,bit,idx=v&31; uintptr_t base;
 if((v>>5)==0){bit=UINT32_MAX>>((uint8_t)v);base=0x50842500u;}
 else if((v>>5)==1){v=idx;bit=0xffffu>>idx;base=0x50842800u;}
 else goto invalid;
 if(bit&1){*descriptor=v;return base;}
invalid:FUN_0007e2fa(0x00099cbdu,0x000f0a04u,0x000f09d1u,0x32f,context);FUN_0007e2ec(0x000f09d1u,0x32f);
}
