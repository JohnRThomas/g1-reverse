/* net-core FUN_01019f34 @ 0x1019f34  (parity 300 trials PROVEN) */
extern unsigned char FUN_0100e04c(void);
extern unsigned char FUN_0100e064(int a);

void FUN_01019f34(int param_1, int param_2, unsigned int param_3)
{
    unsigned char uVar1;
    unsigned char bVar2;
    unsigned int uVar3;

    uVar1 = FUN_0100e04c();
    *(volatile unsigned char *)(param_2 + 0x11) = uVar1;
    uVar1 = FUN_0100e064(param_1);
    *(volatile unsigned char *)(param_2 + 0x12) = uVar1;

    if (param_3 == 0 || param_3 == 2 || param_3 == 4 || param_3 == 6) {
        *(volatile unsigned char *)(param_2 + 1) = 1;
        *(volatile int *)(param_2 + 4) = param_1 + 3;
        *(volatile unsigned int *)(param_2 + 8) = 0;
        bVar2 = (unsigned char)(*(char *)(param_1 + 1) - 6);
        uVar3 = (unsigned int)bVar2;
        *(volatile unsigned char *)(param_2 + 0x10) = bVar2;
        if (uVar3 != 0) {
            *(volatile int *)(param_2 + 0xc) = param_1 + 9;
            return;
        }
        *(volatile unsigned int *)(param_2 + 0xc) = uVar3;
        return;
    }
    if (param_3 == 1) {
        *(volatile unsigned char *)(param_2 + 1) = 3;
        *(volatile unsigned char *)(param_2 + 0x10) = 0;
        *(volatile unsigned int *)(param_2 + 0xc) = 0;
        *(volatile int *)(param_2 + 4) = param_1 + 3;
        *(volatile int *)(param_2 + 8) = param_1 + 9;
        return;
    }
    uVar3 = 0;
    *(volatile unsigned char *)(param_2 + 1) = 0;
    *(volatile unsigned char *)(param_2 + 0x10) = 0;
    *(volatile unsigned int *)(param_2 + 4) = 0;
    *(volatile unsigned int *)(param_2 + 8) = 0;
    *(volatile unsigned int *)(param_2 + 0xc) = uVar3;
}


