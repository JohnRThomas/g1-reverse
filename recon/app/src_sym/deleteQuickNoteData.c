/* Reconstructed deleteQuickNoteData @ 0x244a8  (parity: 300/300 trials, PROVEN) */
extern int FUN_000720d0(unsigned int a0, void *a1, unsigned int a2, unsigned int a3);
extern void DEBUG_PRINT(unsigned int a0, ...);
extern void debug_print(void);
extern void FUN_00072880(unsigned int a0);

unsigned int deleteQuickNoteData(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    unsigned int buf[3];
    int iVar1;
    unsigned int uVar2;
    (void)param_2;
    buf[0] = 0x00010002UL;
    buf[1] = (unsigned int)(unsigned char)param_1;
    buf[2] = param_3;
    iVar1 = FUN_000720d0(0x20003960UL /* unknown global 0x20003960 */, buf, 0UL, 0UL);
    if (iVar1 == 0) {
        if (2 < *(volatile int*)0x2000230cUL /* unknown global 0x2000230c */) {
            if (*(volatile int*)0x20007554UL /* device_info.is_debug (+0xb58) */ == 0)
                DEBUG_PRINT(0x9ee23UL, 0x9f080UL, param_1);
            else
                debug_print();
        }
        FUN_00072880(0x200079e4UL /* device_info+0xfe8 (gap near gap_0FDB+0x2, name best-effort) */);
        uVar2 = 0;
    } else {
        if (0 < *(volatile int*)0x2000230cUL /* unknown global 0x2000230c */) {
            if (*(volatile int*)0x20007554UL /* device_info.is_debug (+0xb58) */ == 0)
                DEBUG_PRINT(0x9edc2UL, 0x9f080UL);
            else
                debug_print();
        }
        uVar2 = 0xffffffffUL;
    }
    return uVar2;
}

