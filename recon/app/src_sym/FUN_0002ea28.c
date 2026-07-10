/* Reconstructed FUN_0002ea28 @ 0x2ea28  (parity: 300/300 trials, PROVEN) */

extern int FUN_0000e2b4(void*, int);
extern int FUN_0002e988(int, void*, void*, void*);
extern unsigned long long k_uptime_get_3(void);
extern void FUN_0007cef6(int, int, void*);

int FUN_0002ea28(int param_1)
{
    int local_20 = 0, uStack_1c = 0, local_18 = 0;
    unsigned char auStack_28[8];
    int iVar1;
    iVar1 = FUN_0002e988(param_1, &local_20, &uStack_1c, &local_18);
    if (iVar1 >= 0) {
        FUN_0007cef6(param_1, 0x39, auStack_28);
        iVar1 = FUN_0000e2b4(&local_20, 0);
        if (iVar1 >= 0) {
            unsigned long long uVar2 = k_uptime_get_3();
            *(volatile unsigned long long*)0x20004790UL = uVar2;
            iVar1 = 0;
        }
    }
    return iVar1;
}

