/* Reconstructed FUN_00078c44 @ 0x78c44  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t u32;
extern uint64_t FUN_00087510(u32);
static inline u32 lsr(u32 v, u32 n){ n&=0xff; return n>=32?0:v>>n; }
static inline u32 lsl(u32 v, u32 n){ n&=0xff; return n>=32?0:v<<n; }
double FUN_00078c44(int param_1){
    u32 r8 = param_1 + 0x14;
    int r6 = (int)r8 + *(int*)(param_1+0x10) * 4;
    u32 r2 = *(u32*)(uintptr_t)(r6 - 4);
    u32 r7 = (u32)(r6 - 4);
    uint64_t ret = FUN_00087510(r2);
    int r0 = (int)(u32)ret;
    u32 rhi = (u32)(ret >> 32);
    *(int*)(uintptr_t)rhi = 0x20 - r0;
    u32 r1 = 0x3ff00000;
    u32 r4, r5;
    if(r0 <= 0xa){
        u32 ip = 0xb - (u32)r0;
        u32 r3 = lsr(r2, ip);
        u32 r0v = lsl(r2, (u32)(r0 + 0x15));
        r5 = r3 | r1;
        r3 = (r8 < r7) ? *(u32*)(uintptr_t)(r6 - 8) : 0;
        r3 = lsr(r3, ip);
        r3 = r3 | r0v;
        r4 = r3;
    } else {
        u32 r3;
        if(r8 < r7){ r7 = (u32)(r6 - 8); r3 = *(u32*)(uintptr_t)(r6 - 8); }
        else { r3 = 0; }
        u32 uVar2 = (u32)r0 - 0xb;
        if(uVar2 == 0){
            r5 = r2 | r1;
            r4 = r3;
        } else {
            u32 r1b = 0x20 - uVar2;
            u32 r2v = lsl(r2, uVar2);
            u32 r4a = lsr(r3, r1b);
            u32 r3v = lsl(r3, uVar2);
            r2v = r2v | r4a;
            r5 = r2v | 0x3fc00000;
            u32 r2b = (r8 < r7) ? *(u32*)(uintptr_t)(r7 - 4) : 0;
            r5 = r5 | 0x300000;
            r2b = lsr(r2b, r1b);
            r3v = r3v | r2b;
            r4 = r3v;
        }
    }
    uint64_t bits = ((uint64_t)r5 << 32) | r4;
    union{uint64_t u; double d;}u; u.u=bits; return u.d;
}

