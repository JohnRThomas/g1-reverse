/* Reconstructed FUN_000510fc @ 0x510fc  (parity: 300/300 trials, PROVEN) */

extern void assert_post_action(int,int);
extern void printk(int,int,int,int);
extern void FUN_000723b8(int,int,int,int);
void FUN_000510fc(int param_1, int param_2)
{
    if (param_1 == 0) {
        printk(0x00099cbd, 0x000f23d4, 0x000f22d5, 0x1a6);
        assert_post_action(0x000f22d5, 0x1a6);
    }
    FUN_000723b8(param_1, param_2, -1, -1);
}

