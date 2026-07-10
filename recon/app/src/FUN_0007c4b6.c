/* Reconstructed FUN_0007c4b6 @ 0x7c4b6  (parity: 300/300 trials, PROVEN) */
extern void FUN_0007c430(unsigned char *a0, unsigned int a1, void *a2);
extern void FUN_0007c48a(unsigned char *a0, void *a1);
extern void FUN_0007c456(unsigned char *a0, void *a1);

unsigned int FUN_0007c4b6(unsigned char *param_1)
{
    unsigned int uVar1;
    unsigned int local_20;
    unsigned char local_1c;
    unsigned int local_18;
    unsigned int uStack_14;
    local_18 = 0;
    uStack_14 = 0;
    local_20 = 0;
    local_1c = 0;
    if (param_1 == 0) {
        uVar1 = 7;
    } else {
        *param_1 = 0xc0;
        FUN_0007c430(param_1, 0, &local_20);
        FUN_0007c48a(param_1, &local_20);
        FUN_0007c456(param_1, &local_18);
        uVar1 = 0;
        *(unsigned int*)(param_1 + 0x14) = 0;
        *(unsigned int*)(param_1 + 0x18) = 0;
    }
    (void)local_1c;
    (void)uStack_14;
    return uVar1;
}

