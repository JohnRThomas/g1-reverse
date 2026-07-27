/* Reconstructed FUN_0004e494 @ 0x4e494  (parity: 300/300 trials, PROVEN) */

extern unsigned long long FUN_0000eefe(unsigned a, unsigned b);
extern void FUN_000723b8(unsigned a, unsigned b, unsigned c, unsigned d);
extern void FUN_00072558(unsigned a);
extern void FUN_0007e2ec(unsigned a, unsigned b);
extern void FUN_0007e2fa(unsigned long, ...);

unsigned FUN_0004e494(unsigned *param_1, unsigned param_2){
    unsigned r5 = (unsigned)param_1;
    unsigned r4 = 0x000882b0UL;
    unsigned r6 = 0x00088328UL;
    for(;;){
        if (r4 <= r6){
            if (!(r4 < r6)) break;
        } else {
            FUN_0007e2fa(0x00099cbd,0x000f1158,0x000f1126,0x2b);
            FUN_0007e2fa(0x000f0d20,0,0,0);
            FUN_0007e2ec(0x000f1126,0x2b);
        }
        unsigned long long uv = FUN_0000eefe(*(volatile unsigned*)r5, *(volatile unsigned*)r4);
        param_2 = (unsigned)(uv>>32);
        if ((unsigned)uv == 0) return 0xffffffefU;
        r4 += 0x14;
    }
    FUN_000723b8(0x20003868, param_2, 0xffffffffU, 0xffffffffU);
    volatile unsigned *piVar2 = (volatile unsigned*)0x2000a10c;
    unsigned r4b = piVar2[0];
    unsigned r4res;
    for(;;){
        if (r4b == 0){
            *(volatile unsigned*)(r5+0x14) = 0;
            unsigned r2 = piVar2[1];
            unsigned r3 = r5 + 0x14;
            if (r2 != 0){
                *(volatile unsigned*)r2 = r3;
                piVar2[1] = r3;
            } else {
                piVar2[0] = r3;
                piVar2[1] = r3;
            }
            r4res = 0;
            goto unlock;
        }
        unsigned long long uv2 = FUN_0000eefe(*(volatile unsigned*)r5, *(volatile unsigned*)(r4b-0x14));
        if ((unsigned)uv2 == 0){ r4res = 0xffffffefU; goto unlock; }
        r4b = *(volatile unsigned*)r4b;
    }
unlock:
    FUN_00072558(0x20003868);
    return r4res;
}

