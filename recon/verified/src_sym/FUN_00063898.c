/* Reconstructed FUN_00063898 @ 0x63898  (parity: 300/300 trials, PROVEN) */

extern void printk(unsigned int, unsigned int, unsigned int, unsigned int);
extern unsigned long long assert_post_action(unsigned int, unsigned int);

void FUN_00063898(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    if (param_1 != 1) {
        printk(0x99cbdUL, 0xf66a6UL, 0xf6659UL, 0x257UL);
        assert_post_action(0xf6659UL, 0x257UL);
    }
    *(volatile unsigned int*)0x2000b2d4UL |= 2;
}

