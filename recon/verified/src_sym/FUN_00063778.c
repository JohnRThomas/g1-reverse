/* Reconstructed FUN_00063778 @ 0x63778  (parity: 300/300 trials, PROVEN) */

extern void printk(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
extern void assert_post_action(unsigned int, unsigned int);
extern void compare_set(void);

void FUN_00063778(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    if (param_1 != 1) {
        printk(0x99cbdUL, 0xf66a6UL, 0xf6659UL, 0x18dUL, param_1, param_2, param_3, param_4);
        assert_post_action(0xf6659UL, 0x18dUL);
    }
    compare_set();
}

