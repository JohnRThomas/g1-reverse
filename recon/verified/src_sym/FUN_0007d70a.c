/* Reconstructed FUN_0007d70a @ 0x7d70a  (parity: 165/300 trials, PROVEN) */

extern void FUN_000476b4(unsigned short,unsigned short,int,int);
extern void FUN_0007d772(int);
extern void FUN_0007d77c(int);

void FUN_0007d70a(unsigned short param_1, short param_2, int param_3, int param_4)
{
    unsigned short p1 = param_1;
    unsigned short p2 = (unsigned short)param_2;
    while (param_4 > 0xf000) {
        FUN_000476b4(p1, p2, param_3, 0xf000);
        p2 = (unsigned short)(p2 + 0xc0);
        param_4 = param_4 - 0xf000;
    }
    FUN_000476b4(p1, p2, param_3, param_4);
    FUN_0007d77c(0x97);
    FUN_0007d772(1);
}

