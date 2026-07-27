/* Reconstructed FUN_00067548 @ 0x67548  (parity: 300/300 trials, PROVEN) */
#include "../../headers/g1_nrf_regs.h"
extern void FUN_0007e2fa(unsigned long, ...);
extern long long FUN_0007e2ec(unsigned,unsigned);
void FUN_00067548(unsigned param_1, unsigned param_2, unsigned param_3, unsigned param_4){
    unsigned r0v=param_1, r1v=param_2, r2v=param_3, r3v=param_4;
    unsigned uVar2; int iVar1;
    if ((param_1 >> 5) == 0) goto L_6a;
    if ((param_1 >> 5) == 1) goto L_94;
L_52:
    FUN_0007e2fa(0x99cbd,0xf0a04,0xf09d1,0x32f);
    r2v = 0xf09d1; r3v = 0x32f;
    { long long r=FUN_0007e2ec(0xf09d1,0x32f); r0v=(unsigned)r; r1v=(unsigned)((unsigned long long)r>>32); }
L_6a:
    { unsigned s=r0v & 0xff; uVar2=(s>=32)?0u:(0xffffffffu>>s); }
    iVar1 = G1_NRF_P0_S_BASE;
    if ((int)(uVar2<<0x1f) >= 0) goto L_52;
    goto L_join;
L_94:
    r0v = param_1 & 0x1f;
    uVar2 = 0xffffu >> r0v;
    iVar1 = G1_NRF_P1_S_BASE;
    if ((int)(uVar2<<0x1f) >= 0) goto L_52;
L_join:
    {
        volatile unsigned* addr = (volatile unsigned*)(iVar1 + (r0v<<2) + 0x200);
        *addr = (r3v<<8) | (r2v<<2) | (r1v<<1) | (0xfffcf0f0 & *addr);
    }
}

