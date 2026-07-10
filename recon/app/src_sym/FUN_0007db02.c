/* Reconstructed FUN_0007db02 @ 0x7db02  (parity: 300/300 trials, PROVEN) */

extern unsigned int FUN_0007dac0(void);
extern int get_device_info(void);
extern int __aeabi_ldivmod(int param_1, int param_2, int param_3, int param_4, int param_5);

void FUN_0007db02(int param_1, int param_2, int param_3, int param_4)
{
    unsigned int uVar1;
    int iVar2;
    int iVar3;

    uVar1 = FUN_0007dac0();
    if (uVar1 < 7) {
        iVar2 = get_device_info();
        iVar3 = __aeabi_ldivmod(param_1, param_2, 1000, 0, param_4);
        iVar2 = uVar1 * 0xc + iVar2;
        *(int *)(iVar2 + 0x10e2) = *(int *)(iVar2 + 0x10e2) + iVar3;
        iVar2 = get_device_info();
        *(int *)(iVar2 + 0x10ca) = *(int *)(iVar2 + 0x10ca) + iVar3;
    }
}

