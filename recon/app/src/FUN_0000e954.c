/* Reconstructed FUN_0000e954 @ 0xe954  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_0000e938(float);
float FUN_0000e954(float* param_1){
    int r0i = FUN_0000e938(param_1[0]);
    float fVar3; int cnt;
    if (r0i == 0){
        fVar3 = param_1[0]; cnt = 2;
    } else {
        r0i = FUN_0000e938(param_1[1]);
        if (r0i != 0){
            r0i = FUN_0000e938(param_1[2]);
            if (r0i == 0) return param_1[2];
            return param_1[0];
        }
        fVar3 = param_1[1]; cnt = 3;
    }
    unsigned r2 = (unsigned)cnt + 0x40000000u - 1u;
    float* p = (float*)((unsigned)(uintptr_t)param_1 + (r2 << 2));
    while (1){
        float fVar4 = *p;
        p = p + 1;
        fVar3 = (fVar4 > fVar3) ? fVar4 : fVar3;
        if (cnt != 2) break;
        cnt = 3;
    }
    return fVar3;
}

