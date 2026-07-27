/* Reconstructed getNewsIndex @ 0x3719c  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);

unsigned long getNewsIndex(void) {
    volatile unsigned char *base = (volatile unsigned char*)0x20004950UL;
    int iVar2 = *(volatile int*)0x2000230cUL;
    unsigned char b = *(volatile unsigned char*)0x2001b814UL;
    base[5] = b;
    if (iVar2 > 2) {
        if (*(volatile int*)0x20007554UL == 0) {
            DEBUG_PRINT(0x000a8ff3UL, 0x000a95abUL, 0x000a95abUL, b);
        } else {
            FUN_00019c70(0x000a8ff3UL, 0x000a95abUL, 0x000a95abUL, b);
        }
    }
    return base[5];
}
