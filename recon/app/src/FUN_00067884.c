/* Full reconstruction FUN_00067884 @ 0x67884, exact extent 60 bytes. */
#include <stdint.h>
extern void FUN_0007e2fa(unsigned long, ...);
extern __attribute__((noreturn)) void FUN_0007e2ec(uintptr_t,uint32_t);
void FUN_00067884(uintptr_t *device,uint32_t a,uint32_t b,uint32_t context){
 (void)a;(void)b; uint8_t channel=((uint8_t*)device)[4]; volatile uint8_t *state=(volatile uint8_t*)(0x2000b3ccu+channel*40u);
 if(state[0x22]!=1){FUN_0007e2fa(0x00099cbdu,0x000f7052u,0x000f6fefu,0x16b,context);FUN_0007e2ec(0x000f6fefu,0x16b);}
 *(volatile uint32_t*)(*device+0x500)=6;state[0x22]=2;
}
