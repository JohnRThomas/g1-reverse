/* named: FUN_0007f894 */
/* Reconstructed FUN_0007f894 @ 0x7f894  (parity: 300/300 trials, PROVEN) */

typedef unsigned int (*fp5_t)(unsigned int, unsigned int*, unsigned int, unsigned int, unsigned int);

unsigned int FUN_0007f894(unsigned int param_1, unsigned int param_2, unsigned short *param_3, unsigned int param_4)
{
    unsigned int uVar1 = 0;
    unsigned int local_c = 0;
    fp5_t fp = *(fp5_t volatile*)(param_2 + 0x1cUL);
    if (fp != 0) {
        int bVar2 = (param_4 == 4);
        if (bVar2) {
            local_c = (unsigned int)param_3[0];
            param_4 = (unsigned int)param_3[1];
        } else {
            uVar1 = 0xffffffea;
        }
        if (bVar2) {
            local_c = (local_c & 0xffff) | ((param_4 & 0xffff) << 16);
        }
        fp(param_2 - 8, &local_c, uVar1, param_4, param_1);
    }
    return 1;
}

