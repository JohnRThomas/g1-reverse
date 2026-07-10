/* Reconstructed auth_cancel @ 0x1849c  (parity: 300/300 trials, PROVEN) */

extern void FUN_00018334(void);
extern unsigned int FUN_00081526(void);
extern void DEBUG_PRINT(void);
extern void FUN_00019c70(void);
extern void FUN_00056a68(void);

void auth_cancel(unsigned int param_1)
{
    unsigned int uVar1 = FUN_00081526();
    (void)uVar1;
    FUN_00018334();
    DEBUG_PRINT();
    if (*(volatile int*)0x2000230cUL > 0) {
        if (*(volatile unsigned int*)0x20007554UL == 0) {
            DEBUG_PRINT();
        } else {
            FUN_00019c70();
        }
    }
    FUN_00056a68();
}

