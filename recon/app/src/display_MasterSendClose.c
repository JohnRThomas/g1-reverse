/* Reconstructed display_MasterSendClose @ 0x499b8  (parity: 300/300 trials, PROVEN) */

extern void FUN_00086c78(void *destination, int value, unsigned int length);
extern int FUN_000720d0(unsigned int queue, void *record,
                       unsigned int wait, unsigned int flags);
extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);

unsigned int display_MasterSendClose(void)
{
    unsigned char record[24];

    FUN_00086c78(record + 1, 0, 23);
    record[0] = 6;
    int iVar1 = FUN_000720d0(0x200038c4UL, record, 0, 0);
    unsigned int uVar2;
    if (iVar1 == 0) {
        uVar2 = 0;
        if (*(volatile int*)0x2000230cUL > 2) {
            if (*(volatile unsigned int*)0x20007554UL == 0) {
                DEBUG_PRINT(0x000f008cUL, 0x000f0139UL);
            } else {
                FUN_00019c70(0x000f008cUL, 0x000f0139UL);
            }
        }
    } else {
        DEBUG_PRINT(0x000ef058UL, 0x000f0139UL);
        uVar2 = 0xffffffffUL;
    }
    return uVar2;
}
