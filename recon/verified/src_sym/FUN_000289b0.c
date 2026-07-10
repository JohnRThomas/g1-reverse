/* Reconstructed FUN_000289b0 @ 0x289b0  (parity: 300/300 trials, PROVEN) */

extern int get_device_info(void);
extern void global_system_suspend(void);
extern void FUN_00047ab8(void);
extern void display_close_screen(int);

void FUN_000289b0(void)
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
    *(volatile unsigned char*)0x20018d8bUL = 0;
    return;
}

