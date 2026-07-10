/* Reconstructed FUN_00059e78 @ 0x59e78  (parity: 300/300 trials, PROVEN) */

extern void assert_post_action(unsigned int a, unsigned int b);
extern void printk(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
extern void FUN_000828da(void *a, unsigned int b, unsigned int c, unsigned int d);

void FUN_00059e78(char *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    if (*(volatile int*)(param_1 + 8) != 0) {
        printk(0x00099cbdUL, 0x000f4707UL, 0x000f46b8UL, 0xd5c);
        assert_post_action(0x000f46b8UL, 0xd5c);
    }
    FUN_000828da(param_1 + 1, 0x000f2b3aUL, param_3, param_4);
}

