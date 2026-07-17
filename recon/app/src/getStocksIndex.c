/* Reconstructed getStocksIndex @ 0x370bc  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int,unsigned int,unsigned int,unsigned int);
extern void FUN_00019c70(unsigned int,unsigned int,unsigned int,unsigned int);

unsigned char getStocksIndex(void)
{
    volatile unsigned char *base = (volatile unsigned char*)0x20004950UL;
    int iVar2 = *(volatile int*)0x2000230cUL;
    unsigned char b = *(volatile unsigned char*)0x2001b815UL;
    base[3] = b;
    if (iVar2 > 2) {
        if (*(volatile int*)0x20007554UL == 0) {
            DEBUG_PRINT(0x000a8ff3UL, 0x000a95d8UL, 0x000a95d8UL, b);
        } else {
            FUN_00019c70(0x000a8ff3UL, 0x000a95d8UL, 0x000a95d8UL, b);
        }
    }
    return base[3];
}
