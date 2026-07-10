/* named: strcmp */
/* Reconstructed strcmp @ 0xeefe  (parity: 300/300 trials, PROVEN) */

int strcmp(unsigned char *param_1, unsigned char *param_2)
{
    unsigned int uVar2;
    unsigned char bVar1;
    int bVar3;
    do {
        uVar2 = *param_1;
        bVar1 = *param_2;
        bVar3 = (uVar2 == 1);
        if (uVar2 != 0) {
            bVar3 = (uVar2 == bVar1);
        }
        param_1 = param_1 + 1;
        param_2 = param_2 + 1;
    } while (bVar3);
    return (int)uVar2 - (int)bVar1;
}

