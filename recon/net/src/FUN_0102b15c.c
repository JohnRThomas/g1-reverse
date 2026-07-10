/* net-core FUN_0102b15c @ 0x102b15c  (parity 300 trials PROVEN) */
extern void FUN_0103b62e(void *dst, int val, int len);
extern void FUN_0103b53a(void *dst, unsigned int a, unsigned int b, int len);
extern int FUN_0102a498(void);
extern int FUN_0102a468(void);
extern void FUN_0102a448(void *a, unsigned int b);
extern void FUN_01039722(int a, unsigned int b, int c);

unsigned int FUN_0102b15c(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    unsigned int local_10c = 0;
    unsigned char auStack_108[252];
    unsigned int uVar2;

    FUN_0103b62e(auStack_108, 0, 0xf8);
    FUN_0103b53a(&local_10c, param_2, param_3, 0xfc);
    int iVar1 = FUN_0102a498();
    if (iVar1 == 1) {
        return 0;
    }
    if (param_3 < 0xfc) {
        iVar1 = FUN_0102a468();
        if (iVar1 == 0) {
            FUN_0102a448(&local_10c, param_3);
            *(volatile unsigned char *)0x21004c9c = 1;
            return 0;
        }
    } else if (0 < *(volatile int *)0x21000580) {
        FUN_01039722(0x103d11b, param_3, 0xfb);
    }
    uVar2 = 0xffffffff;
    return uVar2;
}


