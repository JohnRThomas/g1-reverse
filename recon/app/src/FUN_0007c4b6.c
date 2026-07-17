/* Reconstructed FUN_0007c4b6 @ 0x7c4b6  (parity: 300/300 trials, PROVEN) */
extern void FUN_0007c430(unsigned char *a0, unsigned int a1, void *a2);
extern void FUN_0007c48a(unsigned char *a0, void *a1);
extern void FUN_0007c456(unsigned char *a0, void *a1);

unsigned int FUN_0007c4b6(unsigned char *param_1)
{
    unsigned int uVar1;
    struct {
        unsigned int value;
        unsigned char flag;
    } header = {0};
    unsigned int state[2] = {0, 0};
    if (param_1 == 0) {
        uVar1 = 7;
    } else {
        *param_1 = 0xc0;
        FUN_0007c430(param_1, 0, &header);
        FUN_0007c48a(param_1, &header);
        FUN_0007c456(param_1, state);
        uVar1 = 0;
        *(unsigned int*)(param_1 + 0x14) = 0;
        *(unsigned int*)(param_1 + 0x18) = 0;
    }
    return uVar1;
}
