/* Reconstructed FUN_000183ac @ 0x183ac  (parity: 300/300 trials, PROVEN) */

extern void FUN_00018334(int, int);
extern void DEBUG_PRINT(int, int);
void FUN_000183ac(int param_1, int param_2)
{
    char auStack_28[32];
    FUN_00018334(param_2, (int)auStack_28);
    DEBUG_PRINT(0x0009a458, (int)auStack_28);
    (*(volatile int*)0x20007514UL)--;
    *(volatile char*)(*(volatile int*)0x20006ab8UL + 0x367) = 0;
}
