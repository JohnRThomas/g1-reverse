#include "g1_app_symbols.h"
#include "../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_000681cc @ 0x000681cc
 * public-name: metal_device_close
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   metal_device_close                       <= FUN_000681cc @ 0x000681cc
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f7a9f                             @ 0x000f7a9f
 *   rodata_f7ad6                             @ 0x000f7ad6
 */
/* Reconstructed FUN_000681cc @ 0x681cc  (parity: 300/300 trials, PROVEN) */

extern int assert_post_action(int, int);
typedef void (*fn2_t)(int,int);
void metal_device_close(int param_1)
{
    int iVar1;
    if ((param_1 != 0) && ((iVar1 = *(volatile int*)(param_1 + 4)) != 0)) {
        fn2_t f = *(volatile fn2_t*)(iVar1 + 0xc);
        if (f != 0) {
            f(iVar1, param_1);
            return;
        }
        return;
    }
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)&rodata_f7ad6) /*=0xf7ad6*/, ((unsigned long)&rodata_f7a9f) /*=0xf7a9f*/, 0x51);
    assert_post_action(((unsigned long)&rodata_f7a9f) /*=0xf7a9f*/, 0x51);
}
