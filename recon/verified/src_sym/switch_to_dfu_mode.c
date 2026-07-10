/* Reconstructed switch_to_dfu_mode @ 0x158bc  (parity: 300/300 trials, PROVEN) */

typedef unsigned char u8;
typedef unsigned int u32;
extern void DEBUG_PRINT(unsigned int, unsigned int, ...);
extern void debug_print(unsigned int, unsigned int, unsigned int, unsigned int);
extern int k_is_in_isr(void);
extern void FUN_0007c038(int);
extern int sys_reboot(int);
extern void thunk_FUN_00072880(unsigned int);

void switch_to_dfu_mode(unsigned int param_1)
{
    volatile u8 *puVar1 = (volatile u8*)0x2000ff6eUL;
    int iVar2;
    unsigned int r2val;
    typedef int (*fnptr)(unsigned int, void*, int);

    *puVar1 = 1;
    iVar2 = k_is_in_isr();
    if (iVar2 != 0) {
        thunk_FUN_00072880(param_1);
        return;
    }
    {
        /* driver-vtable dispatch: fn pointer at (*device_info_base + 0x1040); signature
         * (uint32 offset, void *buf, size_t len) matches a Zephyr flash_write() call */
        fnptr f = *(fnptr*)((*(volatile u32*)0x200069fcUL /* device_info.device_type @+0x0 */) + 0x1040);
        iVar2 = f(0x990cfU, (void*)puVar1, 1);  /* ~= flash_write(0x990cf, &dfu_flag, 1) */
    }
    if (iVar2 == 0) {
        if (*(volatile int*)0x2000230cUL > 0) {
            if (*(volatile u32*)0x20007554UL /* device_info.is_debug @+0xb58 */ != 0) {
                debug_print(0x99105U, 0x99b2aU, 0, *puVar1);
                goto loop_start;
            } else {
                r2val = 0;
                goto print_lab;
            }
        }
        goto loop_start;
    } else {
        if (*(volatile int*)0x2000230cUL < 1) return;
        if (*(volatile u32*)0x20007554UL /* device_info.is_debug @+0xb58 */ != 0) {
            debug_print(0x990dcU, 0x99b2aU, (unsigned int)iVar2, 0);
            return;
        }
        DEBUG_PRINT(0x990dcU, 0x99b2aU);
        return;
    }
loop_start:
    for (;;) {
        FUN_0007c038(500);
        r2val = (unsigned int)sys_reboot(1);
print_lab:
        DEBUG_PRINT(0x99105U, 0x99b2aU, r2val);
    }
}

