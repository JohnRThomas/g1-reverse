/* Reconstructed FUN_00059a90 @ 0x59a90  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void FUN_0007e2fa(unsigned long, ...);
extern long long FUN_0007e2ec(unsigned,unsigned);
extern int FUN_0005858c(void);
extern void FUN_000820ae(void);
unsigned FUN_00059a90(int param_1, unsigned* param_2){
    unsigned r1;
    if (param_1 != 0){
        r1 = (unsigned)(uintptr_t)param_2;
    } else {
        FUN_0007e2fa(0x99cbd,0xf3ebd,0xf4388,0xf38);
        long long r = FUN_0007e2ec(0xf4388, 0xf38);
        r1 = (unsigned)((unsigned long long)r >> 32);
    }
L_aae:
    if (r1 != 0) goto L_ac4;
    FUN_0007e2fa(0x99cbd,0xf4590,0xf4388,0xf39);
    { long long r = FUN_0007e2ec(0xf4388, 0xf39);
      r1 = (unsigned)((unsigned long long)r >> 32); }
    goto L_aae;
L_ac4:
    {
        int iVar1 = FUN_0005858c();
        if (iVar1 == 0) return 0xffffff80;
        *param_2 = 0;
        unsigned* r3 = *(unsigned**)(iVar1 + 8);
        if (r3 == 0){
            *(unsigned**)(iVar1 + 4) = param_2;
            *(unsigned**)(iVar1 + 8) = param_2;
        } else {
            *r3 = (unsigned)(uintptr_t)param_2;
            *(unsigned**)(iVar1 + 8) = param_2;
        }
        FUN_000820ae();
        return 0;
    }
}

