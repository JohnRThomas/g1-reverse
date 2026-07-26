#include "g1_app_symbols.h"
#include "../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_0002e398 @ 0x0002e398
 * public-name: ext_flash_read
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   ext_flash_read                           <= FUN_0002e398 @ 0x0002e398
 *   k_mutex_lock                             <= FUN_000723b8 @ 0x000723b8
 *   k_mutex_unlock                           <= FUN_00072558 @ 0x00072558
 *   ext_flash_sync_noop                      <= FUN_0007c080 @ 0x0007c080
 *   ext_flash_bus_lock_stub                  <= FUN_0007c082 @ 0x0007c082
 * address symbols (name @ address):
 *   rodata_a3a5a                             @ 0x000a3a5a   [INLINED -- G6 literal batch]
 *   rodata_a3ab6                             @ 0x000a3ab6   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_ext_flash_mutex                        @ 0x20007b54
 *   g_ext_flash_dev                          @ 0x20007b68
 */
/* Reconstructed FUN_0002e398 @ 0x2e398  (parity: 300/300 trials, PROVEN) */

extern void k_mutex_lock(unsigned a, int b, unsigned c, unsigned d);
extern void k_mutex_unlock(unsigned a);
extern void ext_flash_sync_noop(void);
extern void ext_flash_bus_lock_stub(void);
int ext_flash_read(int param_1, unsigned param_2, unsigned param_3, unsigned param_4){
    volatile unsigned char *r5 = (volatile unsigned char*)(param_1 + 0x1000);
    int iVar2 = (int)((unsigned)*(volatile unsigned short*)(r5 + 0x5c) << 0x1b);
    if (iVar2 >= 0) ext_flash_sync_noop();
    volatile int *g = (volatile int*)((unsigned long)&g_ext_flash_dev) /*=0x20007b68*/;
    if (*g == 0){
        int t = (int)((unsigned)*(volatile unsigned short*)(r5 + 0x5c) << 0x1b);
        if (t >= 0) ext_flash_bus_lock_stub();
        return 0;
    }
    k_mutex_lock(((unsigned long)&g_ext_flash_mutex) /*=0x20007b54*/, iVar2, 0xffffffffu, 0xffffffffu);
    int r0v = *g;
    int r3v = *(volatile int*)(r0v + 8);
    typedef int (*fn_t)(int, unsigned, unsigned, unsigned);
    fn_t f = *(volatile fn_t*)(r3v + 0);
    int res = f(r0v, param_2, param_3, param_4);
    k_mutex_unlock(((unsigned long)&g_ext_flash_mutex) /*=0x20007b54*/);
    int t2 = (int)((unsigned)*(volatile unsigned short*)(r5 + 0x5c) << 0x1b);
    if (t2 >= 0) ext_flash_bus_lock_stub();
    if (res == 0) return 0;
    if (*(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/ < 1) return res;
    if (*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ != 0){
        debug_print(((unsigned long)"%s(): flash read fail!\n") /*=0xa3a5a*/, ((unsigned long)"ext_flash_read") /*=0xa3ab6*/);
        return res;
    }
    log_message(((unsigned long)"%s(): flash read fail!\n") /*=0xa3a5a*/, ((unsigned long)"ext_flash_read") /*=0xa3ab6*/);
    return res;
}
