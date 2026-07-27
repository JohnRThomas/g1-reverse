/* Reconstructed uint32_to_little_endian @ 0x4a568  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);

unsigned int uint32_to_little_endian(unsigned char *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned int uVar1;
    if (param_1 == 0) {
        if (*(volatile int*)0x2000230cUL > 1) {
            unsigned int sink=*(volatile unsigned int*)0x20007554UL;
            if (sink == 0) {
                DEBUG_PRINT(0x000f02d2,0x000f02e7,param_3,sink,param_4);
            } else {
                FUN_00019c70(0x000f02d2,0x000f02e7,param_3,sink,param_4);
            }
        }
        uVar1 = 0;
    } else {
        param_1[0] = (unsigned char)param_2;
        param_1[1] = (unsigned char)(param_2 >> 8);
        param_1[2] = (unsigned char)(param_2 >> 16);
        param_1[3] = (unsigned char)(param_2 >> 24);
        uVar1 = 1;
    }
    return uVar1;
}
