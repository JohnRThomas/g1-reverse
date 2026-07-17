#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0005f4d4 @ 0x0005f4d4
 * public-name: net_buf_simple_reserve
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   net_buf_simple_reserve                   <= FUN_0005f4d4 @ 0x0005f4d4
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f45be                             @ 0x000f45be
 *   rodata_f543a                             @ 0x000f543a
 *   rodata_f5465                             @ 0x000f5465
 */
/* Reconstructed FUN_0005f4d4 @ 0x5f4d4  (parity: 300/300 trials, PROVEN) */

extern void printk(unsigned int, unsigned int, unsigned int, unsigned int);
extern unsigned long long assert_post_action(unsigned int, unsigned int);

static void merge_tail(unsigned int r0, unsigned int r1)
{
    unsigned short chk = *(volatile unsigned short*)((char*)r0 + 4);
    if (chk == 0) {
        unsigned int val8 = *(volatile unsigned int*)((char*)r0 + 8);
        unsigned int result = val8 + r1;
        *(volatile unsigned int*)r0 = result;
    }
}

void net_buf_simple_reserve(int *param_1, int param_2, unsigned int param_3, unsigned int param_4)
{
    if (param_1 == (int*)0) {
        printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f45be) /*=0xf45be*/, ((unsigned long)&rodata_f543a) /*=0xf543a*/, 0x2bUL);
        unsigned long long rv = assert_post_action(((unsigned long)&rodata_f543a) /*=0xf543a*/, 0x2bUL);
        merge_tail((unsigned int)rv, (unsigned int)(rv >> 32));
        return;
    }
    short shortval = *(volatile short*)((char*)param_1 + 4);
    if (shortval == 0) {
        *param_1 = param_1[2] + param_2;
        return;
    }
    printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f5465) /*=0xf5465*/, ((unsigned long)&rodata_f543a) /*=0xf543a*/, 0x2cUL);
    unsigned long long rv = assert_post_action(((unsigned long)&rodata_f543a) /*=0xf543a*/, 0x2cUL);
    merge_tail((unsigned int)rv, (unsigned int)(rv >> 32));
}
