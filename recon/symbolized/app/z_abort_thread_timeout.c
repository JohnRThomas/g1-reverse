#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00074274 @ 0x00074274
 * public-name: z_abort_thread_timeout
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   dlist_unlink_node                        <= FUN_00073cdc @ 0x00073cdc
 *   z_abort_thread_timeout                   <= FUN_00074274 @ 0x00074274
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f82f4                             @ 0x000f82f4
 *   rodata_f85bb                             @ 0x000f85bb
 */
/* Reconstructed FUN_00074274 @ 0x74274  (parity: 300/300 trials, PROVEN) */

extern void dlist_unlink_node(int, int);
extern void printk(unsigned int, unsigned int, unsigned int, unsigned int);
extern unsigned long long assert_post_action(unsigned int, unsigned int);

void z_abort_thread_timeout(int param_1)
{
    int v8 = *(volatile int*)(param_1 + 8);
    int r0;
    if (v8 == 0) {
        printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f85bb) /*=0xf85bb*/, ((unsigned long)&rodata_f82f4) /*=0xf82f4*/, 0x2d2UL);
        unsigned long long rv = assert_post_action(((unsigned long)&rodata_f82f4) /*=0xf82f4*/, 0x2d2UL);
        r0 = (int)rv;
    } else {
        r0 = v8;
    }
    dlist_unlink_node(r0, param_1);
    unsigned char b = *(volatile unsigned char*)(param_1 + 0xd);
    *(volatile unsigned char*)(param_1 + 0xd) = b & 0xfd;
    *(volatile int*)(param_1 + 8) = 0;
}
