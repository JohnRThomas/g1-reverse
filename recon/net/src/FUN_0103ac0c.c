/* net-core FUN_0103ac0c @ 0x103ac0c  (parity 300 trials PROVEN) */

int FUN_0103ac0c(unsigned int param_1, unsigned short param_2, unsigned int param_3, int *param_4, unsigned int param_5, unsigned int param_6, unsigned int *param_7)
{
    unsigned short uVar1;
    unsigned int uVar3;
    int iVar4, iVar2, iVar5;
    char *p = (char *)param_7;

    *(volatile unsigned int *)(p + 0) = param_1;
    *(volatile unsigned int *)(p + 4) = param_3;
    *(volatile unsigned short *)(p + 8) = param_2;
    *(volatile unsigned int *)(p + 0xc) = param_5;
    uVar1 = *(unsigned short *)(param_4 + 2);
    *(volatile unsigned short *)(p + 0xa) = uVar1;
    *(volatile unsigned short *)(p + 0x24) = uVar1;
    *(volatile unsigned int *)(p + 0x10) = param_6;
    uVar3 = (unsigned int)uVar1;
    iVar4 = param_4[0];
    iVar2 = param_4[1];
    iVar5 = iVar4 + uVar3 * 0x10;
    *(volatile unsigned int *)(p + 0x14) = uVar3;
    *(volatile unsigned int *)(p + 0x18) = iVar4;
    *(volatile unsigned int *)(p + 0x1c) = iVar5;
    *(volatile unsigned int *)(p + 0x20) = (iVar5 + (uVar3 + 2) * 2 + iVar2 + 1) & -iVar2;
    return 0;
}

