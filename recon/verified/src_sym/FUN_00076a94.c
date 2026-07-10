/* Reconstructed FUN_00076a94 @ 0x76a94  (parity: 300/300 trials, PROVEN) */

extern void FUN_00076cc8(int,int);
extern int abort(void);
void FUN_00076a94(void)
{
    int uVar1 = *(volatile int*)(*(volatile int*)0x20002d20UL + 0xc);
    for (;;) {
        FUN_00076cc8(uVar1, 0);
        uVar1 = abort();
    }
}

