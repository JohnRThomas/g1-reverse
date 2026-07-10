/* Reconstructed FUN_000574ec @ 0x574ec  (parity: 300/300 trials, PROVEN) */

extern void FUN_000864e8(unsigned int a, unsigned int b);
extern void FUN_000732d4(unsigned int a, unsigned int b);

void FUN_000574ec(int param_1)
{
    *(volatile unsigned int*)(param_1+0x24) = 0;
    *(volatile unsigned int*)(param_1+0x28) = 0;
    *(volatile unsigned int*)(param_1+0x2c) = 0;
    unsigned int uVar1 = *(volatile unsigned int*)(param_1+0x2c);
    *(volatile unsigned int*)(param_1+0x2c) = 0;
    FUN_000864e8(param_1+0x30, uVar1);
    FUN_000732d4(param_1+0x50, 0x000818ddUL);
}

