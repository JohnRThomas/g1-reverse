/* readable reconstruction; identity: FUN_000289b0 @ 0x000289b0
 * public-name: prepare_system_suspend_state
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   prepare_system_suspend_state             <= FUN_000289b0 @ 0x000289b0
 *   global_system_suspend                    <= FUN_0002bd7c @ 0x0002bd7c
 *   free_pixel4bit_row_buf                   <= FUN_00047ab8 @ 0x00047ab8
 *   display_close_screen                     <= FUN_00049858 @ 0x00049858
 * address symbols (name @ address):
 *   g_suspend_pending_flag                   @ 0x20018d8b
 */
/* Reconstructed FUN_000289b0 @ 0x289b0  (parity: 300/300 trials, PROVEN) */

extern int get_device_info(void);
extern void global_system_suspend(void);
extern void free_pixel4bit_row_buf(void);
extern void display_close_screen(int);

void prepare_system_suspend_state(void)
{
    int iVar2;
    free_pixel4bit_row_buf();
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
