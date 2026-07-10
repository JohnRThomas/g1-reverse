/* Reconstructed dequeue_dmic @ 0x2ed00  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(void);
extern void FUN_00019c70(void);
extern int FUN_00072240(void);
extern void FUN_00086c04(void);

int dequeue_dmic(unsigned int param_1)
{
    FUN_00086c04();
    int iVar1 = FUN_00072240();
    if (iVar1 == 0) {
        FUN_00086c04();
    } else if (*(volatile int*)0x2000230cUL > 0) {
        if (*(volatile unsigned int*)0x20007554UL == 0) {
            DEBUG_PRINT();
        } else {
            FUN_00019c70();
        }
    }
    return iVar1;
}

