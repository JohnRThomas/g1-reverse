/* Reconstructed FUN_0005e83c @ 0x5e83c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
extern void FUN_0007e2ec(uint,int);
extern void FUN_0007e2fa(unsigned long, ...);
extern int FUN_00080ca0(uint,void*);
extern int FUN_00086be4(void*,uint,int);
uint8_t* FUN_0005e83c(uint param_1, uint8_t* param_2, uint param_3, uint param_4){
    volatile uint8_t* r4=(volatile uint8_t*)0x2000af4c;
    int r3int; uint8_t* r7;
    if(param_2==0){
        FUN_0007e2fa(0x00099cbdu,0x000f52acu,0x000f5268u,0xe9u);
        FUN_0007e2ec(0x000f5268u,0xe9);
    }
    if(*(volatile uint8_t*)param_2 != 1) return 0;
    if((param_2[6]&0xc0) != 0x40) return 0;
    if(((uint)*(volatile uint16_t*)(r4+0xe)<<0x1e)&0x80000000u) goto L894;
    if(!(((uint)*(volatile uint16_t*)(r4+0x6a)<<0x1e)&0x80000000u)) return 0;
    if((uint)*(volatile uint8_t*)(r4+0x5c) != param_1) goto L8aa;
    if(FUN_00086be4(param_2+1,0x2000af4c+0x96,6)!=0) goto L8a2;
    goto L8fe;
L894:
    if((uint)*(volatile uint8_t*)r4 == param_1) goto L8d4;
    if(((uint)*(volatile uint16_t*)(r4+0x6a)<<0x1e)&0x80000000u) goto L8ea;
L8a2:
    if(!(((uint)*(volatile uint16_t*)(r4+0x6a)<<0x1e)&0x80000000u)) return 0;
L8aa:
    if((uint)*(volatile uint8_t*)(r4+0x5c) != param_1) return 0;
    r7=param_2+1;
    if(FUN_00080ca0(0x2000afd2,r7)==0) return 0;
    r3int=0x5c;
L8c2:
    {
        uint32_t v=*(volatile uint32_t*)r7;
        *(volatile uint32_t*)((int)r4+r3int+0x3a)=v;
        uint16_t h=*(volatile uint16_t*)(r7+4);
        uint8_t* ret=(uint8_t*)((int)r4+r3int);
        *(volatile uint16_t*)((int)r4+r3int+0x3e)=h;
        return ret;
    }
L8d4:
    if(FUN_00086be4(param_2+1,0x2000af4c+0x3a,6)==0) return (uint8_t*)((int)r4+0);
    if(!(((uint)*(volatile uint16_t*)(r4+0x6a)<<0x1e)&0x80000000u)) goto L904;
L8ea:
    if((uint)*(volatile uint8_t*)(r4+0x5c) != param_1) goto L904;
    if(FUN_00086be4(param_2+1,0x2000afe2,6)!=0) goto L904;
L8fe:
    return (uint8_t*)((int)r4+0x5c);
L904:
    if((uint)*(volatile uint8_t*)r4 != param_1) goto L8a2;
    r7=param_2+1;
    if(FUN_00080ca0(0x2000af76,r7)==0) goto L8a2;
    r3int=0;
    goto L8c2;
}
