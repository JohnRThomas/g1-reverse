/* Reconstructed SlaveDoubleClickEventInject @ 0x48ad4  (parity: 300/300 trials, PROVEN) */

extern void memset_bytes(void);
extern int FUN_000720d0(void);
extern void DEBUG_PRINT(void);
extern void debug_print(void);

unsigned int SlaveDoubleClickEventInject(void)
{
    memset_bytes();
    int iVar1 = FUN_000720d0();
    unsigned int uVar2;
    if (iVar1 == 0) {
        uVar2 = 0;
        if (*(volatile int*)0x2000230cUL /* unknown global 0x2000230c */ > 2) {
            if (*(volatile unsigned int*)0x20007554UL /* device_info.is_debug (+0xb58) */ == 0) {
                DEBUG_PRINT();
            } else {
                debug_print();
            }
        }
    } else {
        DEBUG_PRINT();
        uVar2 = 0xffffffffUL;
    }
    return uVar2;
}

