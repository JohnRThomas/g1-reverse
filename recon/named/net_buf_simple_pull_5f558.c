/* readable reconstruction; identity: FUN_0005f558 @ 0x0005f558
 * public-name: net_buf_simple_pull_5f558
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   net_buf_simple_pull_5f558                <= FUN_0005f558 @ 0x0005f558
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f543a                             @ 0x000f543a   [INLINED -- G6 literal batch]
 *   rodata_f5474                             @ 0x000f5474   [INLINED -- G6 literal batch]
 */
#include "../headers/g1_log.h"
/* Reconstructed FUN_0005f558 @ 0x5f558  (parity: 300/300 trials, PROVEN) */

extern unsigned long long assert_post_action(unsigned int, unsigned int);

void net_buf_simple_pull_5f558(int *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned short ushort_val = *(unsigned short*)((char*)param_1 + 4);
    if (ushort_val < param_2) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), 0xf5474U, 0xf543aU, 0x18dU, param_4);
        unsigned long long rv = assert_post_action(0xf543aU, 0x18dU);
        unsigned int r0v = (unsigned int)rv;
        unsigned int r1v = (unsigned int)(rv >> 32);
        unsigned int r2v = 0xf543aU - r1v;
        *(volatile unsigned short*)(r0v + 4) = (unsigned short)r2v;
        unsigned int memv = *(volatile unsigned int*)r0v;
        unsigned int finalv = memv + r1v;
        *(volatile unsigned int*)0x18dUL = finalv;
        return;
    }
    *(unsigned short*)((char*)param_1 + 4) = (unsigned short)(ushort_val - param_2);
    *param_1 = *param_1 + param_2;
    return;
}
