#include "g1_app_symbols.h"
#include "../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_0005f390 @ 0x0005f390
 * public-name: net_buf_frag_add
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   net_buf_ref                              <= FUN_0005f2d4 @ 0x0005f2d4
 *   net_buf_frag_last                        <= FUN_0005f304 @ 0x0005f304
 *   net_buf_frag_insert                      <= FUN_0005f338 @ 0x0005f338
 *   net_buf_frag_add                         <= FUN_0005f390 @ 0x0005f390
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f539a                             @ 0x000f539a
 *   rodata_f542d                             @ 0x000f542d
 */
/* Reconstructed FUN_0005f390 @ 0x5f390  (parity: 300/300 trials, PROVEN) */

extern int net_buf_ref(int a, int b, unsigned int c, unsigned int d);
extern unsigned int net_buf_frag_last(void);
extern void net_buf_frag_insert(unsigned int a, int b);
extern int assert_post_action(int, int);

int net_buf_frag_add(int param_1, int param_2, unsigned int param_3, unsigned int param_4)
{
    int iVar1;
    unsigned int uVar2;

    if (param_2 == 0) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)&rodata_f542d) /*=0xf542d*/, ((unsigned long)&rodata_f539a) /*=0xf539a*/, 0x24d);
        assert_post_action(((unsigned long)&rodata_f539a) /*=0xf539a*/, 0x24d);
    }
    if (param_1 == 0) {
        iVar1 = net_buf_ref(param_2, param_2, param_3, param_4);
        return iVar1;
    }
    uVar2 = net_buf_frag_last();
    net_buf_frag_insert(uVar2, param_2);
    return param_1;
}
