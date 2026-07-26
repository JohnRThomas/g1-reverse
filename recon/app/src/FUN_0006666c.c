/* Reconstructed FUN_0006666c @ 0x6666c  (parity: 300/300 trials, PROVEN) */
#include "../../headers/g1_nrf_regs.h"
extern void FUN_0007e2fa(unsigned,unsigned,unsigned,unsigned,unsigned);
extern long long FUN_0007e2ec(unsigned,unsigned);
void FUN_0006666c(unsigned param_1, int param_2, unsigned param_3, unsigned param_4){
    unsigned r0v = param_1;
    unsigned r1v = (unsigned)param_2;
    unsigned uVar2; int iVar1;
    if ((param_1 >> 5) == 0) goto L_68e;
    if ((param_1 >> 5) == 1) goto L_6b4;
L_676:
    FUN_0007e2fa(0x99cbd,0xf0a04,0xf09d1,0x32f,param_4);
    { long long r = FUN_0007e2ec(0xf09d1,0x32f);
      r0v = (unsigned)r; r1v = (unsigned)((unsigned long long)r >> 32); }
L_68e:
    { unsigned s = r0v & 0xff; uVar2 = (s >= 32) ? 0u : (0xffffffffu >> s); }
    iVar1 = G1_NRF_P0_S_BASE;
    if ((int)(uVar2 << 0x1f) >= 0) goto L_676;
    goto L_join;
L_6b4:
    r0v = param_1 & 0x1f;
    uVar2 = 0xffffu >> r0v;
    iVar1 = G1_NRF_P1_S_BASE;
    if ((int)(uVar2 << 0x1f) >= 0) goto L_676;
L_join:
    {
        volatile unsigned* addr = (volatile unsigned*)(iVar1 + (r0v << 2) + 0x200);
        *addr = (*addr & 0xfffcf0f0) | (r1v << 8) | 2;
    }
}

