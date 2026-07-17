/* Reconstructed reset_all_static_info @ 0x16738  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int,unsigned int,unsigned int,unsigned int,unsigned int);
extern void FUN_00019c70(unsigned int,unsigned int,unsigned int,unsigned int,unsigned int);
extern void FUN_00086c78(void *dst, int val, unsigned int len);

void reset_all_static_info(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    if (*(volatile int *)0x2000230cUL > 2) {
        unsigned int sink = *(volatile int *)0x20007554UL;
        if (sink == 0) {
            DEBUG_PRINT(0x99707U, 0x99bd8U, param_3, sink, param_4);
        } else {
            FUN_00019c70(0x99707U, 0x99bd8U, param_3, sink, param_4);
        }
    }
    volatile unsigned char *base = (volatile unsigned char *)0x2007fc00UL;
    *(volatile unsigned int *)(base + 8) = 0;
    *(volatile unsigned int *)(base + 0xc) = 0;
    *(volatile unsigned int *)(base + 0) = 0;
    *(volatile unsigned short *)(base + 4) = 0;
    *(volatile unsigned char *)(base + 0x5f) = 0;
    *(volatile unsigned short *)(base + 0x60) = 0;
    *(volatile unsigned char *)(base + 0x62) = 0;
    *(volatile unsigned char *)(base + 0x68) = 0;
    FUN_00086c78((void *)(base + 0x10), 0, 0x25);
    FUN_00086c78((void *)(base + 0x35), 0, 0x25);
    *(volatile unsigned int *)(base + 0x64) = 0;
}
