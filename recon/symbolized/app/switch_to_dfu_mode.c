#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000158bc @ 0x000158bc
 * public-name: switch_to_dfu_mode
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   sys_reboot                               <= FUN_0004c0a8 @ 0x0004c0a8
 *   app_msleep_thunk_a                       <= FUN_0007c038 @ 0x0007c038
 *   k_is_in_isr                              <= FUN_00086406 @ 0x00086406
 * address symbols (name @ address):
 *   rodata_990cf                             @ 0x000990cf
 *   rodata_990dc                             @ 0x000990dc
 *   rodata_99105                             @ 0x00099105
 *   rodata_99b2a                             @ 0x00099b2a
 *   g_log_level                              @ 0x2000230c
 *   device_info                              @ 0x200069fc
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_runtime_mode_flag                      @ 0x2000ff6e
 */
/* Reconstructed switch_to_dfu_mode @ 0x158bc  (parity: 300/300 trials, PROVEN) */

typedef unsigned char u8;
typedef unsigned int u32;
extern void DEBUG_PRINT(unsigned int, unsigned int, ...);
extern void debug_print(unsigned int, unsigned int, unsigned int, unsigned int);
extern int k_is_in_isr(void);
extern void app_msleep_thunk_a(int);
extern int sys_reboot(int);
extern void thunk_FUN_00072880(unsigned int);

void switch_to_dfu_mode(unsigned int param_1)
{
    volatile u8 *puVar1 = (volatile u8*)((unsigned long)&g_runtime_mode_flag) /*=0x2000ff6e*/;
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
        fnptr f = *(fnptr*)((*(volatile u32*)((unsigned long)&device_info) /*=0x200069fc*/) + 0x1040);
        iVar2 = f(((unsigned long)&rodata_990cf) /*=0x990cf*/, (void*)puVar1, 1);
    }
    if (iVar2 == 0) {
        if (*(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/ > 0) {
            if (*(volatile u32*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ != 0) {
                debug_print(((unsigned long)&rodata_99105) /*=0x99105*/, ((unsigned long)&rodata_99b2a) /*=0x99b2a*/, 0, *puVar1);
                goto loop_start;
            } else {
                r2val = 0;
                goto print_lab;
            }
        }
        goto loop_start;
    } else {
        if (*(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/ < 1) return;
        if (*(volatile u32*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ != 0) {
            debug_print(((unsigned long)&rodata_990dc) /*=0x990dc*/, ((unsigned long)&rodata_99b2a) /*=0x99b2a*/, (unsigned int)iVar2, 0);
            return;
        }
        DEBUG_PRINT(((unsigned long)&rodata_990dc) /*=0x990dc*/, ((unsigned long)&rodata_99b2a) /*=0x99b2a*/);
        return;
    }
loop_start:
    for (;;) {
        app_msleep_thunk_a(500);
        r2val = (unsigned int)sys_reboot(1);
print_lab:
        DEBUG_PRINT(((unsigned long)&rodata_99105) /*=0x99105*/, ((unsigned long)&rodata_99b2a) /*=0x99b2a*/, r2val);
    }
}
