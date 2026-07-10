/* Reconstructed FUN_0008629e @ 0x8629e  (parity: 300/300 trials, PROVEN) */

extern void FUN_000861c2(int a, int b);
extern int FUN_00086208(int a, int b, void *c);

unsigned int FUN_0008629e(int param_1, unsigned char *param_2, unsigned int param_3)
{
    unsigned int uVar1;
    unsigned char *pbVar3;
    unsigned char *outp;

    if (param_3 < 9) {
        unsigned char buf[8];
        pbVar3 = param_2 + param_3;
        outp = param_2;
        if ((signed char)pbVar3[-1] < 0) {
            unsigned char *src = param_2;
            unsigned char *dst = buf;
            while (src != pbVar3) {
                *dst = (unsigned char)~(*src);
                dst++;
                src++;
            }
            uVar1 = 1;
            outp = buf;
        } else {
            uVar1 = 0;
        }
        if (param_3 != 0) {
            uVar1 = FUN_00086208(param_1, uVar1, outp);
            return uVar1;
        }
        uVar1 = 0xe;
    } else {
        uVar1 = 5;
    }
    FUN_000861c2(param_1, uVar1);
    return 0;
}

