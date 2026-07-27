#include "g1_app_symbols.h"
#include "../../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_00023514 @ 0x00023514
 * public-name: enqueue_file
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   k_msgq_put                               <= FUN_000720d0 @ 0x000720d0
 *   k_msgq_get                               <= FUN_00072240 @ 0x00072240
 *   safe_memcpy_checked                      <= FUN_00086c1e @ 0x00086c1e
 * address symbols (name @ address):
 *   rodata_9e824                             @ 0x0009e824   [INLINED -- G6 literal batch]
 *   rodata_9e840                             @ 0x0009e840   [INLINED -- G6 literal batch]
 *   rodata_9e8f6                             @ 0x0009e8f6   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_file_msg_pipe                          @ 0x200079a0
 */
/* Reconstructed enqueue_file @ 0x23514  (parity: 300/300 trials, PROVEN) */

extern int k_msgq_get(int, unsigned int, int, int);
extern void safe_memcpy_checked(void*, unsigned int, unsigned int, int);
extern int k_msgq_put(unsigned int, void*, int, int);

int enqueue_file(unsigned int param_1, unsigned int param_2)
{
    int iVar1;
    unsigned char buf[201];

    if (*(volatile int*)(((unsigned long)&g_file_msg_pipe) /*=0x200079a0*/ + 0x24) == 0x1e) {
        k_msgq_get(((unsigned long)&g_file_msg_pipe) /*=0x200079a0*/, buf, 0, 0);
        if (0 < *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/) {
            if (*(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                log_message(((unsigned long)"%s(): enqueue_file is full\n") /*=0x9e824*/, ((unsigned long)"enqueue_file") /*=0x9e8f6*/);
            } else {
                debug_print(((unsigned long)"%s(): enqueue_file is full\n") /*=0x9e824*/, ((unsigned long)"enqueue_file") /*=0x9e8f6*/);
            }
        }
    }
    safe_memcpy_checked(buf, param_1, param_2, 0xc9);
    buf[200] = (unsigned char)param_2;
    iVar1 = k_msgq_put(((unsigned long)&g_file_msg_pipe) /*=0x200079a0*/, buf, 0, 0);
    if ((iVar1 != 0) && (0 < *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/)) {
        if (*(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            log_message(((unsigned long)"%s(): enqueue_file failed\r\n\n") /*=0x9e840*/, ((unsigned long)"enqueue_file") /*=0x9e8f6*/);
        } else {
            debug_print(((unsigned long)"%s(): enqueue_file failed\r\n\n") /*=0x9e840*/, ((unsigned long)"enqueue_file") /*=0x9e8f6*/);
        }
    }
    return iVar1;
}
