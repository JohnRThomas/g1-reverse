/* Reconstructed dequeue_ancs @ 0x18d94  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);
extern int FUN_00072240(void *a, void *b, unsigned int c, unsigned int d);
extern void FUN_00086c04(void *dst, void *src, unsigned int len);
extern void FUN_00086c78(void *dst, int val, unsigned int len);

int dequeue_ancs(void *param_1)
{
    unsigned char buf[0x1b4];
    FUN_00086c78(buf, 0, 0x1b4);

    volatile unsigned char *base = (volatile unsigned char *)0x20006a6cUL;
    if (*(volatile unsigned int *)(base + 0x10) == 0) {
        return 1;
    }

    int iVar1 = FUN_00072240((void *)base, buf, 0, 0);
    if (iVar1 == 0) {
        FUN_00086c04(param_1, buf, 0x1b4);
    } else if (*(volatile int *)0x2000230cUL > 0) {
        if (*(volatile int *)0x20007554UL == 0) {
            DEBUG_PRINT(0x9aa1fU, 0x9b190U);
        } else {
            FUN_00019c70(0x9aa1fU, 0x9b190U);
        }
    }
    return iVar1;
}
