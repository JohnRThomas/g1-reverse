/* net-core FUN_0100a50c @ 0x100a50c  (parity 300 trials PROVEN) */
extern unsigned int FUN_01027662(unsigned char a, int b, unsigned char c);
extern void FUN_010275d2(int a, unsigned short b, unsigned char c, int d, unsigned char e);

unsigned int FUN_0100a50c(int param_1, unsigned char param_2, unsigned char param_3)
{
    unsigned short uVar1 = (unsigned short)FUN_01027662(param_3, 0x2e, param_2);
    if (param_1 != 0) {
        FUN_010275d2(param_1, uVar1, param_3, 0x2e, param_2);
        *(volatile int *)0x21000bc4 = param_1;
        *(volatile unsigned char *)0x21000bc8 = param_2;
        *(volatile unsigned char *)0x21000bc9 = param_3;
    }
    return (unsigned int)uVar1 & 0xffffu;
}


