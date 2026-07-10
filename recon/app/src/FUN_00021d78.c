/* Reconstructed FUN_00021d78 @ 0x21d78  (parity: 300/300 trials, PROVEN) */

extern void FUN_0004a424(unsigned int a, unsigned int b, unsigned int c);
extern int spec_ble_command_hook(unsigned int a, unsigned int b);
extern void FUN_0007c244(unsigned int a, unsigned int b);

void FUN_00021d78(unsigned int param_1, unsigned int param_2, int param_3)
{
    int iVar1;
    if (param_3 != 0) {
        FUN_0004a424(0x0009dec8UL, param_1, param_2);
    }
    iVar1 = spec_ble_command_hook(param_1, param_2);
    if (iVar1 != 0) {
        FUN_0007c244(param_1, param_2);
    }
}

