/* Reconstructed update_persist_task_status_to_idle @ 0x2c0e8  (parity: 300/300 trials, PROVEN) */

typedef unsigned char u8;
extern void DEBUG_PRINT(unsigned long, ...);
extern void debug_print(unsigned long, ...);
extern void display_close_screen(unsigned int);
extern void FUN_0007cdf8(void);

int update_persist_task_status_to_idle(int param_1)
{
    volatile u8 *lock = (volatile u8*)0x20018d9cUL;
    while (*lock != 0) {
        FUN_0007cdf8();
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
            if (*(volatile unsigned int*)0x20007554UL /* device_info.is_debug @+0xb58 */ == 0) {
                DEBUG_PRINT(0xa25d9U, 0xa2625U, 0);
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

