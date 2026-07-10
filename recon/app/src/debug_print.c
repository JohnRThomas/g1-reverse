/* Reconstructed debug_print @ 0x19c70  (parity: 300/300 trials, PROVEN) */

extern unsigned int FUN_000181fc(void);
extern void FUN_00086c78(void *dst, int val, unsigned int len);
extern void FUN_00077c30(void *dst, unsigned int size, unsigned int fmt, unsigned int *args);
extern void FUN_00019bfc(void *buf);
extern void thunk_FUN_00072880(unsigned int arg);

void debug_print(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned char local_e8[200];
    unsigned int stack_args[3];
    stack_args[0] = param_2;
    stack_args[1] = param_3;
    stack_args[2] = param_4;

    unsigned int iVar1 = FUN_000181fc();

    FUN_00086c78(local_e8, 0, 200);
    FUN_00077c30(local_e8, 200, param_1, stack_args);
    FUN_00019bfc(local_e8);
    local_e8[0] = 0;

    if ((*(volatile unsigned char *)(iVar1 + 0x248) == 0) &&
        (*(volatile unsigned int *)(iVar1 + 0x220) == 0)) {
        *(volatile unsigned int *)0x20007550UL = 1;
        thunk_FUN_00072880(iVar1 + 0x218);
    }
}

