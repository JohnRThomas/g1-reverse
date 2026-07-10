/* Reconstructed FUN_00076718 @ 0x76718  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern float FUN_00076538(float);
static inline int fbits(float f){ union{float f;int i;}u; u.f=f; return u.i; }
static inline float mkf(int b){ union{int i;float f;}u; u.i=b; return u.f; }
float FUN_00076718(float param_1){
    int r3 = fbits(param_1);
    int r2 = r3 & 0x7fffffff;
    float s14;
    if(r2 != 0){
        if(r3 >= 0){
            if(r3 >= 0x7f800000) return param_1 + param_1;
            int iVar2;
            if(r3 < 0x800000){
                iVar2 = -0x19;
                param_1 = param_1 * mkf(0x4c000000);
                r2 = fbits(param_1);
            } else {
                iVar2 = 0;
                r2 = r3;
            }
            int e = (r2 >> 0x17) - 0x7f + iVar2;
            int r1 = (int)((unsigned)e >> 0x1f);
            int emant = e + (int)((unsigned)e >> 31);
            float fVar4 = (float)emant;
            int mant = r2 & 0x7fffff;
            int expo = 0x7f - r1;
            float x = mkf(mant | (expo << 23));
            float fVar3 = FUN_00076538(x);
            float result = fVar3 * mkf(0x3ede5bd9);
            result = __builtin_fmaf(fVar4, mkf(0x355427db), result);
            result = __builtin_fmaf(fVar4, mkf(0x3e9a2080), result);
            return result;
        } else {
            s14 = param_1 - param_1;
        }
    } else {
        s14 = mkf(0xcc000000);
    }
    return s14 / mkf(0x00000000);
}

