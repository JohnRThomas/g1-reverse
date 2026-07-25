#include "g1_app_symbols.h"
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
extern void global_system_suspend(int context);
extern void free_pixel4bit_row_buf(void);
extern void display_close_screen(int);

void prepare_system_suspend_state(void)
{
    int iVar2;
    free_pixel4bit_row_buf();
    /* iteration 14: the original forwards get_device_info()'s return (r0, the
     * device context) straight into global_system_suspend -- 0x289b6 bl
     * 0x167a8 ; 0x289ba bl 0x2bd7c.  Dropping it handed the callee a NULL
     * context, and its `ldr r3,[r4,#0xb70] ; blx r3` then faulted. */
    iVar2 = get_device_info();
    global_system_suspend(iVar2);
    iVar2 = get_device_info();
    *(unsigned char*)(iVar2 + 0xee4) = 1;
    display_close_screen(3);
    iVar2 = get_device_info();
    *(unsigned char*)(iVar2 + 0xd5) = 0;
    *(volatile unsigned char*)((unsigned long)&g_suspend_pending_flag) /*=0x20018d8b*/ = 0;
    return;
}
