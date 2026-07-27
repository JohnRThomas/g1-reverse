#include "g1_app_symbols.h"
#include "../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_0004e494 @ 0x0004e494
 * public-name: settings_register
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   strcmp                                   <= FUN_0000eefe @ 0x0000eefe
 *   settings_register                        <= FUN_0004e494 @ 0x0004e494
 *   k_mutex_lock                             <= FUN_000723b8 @ 0x000723b8
 *   k_mutex_unlock                           <= FUN_00072558 @ 0x00072558
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   __settings_handler_static_list_start     @ 0x000882b0
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f0d20                             @ 0x000f0d20   [INLINED -- G6 literal batch]
 *   rodata_f1126                             @ 0x000f1126
 *   rodata_f1158                             @ 0x000f1158   [INLINED -- G6 literal batch]
 *   g_settings_lock                          @ 0x20003868
 *   g_settings_handlers                      @ 0x2000a10c
 */
/* Reconstructed FUN_0004e494 @ 0x4e494  (parity: 300/300 trials, PROVEN) */

extern unsigned long long strcmp(unsigned a, unsigned b);
extern void k_mutex_lock(unsigned a, unsigned b, unsigned c, unsigned d);
extern int k_mutex_unlock(unsigned int);
extern int assert_post_action(int, int);

unsigned settings_register(unsigned *param_1, unsigned param_2){
    unsigned r5 = (unsigned)param_1;
    unsigned r4 = ((unsigned long)&__settings_handler_static_list_start) /*=0x882b0*/;
    unsigned r6 = 0x00088328UL;
    for(;;){
        if (r4 <= r6){
            if (!(r4 < r6)) break;
        } else {
            printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)"ch <= _settings_handler_static_list_end") /*=0xf1158*/,((unsigned long)&rodata_f1126) /*=0xf1126*/,0x2b);
            printk(((unsigned long)"\tunexpected list end location\n") /*=0xf0d20*/,0,0,0);
            assert_post_action(((unsigned long)&rodata_f1126) /*=0xf1126*/,0x2b);
        }
        unsigned long long uv = strcmp(*(volatile unsigned*)r5, *(volatile unsigned*)r4);
        param_2 = (unsigned)(uv>>32);
        if ((unsigned)uv == 0) return 0xffffffefU;
        r4 += 0x14;
    }
    k_mutex_lock(((unsigned long)&g_settings_lock) /*=0x20003868*/, param_2, 0xffffffffU, 0xffffffffU);
    volatile unsigned *piVar2 = (volatile unsigned*)((unsigned long)&g_settings_handlers) /*=0x2000a10c*/;
    unsigned r4b = piVar2[0];
    unsigned r4res;
    for(;;){
        if (r4b == 0){
            *(volatile unsigned*)(r5+0x14) = 0;
            unsigned r2 = piVar2[1];
            unsigned r3 = r5 + 0x14;
            if (r2 != 0){
                *(volatile unsigned*)r2 = r3;
                piVar2[1] = r3;
            } else {
                piVar2[0] = r3;
                piVar2[1] = r3;
            }
            r4res = 0;
            goto unlock;
        }
        unsigned long long uv2 = strcmp(*(volatile unsigned*)r5, *(volatile unsigned*)(r4b-0x14));
        if ((unsigned)uv2 == 0){ r4res = 0xffffffefU; goto unlock; }
        r4b = *(volatile unsigned*)r4b;
    }
unlock:
    k_mutex_unlock(((unsigned long)&g_settings_lock) /*=0x20003868*/);
    return r4res;
}
