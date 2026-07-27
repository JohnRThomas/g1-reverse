/* Reconstructed cleanDashBoardStartUpModeInfo @ 0x23c88  (parity: 300/300 trials, PROVEN) */
extern void DEBUG_PRINT(unsigned long, ...);
extern void debug_print(unsigned long, ...);
extern int FUN_000720d0(unsigned int a0, void *a1, unsigned int a2, unsigned int a3);
extern void FUN_00072880(unsigned int a0);

unsigned int cleanDashBoardStartUpModeInfo(unsigned int param_1, unsigned int param_2)
{
    unsigned int buf[2];
    int iVar1;
    unsigned int uVar2;
    (void)param_1; (void)param_2;
    buf[0] = 4;
    buf[1] = 0;
    iVar1 = FUN_000720d0(0x20003994UL /* unknown global 0x20003994 */, buf, 0UL, 0UL);
    if (iVar1 == 0) {
        if (2 < *(volatile int*)0x2000230cUL /* unknown global 0x2000230c */) {
            if (*(volatile int*)0x20007554UL /* device_info.is_debug (+0xb58) */ == 0)
                DEBUG_PRINT(0x9e968UL, 0x9ed4aUL);
            else
                debug_print(0x9e968UL, 0x9ed4aUL);
        }
        FUN_00072880(0x200079e4UL /* device_info+0xfe8 (gap near gap_0FDB+0x2, name best-effort) */);
        uVar2 = 0;
    } else {
        if (0 < *(volatile int*)0x2000230cUL /* unknown global 0x2000230c */) {
            if (*(volatile int*)0x20007554UL /* device_info.is_debug (+0xb58) */ == 0)
                DEBUG_PRINT(0x9e903UL, 0x9ed4aUL);
            else
                debug_print(0x9e903UL, 0x9ed4aUL);
        }
        uVar2 = 0xffffffffUL;
    }
    return uVar2;
}

