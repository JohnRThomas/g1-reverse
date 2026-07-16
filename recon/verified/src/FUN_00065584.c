/* Full reconstruction FUN_00065584 @ 0x65584, exact extent 80 bytes. */
#include <stdint.h>
extern uint64_t FUN_000850f6(uint32_t,void*,uint32_t,uint32_t,uint32_t);
extern void FUN_0007e2fa(uintptr_t,uintptr_t,uintptr_t,uint32_t,...);
extern __attribute__((noreturn)) void FUN_0007e2ec(uintptr_t,uint32_t);
uintptr_t FUN_00065584(uint32_t *descriptor,uint32_t a,uint32_t b,uint32_t context){
 (void)a;(void)b; uint32_t encoded=*descriptor;
 uint64_t slot=FUN_000850f6(encoded,descriptor,encoded,context,context);
 if((uint32_t)slot==0){FUN_0007e2fa(0x00099cbdu,0x000f0a04u,0x000f09d1u,0x32f);FUN_0007e2ec(0x000f09d1u,0x32f);}
 *(uint32_t*)(uintptr_t)(slot>>32)=encoded&0x1f;
 if((encoded>>5)==0)return 0x50842500u;
 if((encoded>>5)==1)return 0x50842800u;
 FUN_0007e2fa(0x00099cbdu,0x000f7a30u,0x000f09d1u,0x338);FUN_0007e2ec(0x000f09d1u,0x338);
}
