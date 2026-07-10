#include "g1_app_symbols.h"
/* named: prepare_system_suspend_state */
/* Reconstructed prepare_system_suspend_state @ 0x289b0  (parity: 300/300 trials, PROVEN) */

extern int get_device_info(void);
extern void global_system_suspend(void);
extern void FUN_00047ab8(void);
extern void display_close_screen(int);

void prepare_system_suspend_state(void)
{
    int iVar2;
    FUN_00047ab8();
    get_device_info();
    global_system_suspend();
    iVar2 = get_device_info();
    *(unsigned char*)(iVar2 + 0xee4) = 1;
    display_close_screen(3);
    iVar2 = get_device_info();
    *(unsigned char*)(iVar2 + 0xd5) = 0;
    *(volatile unsigned char*)((uintptr_t)&g_suspend_pending_flag) /*=0x20018d8b*/ = 0;
    return;
}

