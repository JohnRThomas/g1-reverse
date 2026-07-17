#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00016738 @ 0x00016738
 * public-name: reset_all_static_info
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_99707                             @ 0x00099707
 *   rodata_99bd8                             @ 0x00099bd8
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_dashboard_startup_mode_info_defaults   @ 0x2007fc00
 */
/* Reconstructed reset_all_static_info @ 0x16738  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int,unsigned int,unsigned int,unsigned int,unsigned int);
extern void debug_print(unsigned int,unsigned int,unsigned int,unsigned int,unsigned int);
extern void memset_bytes(void *dst, int val, unsigned int len);

void reset_all_static_info(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    if (*(volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/ > 2) {
        unsigned int sink = *(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
        if (sink == 0) {
            DEBUG_PRINT(((unsigned long)&rodata_99707) /*=0x99707*/, ((unsigned long)&rodata_99bd8) /*=0x99bd8*/, param_3, sink, param_4);
        } else {
            debug_print(((unsigned long)&rodata_99707) /*=0x99707*/, ((unsigned long)&rodata_99bd8) /*=0x99bd8*/, param_3, sink, param_4);
        }
    }
    volatile unsigned char *base = (volatile unsigned char *)((unsigned long)&g_dashboard_startup_mode_info_defaults) /*=0x2007fc00*/;
    *(volatile unsigned int *)(base + 8) = 0;
    *(volatile unsigned int *)(base + 0xc) = 0;
    *(volatile unsigned int *)(base + 0) = 0;
    *(volatile unsigned short *)(base + 4) = 0;
    *(volatile unsigned char *)(base + 0x5f) = 0;
    *(volatile unsigned short *)(base + 0x60) = 0;
    *(volatile unsigned char *)(base + 0x62) = 0;
    *(volatile unsigned char *)(base + 0x68) = 0;
    memset_bytes((void *)(base + 0x10), 0, 0x25);
    memset_bytes((void *)(base + 0x35), 0, 0x25);
    *(volatile unsigned int *)(base + 0x64) = 0;
}
