#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000498c0 @ 0x000498c0
 * public-name: display_DelayClose
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   k_msgq_put                               <= FUN_000720d0 @ 0x000720d0
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_ef058                             @ 0x000ef058   [INLINED -- G6 literal batch]
 *   rodata_f008c                             @ 0x000f008c   [INLINED -- G6 literal batch]
 *   rodata_f0164                             @ 0x000f0164   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_display_msgq                           @ 0x200038c4
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed display_DelayClose @ 0x498c0  (parity: 300/300 trials, PROVEN) */

extern void memset_bytes(void*, int, int);
extern int k_msgq_put(unsigned int, void*, int, int);
extern void log_message(unsigned long, ...);
extern void debug_print(unsigned long, ...);

unsigned int display_DelayClose(unsigned int param_1)
{
    unsigned char buf[0x18];
    memset_bytes(buf + 1, 0, 0x17);
    buf[0] = 4;
    *(unsigned short *)(buf + 2) = 4;
    *(unsigned int *)(buf + 4) = param_1;

    void *obj = (void *)((unsigned long)&g_display_msgq) /*=0x200038c4*/;
    int iVar1 = k_msgq_put(obj, buf, 0, 0);
    unsigned int uVar2;

    if (iVar1 == 0) {
        uVar2 = 0;
        if (*(volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/ > 2) {
            if (*(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                log_message(((unsigned long)"%s(): send display delay close command.......\n") /*=0xf008c*/, ((unsigned long)"display_DelayClose") /*=0xf0164*/);
            } else {
                debug_print(((unsigned long)"%s(): send display delay close command.......\n") /*=0xf008c*/, ((unsigned long)"display_DelayClose") /*=0xf0164*/);
            }
        }
    } else {
        log_message(((unsigned long)"message queue send failed %s\r\n") /*=0xef058*/, ((unsigned long)"display_DelayClose") /*=0xf0164*/);
        uVar2 = 0xffffffffU;
    }
    return uVar2;
}
