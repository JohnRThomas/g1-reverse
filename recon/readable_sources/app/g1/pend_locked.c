#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00073f3c @ 0x00073f3c
 * public-name: pend_locked
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   add_thread_to_wait_queue                 <= FUN_00073ec0 @ 0x00073ec0
 *   pend_locked                              <= FUN_00073f3c @ 0x00073f3c
 *   z_add_timeout                            <= FUN_00074bf4 @ 0x00074bf4
 * address symbols (name @ address):
 *   rodata_86661                             @ 0x00086661
 */
/* Reconstructed FUN_00073f3c @ 0x73f3c  (parity: 300/300 trials, PROVEN) */

extern void add_thread_to_wait_queue(void);
extern void z_add_timeout(int, unsigned int, int, int);

void pend_locked(int param_1, unsigned int param_2, int param_3, int param_4)
{
    add_thread_to_wait_queue();
    if (param_4 != -1 || param_3 != -1) {
        z_add_timeout(param_1 + 0x18, ((unsigned long)&rodata_86661) /*=0x86661*/, param_3, param_4);
        return;
    }
    return;
}
