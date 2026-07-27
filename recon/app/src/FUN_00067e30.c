/* Full reconstruction FUN_00067e30 @ 0x67e30, exact extent 70 bytes. */
#include <stdint.h>
extern void FUN_0007e2fa(unsigned long, ...);
extern __attribute__((noreturn)) void FUN_0007e2ec(uintptr_t,uint32_t);
void FUN_00067e30(uintptr_t *device,uint32_t a,uint32_t b,uint32_t context){
 (void)a;(void)b;uint32_t ch=((uint8_t*)device)[4];volatile uint8_t *s=(volatile uint8_t*)(0x2000b41cu+ch*8u);
 if(s[1]==0){FUN_0007e2fa(0x00099cbdu,0x000f7a1bu,0x000f79c8u,0x8c,context);FUN_0007e2ec(0x000f79c8u,0x8c);}
 if(s[0]==1){*(volatile uint32_t*)*device=1;s[0]=2;return;}
 FUN_0007e2fa(0x00099cbdu,0x000f7052u,0x000f79c8u,0x8d,context);FUN_0007e2ec(0x000f79c8u,0x8d);
}
