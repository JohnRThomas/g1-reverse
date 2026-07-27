/* Reconstructed stopAudioStreamRecord @ 0x2f80c  (parity: 300/300 trials, PROVEN) */

extern void memset_bytes(void);
extern int FUN_000720d0(void);
extern void FUN_00072880(void);
extern void DEBUG_PRINT(unsigned long, ...);
extern void debug_print(unsigned long, ...);

unsigned int stopAudioStreamRecord(void)
{
    memset_bytes();
    int iVar1 = FUN_000720d0();
    unsigned int uVar2;
    if (iVar1 == 0) {
        FUN_00072880();
        uVar2 = 0;
    } else {
        if (*(volatile int*)0x2000230cUL > 0) {
            if (*(volatile unsigned int*)0x20007554UL /* device_info.is_debug @+0xb58 */ == 0) {
                DEBUG_PRINT();
            } else {
                debug_print();
            }
        }
        uVar2 = 0xffffffffUL;
    }
    return uVar2;
}

