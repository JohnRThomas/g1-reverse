#include "g1_app_symbols.h"
#include "../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_0005f594 @ 0x0005f594
 * public-name: net_buf_simple_pull_5f594
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   net_buf_simple_pull_5f594                <= FUN_0005f594 @ 0x0005f594
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f543a                             @ 0x000f543a   [INLINED -- G6 literal batch]
 *   rodata_f5474                             @ 0x000f5474   [INLINED -- G6 literal batch]
 */
/* Reconstructed FUN_0005f594 @ 0x5f594  (parity: 300/300 trials, PROVEN) */

extern unsigned long long assert_post_action(unsigned int, unsigned int);

void net_buf_simple_pull_5f594(int *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned short ushort_val = *(unsigned short*)((char*)param_1 + 4);
    unsigned int loaded = *(unsigned int*)param_1;
    if (ushort_val < param_2) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)"buf->len >= len") /*=0xf5474*/, ((unsigned long)"WEST_TOPDIR/zephyr/subsys/net/buf_simple.c") /*=0xf543a*/, 0x199U, param_4);
        unsigned long long rv = assert_post_action(((unsigned long)"WEST_TOPDIR/zephyr/subsys/net/buf_simple.c") /*=0xf543a*/, 0x199U);
        unsigned int r0v = (unsigned int)rv;
        unsigned int r1v = (unsigned int)(rv >> 32);
        unsigned int r2v = ((unsigned long)"WEST_TOPDIR/zephyr/subsys/net/buf_simple.c") /*=0xf543a*/ - r1v;
        unsigned int r1final = r1v + r0v;
        *(volatile unsigned short*)0x19dUL = (unsigned short)r2v;
        *(volatile unsigned int*)0x199UL = r1final;
        return;
    }
    *(unsigned short*)((char*)param_1 + 4) = (unsigned short)(ushort_val - param_2);
    *param_1 = param_2 + loaded;
    return;
}
