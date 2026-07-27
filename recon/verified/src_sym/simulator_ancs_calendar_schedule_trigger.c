/* Reconstructed simulator_ancs_calendar_schedule_trigger @ 0x21cd8  (parity: 300/300 trials, PROVEN) */

extern unsigned int FUN_000181fc(void);
extern void DEBUG_PRINT(unsigned long, ...);
extern void debug_print(unsigned long, ...);
extern void memset_bytes(unsigned int, int, int);
extern void FUN_0008705a(unsigned int, unsigned int, int);
extern void FUN_0004a3d0(unsigned int, unsigned int);
extern void thunk_FUN_00072880(unsigned int);

void simulator_ancs_calendar_schedule_trigger(void)
{
    unsigned int iVar1;

    iVar1 = FUN_000181fc();
    if (2 < *(volatile int*)0x2000230cUL) {
        if (*(volatile unsigned int*)0x20007554UL /* device_info.is_debug @+0xb58 */ == 0) {
            DEBUG_PRINT(0x99969, 0x9dfbf);
        } else {
            debug_print(0x99969, 0x9dfbf);
        }
    }
    memset_bytes(iVar1 + 0x34, 0, 0x1b4);
    FUN_0008705a(iVar1 + 0x44, 0x9d7b8, 0x20);
    FUN_0008705a(iVar1 + 0x84, 0x9d7cc, 0x20);
    FUN_0008705a(iVar1 + 0xc4, 0x9d7d4, 0x100);
    FUN_0008705a(iVar1 + 0x64, 0x9d7e1, 0x20);
    FUN_0004a3d0(0x9d7e8, iVar1 + 0x34);
    thunk_FUN_00072880(iVar1 + 0x1e8);
}

