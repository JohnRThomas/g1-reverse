/* Reconstructed FUN_0003271c @ 0x3271c  (parity: 300/300 trials, PROVEN) */
extern int FUN_0002ead8(void);
extern void FUN_0002eaa8(void);
extern void FUN_00074844(int,int);
#ifdef G1_APP_SDK_INLINE_COHESION
#include <stdint.h>
extern int64_t z_impl_k_uptime_ticks(void);
/* Exact configured kernel.h/time_units.h owner: floor(ticks * 1000 / 32768). */
static __attribute__((always_inline)) inline int g1_sdk_uptime_get_4(void)
{
    return (int)(((uint64_t)z_impl_k_uptime_ticks() * 1000u) >> 15);
}
#else
extern int FUN_0007d12e(void); /* k_uptime_get_4 @ 0x0007d12e */
#define g1_sdk_uptime_get_4() FUN_0007d12e()
#endif
void FUN_0003271c(void){
    unsigned uVar5 = 0;
    do {
        int iVar4 = FUN_0002ead8();
        if (iVar4 == 0){ uVar5 = uVar5 & 0xff; break; }
        FUN_0002eaa8();
        uVar5 = uVar5 + 1;
        FUN_00074844(0x290, 0);
    } while (uVar5 != 10);
    int iVar4 = g1_sdk_uptime_get_4();
    if (999 < (unsigned)(iVar4 - *(volatile int*)0x20007bf0UL)){
        *(volatile int*)0x20007bf0UL = iVar4;
        if (uVar5 == 10){
            unsigned char bVar1 = *(volatile unsigned char*)0x20019ef0UL;
            *(volatile unsigned char*)0x20019ef0UL = bVar1 + 1;
            if (3 < (unsigned char)(bVar1 + 1)){
                *(volatile unsigned char*)0x20003031UL = 0;
                *(volatile unsigned char*)0x20019ef0UL = 3;
                return;
            }
        } else {
            *(volatile unsigned char*)0x20019ef0UL = 0;
        }
        *(volatile unsigned char*)0x20003031UL = 1;
    }
}
