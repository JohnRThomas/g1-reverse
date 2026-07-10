/* Reconstructed panel_off @ 0x46d2c  (parity: 300/300 trials, PROVEN) */

typedef void (*fn_t)(int);
extern void DEBUG_PRINT(int a, int b);
extern int FUN_00019c70(void);
extern int FUN_0001655c(void);
extern int FUN_0002e8b4(void);
extern int FUN_00015fdc(void);

unsigned int panel_off(int param_1)
{
    int iVar1;

    *(int *)(param_1 + 0x374) = param_1 + -0x5c;
    if (*(int *)(param_1 + -0x48) != 0) {
        *(int *)(param_1 + 0x35c) = 0;
        if (*(volatile int *)0x2000230cUL > 2) {
            if (*(volatile int *)0x20007554UL == 0) {
                DEBUG_PRINT(0xd721e, 0xd72d1);
            } else {
                FUN_00019c70();
            }
        }
        iVar1 = FUN_0001655c();
        if (iVar1 == 0) {
            FUN_0002e8b4();
        }
        ((fn_t)(*(int *)(param_1 + -0x58)))(*(int *)(param_1 + 0x374));
        FUN_00015fdc();
    }
    return 0;
}

