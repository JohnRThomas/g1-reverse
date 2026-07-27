/* Reconstructed FUN_0005f390 @ 0x5f390  (parity: 300/300 trials, PROVEN) */

extern int FUN_0005f2d4(int a, int b, unsigned int c, unsigned int d);
extern unsigned int FUN_0005f304(void);
extern void FUN_0005f338(unsigned int a, int b);
extern void assert_post_action(unsigned int a, unsigned int b);
extern void printk(unsigned long, ...);

int FUN_0005f390(int param_1, int param_2, unsigned int param_3, unsigned int param_4)
{
    int iVar1;
    unsigned int uVar2;

    if (param_2 == 0) {
        printk(0x00099cbdUL, 0x000f542dUL, 0x000f539aUL, 0x24d);
        assert_post_action(0x000f539aUL, 0x24d);
    }
    if (param_1 == 0) {
        iVar1 = FUN_0005f2d4(param_2, param_2, param_3, param_4);
        return iVar1;
    }
    uVar2 = FUN_0005f304();
    FUN_0005f338(uVar2, param_2);
    return param_1;
}

