/* Reconstructed store_whitelist @ 0x35608  (parity: 300/300 trials, PROVEN) */
extern int FUN_000227d0(unsigned int a0, unsigned int a1, unsigned int a2);
extern void FUN_000355b4(void);
extern void FUN_00074844(unsigned int a0, unsigned int a1);
extern void DEBUG_PRINT(unsigned int a0, ...);
extern void FUN_00019c70(unsigned int a0, ...);

int store_whitelist(void)
{
    int iVar4;
    unsigned char cVar5 = 3;
    do {
        iVar4 = FUN_000227d0(0x131000UL, 0x2001a22cUL, 0x15e2UL);
        if (iVar4 == 0) {
            FUN_000355b4();
            break;
        }
        FUN_00074844(0xa4UL, 0UL);
        if (*(volatile int*)0x20007554UL == 0)
            DEBUG_PRINT(0xa896cUL);
        else
            FUN_00019c70(0);
        cVar5 = cVar5 - 1;
    } while (cVar5 != 0);
    if (*(volatile int*)0x20007554UL == 0)
        DEBUG_PRINT(0xa8994UL, 0xa8ab7UL, 0x24UL, iVar4);
    else
        FUN_00019c70(0xa8994UL, 0xa8ab7UL, 0x24UL, iVar4);
    return iVar4;
}

