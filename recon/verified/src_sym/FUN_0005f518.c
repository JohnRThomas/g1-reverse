/* Reconstructed FUN_0005f518 @ 0x5f518  (parity: 300/300 trials, PROVEN) */

extern void printk(unsigned int, unsigned int, unsigned int, unsigned int);
extern unsigned long long assert_post_action(unsigned int, unsigned int);

void FUN_0005f518(int *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned int r0 = (unsigned int)*param_1;
    char *r3 = (char*)param_1;
    unsigned int r1 = param_2;
    if ((unsigned int)(r0 - param_1[2]) < param_2) {
        printk(0x99cbdUL, 0xf5484UL, 0xf543aUL, 0x12dUL);
        unsigned long long rv = assert_post_action(0xf543aUL, 0x12dUL);
        r0 = (unsigned int)rv;
        r1 = (unsigned int)(rv >> 32);
        r3 = (char*)0x12dUL;
    }
    unsigned short r2 = *(volatile unsigned short*)(r3 + 4);
    *(volatile unsigned int*)r3 = r0 - r1;
    *(volatile short*)(r3 + 4) = (short)r1 + (short)r2;
}

