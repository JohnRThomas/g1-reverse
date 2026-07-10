/* Reconstructed FUN_0004d100 @ 0x4d100  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t u32;
extern u32 FUN_00071358(int,...);
extern void FUN_00085be8(int,int,u32);
u32 FUN_0004d100(int p1,int p2,int* p3,u32 p4,u32 p5,int p6,u32 p7,int p8){
    if(p1==0 || p6==0) return 0xffffffea;
    if(p8==0) p8 = 0x0004d059;
    if(p2 != 0){
        return FUN_00071358(p1+0xe0, p5, p8, p4, 0);
    }
    FUN_00085be8(p1+0x19c, p6, p7);
    return FUN_00071358(p1+0xe0, p5, p8, p4, p1+0x19c, 0);
}

