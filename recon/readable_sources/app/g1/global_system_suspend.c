#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_system_suspend_ctx__param_0077         [param_0077; G1-original]
 * Raw function identity: 0x0002bd7c.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0002bd7c @ 0x0002bd7c
 * public-name: global_system_suspend
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 * address symbols (name @ address):
 *   rodata_a24eb                             @ 0x000a24eb
 *   rodata_a24f9                             @ 0x000a24f9
 *   rodata_a251a                             @ 0x000a251a
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed global_system_suspend @ 0x2bd7c  (parity: 296/300 trials, PROVEN) */

extern void log_message(unsigned int fmt, unsigned int a1, unsigned int a2, unsigned int a3);
extern void debug_print(void);
typedef void (*fn2_t)(unsigned int);

unsigned int global_system_suspend(void *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    volatile unsigned char *base = (volatile unsigned char *)param_1;
    if ((*(base + 0xfe6) & 0xfb) == 0) {
        *(base + 0xfe6) = 2;
        if (*(volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/ > 1) {
            if (*(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                log_message(((unsigned long)&rodata_a24eb) /*=0xa24eb*/, ((unsigned long)&rodata_a251a) /*=0xa251a*/, param_3, 0U);
            } else {
                debug_print();
            }
        }
        fn2_t fn = *(fn2_t *)(base + 0xb70);
        fn((unsigned int)((unsigned char *)param_1 + 0xb6c));
        if (*(volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/ > 1) {
            if (*(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                log_message(((unsigned long)&rodata_a24f9) /*=0xa24f9*/, ((unsigned long)&rodata_a251a) /*=0xa251a*/, param_3, 0U);
            } else {
                debug_print();
            }
        }
        *(base + 0xfe6) = 1;
    }
    return 0;
}
