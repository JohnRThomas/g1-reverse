/* Reconstructed jbd_panel_suspend @ 0x475f0  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(void);
extern void FUN_00019c70(void);
extern void FUN_0007d82e(void);

unsigned int jbd_panel_suspend(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    if (*(volatile int*)0x2000230cUL > 2) {
        if (*(volatile unsigned int*)0x20007554UL == 0) {
            DEBUG_PRINT();
        } else {
            FUN_00019c70();
        }
    }
    FUN_0007d82e();
    return 0;
}

