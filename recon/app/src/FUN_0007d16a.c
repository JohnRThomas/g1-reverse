/* Reconstructed FUN_0007d16a @ 0x7d16a  (parity: 300/300 trials, PROVEN) */

int FUN_0007d16a(int *param_1, unsigned char *param_2)
{
    if (param_1 == 0 || param_2 == 0) {
        return -1;
    }
    char cVar2 = 0;
    unsigned char bVar1 = *param_2;
    int iVar4;
    for (iVar4 = 0; iVar4 < (int)(unsigned int)bVar1; iVar4++) {
        cVar2 = cVar2 + *(char*)(*param_1 + iVar4);
    }
    *(char*)(*param_1 + (unsigned int)bVar1) = cVar2;
    *param_2 = bVar1 + 1;
    return 0;
}

