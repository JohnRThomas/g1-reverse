/* Reconstructed upgradeDashboardStartupModeInfoToFlash @ 0x23bfc  (parity: 300/300 trials, PROVEN) */
extern int FUN_000720d0(unsigned int a0, void *a1, unsigned int a2, unsigned int a3);
extern void DEBUG_PRINT(unsigned long, ...);
extern void debug_print(unsigned long, ...);
extern void FUN_00072880(unsigned int a0);

unsigned int upgradeDashboardStartupModeInfoToFlash(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    unsigned int buf[3];
    int iVar1;
    unsigned int uVar2;
    (void)param_2;
    buf[0] = 0x00010003UL;
    buf[1] = (unsigned int)(unsigned char)param_1;
    buf[2] = param_3;
    iVar1 = FUN_000720d0(0x20003994UL, buf, 0UL, 0UL);
    if (iVar1 == 0) {
        if (2 < *(volatile int*)0x2000230cUL) {
            if (*(volatile int*)0x20007554UL /* device_info.is_debug @+0xb58 */ == 0)
                DEBUG_PRINT(0x9e98cUL, 0x9ed68UL, param_1);
            else
                debug_print(0x9e98cUL, 0x9ed68UL, param_1);
        }
        FUN_00072880(0x200079e4UL /* device_info_t+0xfe8 (unmapped region) */);
        uVar2 = 0;
    } else {
        if (0 < *(volatile int*)0x2000230cUL) {
            if (*(volatile int*)0x20007554UL /* device_info.is_debug @+0xb58 */ == 0)
                DEBUG_PRINT(0x9e903UL, 0x9ed68UL);
            else
                debug_print(0x9e903UL, 0x9ed68UL);
        }
        uVar2 = 0xffffffffUL;
    }
    return uVar2;
}

