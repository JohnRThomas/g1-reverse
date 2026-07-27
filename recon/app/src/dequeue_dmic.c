/* Reconstructed dequeue_dmic @ 0x2ed00  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);
extern int FUN_00072240(unsigned int queue, void *record,
                       unsigned int wait, unsigned int flags);
extern void FUN_00086c04(void *destination, const void *source,
                        unsigned int length);

int dequeue_dmic(void *param_1)
{
    unsigned char record[204];

    FUN_00086c04(record, (const void *)0x000885ccUL, 200);
    int iVar1 = FUN_00072240(0x20007b7cUL, record, 0, 0);
    if (iVar1 == 0) {
        FUN_00086c04(param_1, record, 200);
    } else if (*(volatile int*)0x2000230cUL > 0) {
        if (*(volatile unsigned int*)0x20007554UL == 0) {
            DEBUG_PRINT(0x000a3f62UL, 0x000a41d5UL);
        } else {
            FUN_00019c70(0x000a3f62UL, 0x000a41d5UL);
        }
    }
    return iVar1;
}
