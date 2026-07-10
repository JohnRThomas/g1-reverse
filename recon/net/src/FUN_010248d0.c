/* net-core FUN_010248d0 @ 0x10248d0  (parity 300 trials PROVEN) */

extern int FUN_01024b20(unsigned int);
#define DAT_010248e4 ((unsigned int)0x21001bd0)

void FUN_010248d0(void)
{
    unsigned int iVar1 = DAT_010248e4;
    int iVar2;
    do {
        iVar2 = FUN_01024b20(*(volatile unsigned int *)(iVar1 + 0x20) & 3);
    } while (iVar2 == 0);
    return;
}

