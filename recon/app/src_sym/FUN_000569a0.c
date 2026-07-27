/* Reconstructed FUN_000569a0 @ 0x569a0  (parity: 300/300 trials, PROVEN) */

extern void printk(unsigned long, ...);
extern void assert_post_action(unsigned int, unsigned int);

unsigned int FUN_000569a0(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    int diff = param_1 - (int)0x20006138;
    int shifted = diff >> 3;
    unsigned int R = (0x684bda13U * (unsigned int)shifted) & 0xffU;
    if (param_1 != (int)0x20006138) {
        printk(0x99cbdUL, 0xf3c92UL, 0xf3a5dUL, 0x543UL);
        printk(0xf3d5bUL, 0xf3a5dUL, 0x543UL, 0x543UL);
        assert_post_action(0xf3a5dUL, 0x543UL);
        return 0x543U & 0xffU;
    }
    return R;
}

