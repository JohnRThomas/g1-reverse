/* Reconstructed lseek @ 0x4b17c  (parity: 300/300 trials, PROVEN) */

extern int FUN_0004b01c(void);
extern unsigned int z_fdtable_call_ioctl(unsigned int, unsigned int, int, unsigned int, unsigned int, unsigned int);

unsigned int lseek(int param_1, unsigned int param_2, unsigned int param_3)
{
    int iVar1 = FUN_0004b01c();
    if (iVar1 < 0) {
        return 0xffffffff;
    }
    unsigned int base = 0x20002548UL + (unsigned int)param_1 * 0x28U;
    unsigned int v0 = *(volatile unsigned int*)base;
    unsigned int v4 = *(volatile unsigned int*)(base + 4);
    return z_fdtable_call_ioctl(v4, v0, 0x101, param_2, param_3, param_2);
}

