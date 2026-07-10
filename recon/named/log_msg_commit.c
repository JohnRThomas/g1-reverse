/* named: log_msg_commit */
/* Reconstructed log_msg_commit @ 0x4d8f8  (parity: 300/300 trials, PROVEN) */

extern void printk(int a, int b, int c, int d);
extern void assert_post_action(int a, int b);
extern void FUN_0004d44c(void);

void log_msg_commit(int param_1, unsigned int param_2, unsigned char param_3)
{
    if (param_1 == 0) {
        printk(0x99cbd, 0xf0ddf, 0xf0da7, 0xdf);
        assert_post_action(0xf0da7, 0xdf);
    }
    *(char *)(*(int *)(param_1 + 4) + 4) = (char)((param_1 - 0x882a0) >> 4) + 1;
    *(unsigned char *)(*(int *)(param_1 + 4) + 6) = param_3;
    **(unsigned int **)(param_1 + 4) = param_2;
    *(unsigned char *)(*(int *)(param_1 + 4) + 5) = 1;
    FUN_0004d44c();
}

