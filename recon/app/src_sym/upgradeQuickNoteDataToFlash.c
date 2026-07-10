/* Reconstructed upgradeQuickNoteDataToFlash @ 0x24420  (parity: 300/300 trials, PROVEN) */

extern int FUN_000720d0(unsigned int, void*, int, int);
extern void DEBUG_PRINT(unsigned int, unsigned int, ...);
extern void debug_print(void);
extern void FUN_00072880(unsigned int);

int upgradeQuickNoteDataToFlash(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    unsigned int local_18;
    unsigned int local_14;
    unsigned int uStack_10;
    int iVar1;
    int uVar2;

    local_18 = 0x10001;
    local_14 = (((param_1 & 0xff)) | ((param_2 & 0xff00))) & 0xffff00ff;
    uStack_10 = param_3;
    iVar1 = FUN_000720d0(*(volatile unsigned int*)0x20003960UL, &local_18, 0, 0);
    if (iVar1 == 0) {
        if (2 < *(volatile int*)0x2000230cUL) {
            if (*(volatile unsigned int*)0x20007554UL /* device_info.is_debug @+0xb58 */ == 0) {
                DEBUG_PRINT(0x9edf3, 0x9f094, param_1);
            } else {
                debug_print();
            }
        }
        FUN_00072880(*(volatile unsigned int*)0x200079e4UL /* device_info_t+0xfe8 (unmapped region) */);
        uVar2 = 0;
    } else {
        if (0 < *(volatile int*)0x2000230cUL) {
            if (*(volatile unsigned int*)0x20007554UL /* device_info.is_debug @+0xb58 */ == 0) {
                DEBUG_PRINT(0x9edc2, 0x9f094);
            } else {
                debug_print();
            }
        }
        uVar2 = -1;
    }
    return uVar2;
}

