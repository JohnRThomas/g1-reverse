#include "g1_app_symbols.h"
#include "../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_0005f200 @ 0x0005f200
 * public-name: net_buf_put
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   net_buf_put                              <= FUN_0005f200 @ 0x0005f200
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   net_pkt_skip                             <= FUN_00086502 @ 0x00086502
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f45be                             @ 0x000f45be
 *   rodata_f539a                             @ 0x000f539a
 *   rodata_f5402                             @ 0x000f5402   [INLINED -- G6 literal batch]
 */
/* Reconstructed FUN_0005f200 @ 0x5f200  (parity: 300/300 trials, PROVEN) */

extern unsigned long long assert_post_action(unsigned int a, unsigned int b);
extern void net_pkt_skip(int);

void net_buf_put(int param_1, int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned int uVar1;

    if (param_1 == 0) {
        unsigned long long r;
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)"fifo") /*=0xf5402*/, ((unsigned long)&rodata_f539a) /*=0xf539a*/, 0x1c7);
        uVar1 = 0x1c7;
        r = assert_post_action(((unsigned long)&rodata_f539a) /*=0xf539a*/, uVar1);
        param_1 = (int)r; param_2 = (int)(r >> 32);
    }
    if (param_2 == 0) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)&rodata_f45be) /*=0xf45be*/, ((unsigned long)&rodata_f539a) /*=0xf539a*/, 0x1c8);
        uVar1 = 0x1c8;
        {
          unsigned long long r = assert_post_action(((unsigned long)&rodata_f539a) /*=0xf539a*/, uVar1);
          param_1 = (int)r; param_2 = (int)(r >> 32);
        }
    }
    net_pkt_skip(param_1);
}
