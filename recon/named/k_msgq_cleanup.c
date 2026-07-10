/* named: k_msgq_cleanup */
/* Reconstructed k_msgq_cleanup @ 0x86480  (parity: 300/300 trials, PROVEN) */

extern void FUN_000868b4(int);

int k_msgq_cleanup(int *param_1)
{
    int v0 = *(volatile int*)param_1;
    if (param_1 == (int*)v0 || v0 == 0) {
        unsigned char flag = *(volatile unsigned char*)((char*)param_1 + 0x30);
        if ((int)((unsigned int)flag << 31) < 0) {
            int arg = *(volatile int*)((char*)param_1 + 0x14);
            FUN_000868b4(arg);
            unsigned char flag2 = *(volatile unsigned char*)((char*)param_1 + 0x30);
            *(volatile unsigned char*)((char*)param_1 + 0x30) = flag2 & 0xfe;
        }
        return 0;
    } else {
        return (int)0xfffffff0;
    }
}

