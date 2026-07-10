/* Reconstructed dequeue_ancs @ 0x18d94  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int fmt, unsigned int arg);
extern void debug_print(void);
extern int FUN_00072240(void *a, void *b, unsigned int c, unsigned int d);
extern void memcpy(void *dst, void *src, unsigned int len);
extern void memset_bytes(void *dst, int val, unsigned int len);

int dequeue_ancs(void *param_1)
{
    unsigned char buf[0x1b4];
    memset_bytes(buf, 0, 0x1b4);

    volatile unsigned char *base = (volatile unsigned char *)0x20006a6cUL /* device_info+0x70 (gap near gap_0003+0x6d, name best-effort) */;
    if (*(volatile unsigned int *)(base + 0x10) == 0) {
        return 1;
    }

    int iVar1 = FUN_00072240((void *)base, buf, 0, 0);
    if (iVar1 == 0) {
        memcpy(param_1, buf, 0x1b4);
    } else if (*(volatile int *)0x2000230cUL /* unknown global 0x2000230c */ > 0) {
        if (*(volatile int *)0x20007554UL /* device_info.is_debug (+0xb58) */ == 0) {
            DEBUG_PRINT(0x9aa1fU, 0x9b190U);
        } else {
            debug_print();
        }
    }
    return iVar1;
}

