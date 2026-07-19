/* readable reconstruction; identity: FUN_0002c0e8 @ 0x0002c0e8
 * public-name: update_persist_task_status_to_idle
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   display_close_screen                     <= FUN_00049858 @ 0x00049858
 *   signal_persist_task_event                <= FUN_0007cdf8 @ 0x0007cdf8
 * address symbols (name @ address):
 *   rodata_a25d9                             @ 0x000a25d9
 *   rodata_a2625                             @ 0x000a2625
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_persist_task_status_lock               @ 0x20018d9c
 *   g_persist_task_status                    @ 0x20018d9d
 */
/* Reconstructed update_persist_task_status_to_idle @ 0x2c0e8  (parity: 300/300 trials, PROVEN) */

typedef unsigned char u8;
extern void log_message(unsigned int, unsigned int, ...);
extern void debug_print(unsigned int, unsigned int, unsigned int);
extern void display_close_screen(unsigned int);
extern void signal_persist_task_event(void);

int update_persist_task_status_to_idle(int param_1)
{
    volatile u8 *lock = (volatile u8*)0x20018d9cUL;
    while (*lock != 0) {
        signal_persist_task_event();
    }
    *lock = 1;
    if ((*(char*)(param_1+0xd5) != 0) || (*(char*)(*(int*)(param_1+0x1054)+4) != 1)) {
        if ((*(char*)(param_1+0xd5) != 0) && (*(char*)(param_1+0xd5) != 1)) {
            display_close_screen(*(u8*)(param_1+0xd5));
        }
        if (*(char*)(param_1+0xd5) == 0x10) {
            *(u8*)(param_1+0xf98) = *(volatile u8*)0x20018d9dUL;
        }
        if (*(volatile int*)0x2000230cUL > 0) {
            if (*(volatile unsigned int*)0x20007554UL == 0) {
                log_message(0xa25d9U, 0xa2625U);
            } else {
                debug_print(0xa25d9U, 0xa2625U, 0);
            }
        }
        *(u8*)(param_1+0xd5) = 0;
        *(u8*)(*(int*)(param_1+0x1054)+4) = 1;
    }
    *lock = 0;
    return 0;
}
