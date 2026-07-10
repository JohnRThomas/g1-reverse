#include "g1_app_symbols.h"
/* named: settings_register */
/* globals referenced:
//   0x000882b0  __settings_handler_static_list_start 
//   0x00088328  __settings_handler_static_list_end 
//   0x20003868  g_settings_lock              
//   0x2000a10c  g_settings_handlers          
*/
/* Reconstructed settings_register @ 0x4e494  (parity: 300/300 trials, PROVEN) */

extern unsigned long long strcmp(unsigned a, unsigned b);
extern void k_mutex_lock(unsigned a, unsigned b, unsigned c, unsigned d);
extern void k_mutex_unlock(unsigned a);
extern void assert_post_action(unsigned a, unsigned b);
extern void printk(unsigned a, unsigned b, unsigned c, unsigned d);

unsigned settings_register(unsigned *param_1, unsigned param_2){
    unsigned r5 = (unsigned)param_1;
    unsigned r4 = ((uintptr_t)&__settings_handler_static_list_start) /*=0x882b0*/;
    unsigned r6 = ((uintptr_t)&__settings_handler_static_list_end) /*=0x88328*/;
    for(;;){
        if (r4 <= r6){
            if (!(r4 < r6)) break;
        } else {
            printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"ch <= _settings_handler_static_list_end" /*=0xf1158*/,"WEST_TOPDIR/zephyr/subsys/settings/src/settings.c" /*=0xf1126*/,0x2b);
            printk("\tunexpected list end location\n" /*=0xf0d20*/,0,0,0);
            assert_post_action("WEST_TOPDIR/zephyr/subsys/settings/src/settings.c" /*=0xf1126*/,0x2b);
        }
        unsigned long long uv = strcmp(*(volatile unsigned*)r5, *(volatile unsigned*)r4);
        param_2 = (unsigned)(uv>>32);
        if ((unsigned)uv == 0) return 0xffffffefU;
        r4 += 0x14;
    }
    k_mutex_lock(((uintptr_t)&g_settings_lock) /*=0x20003868*/, param_2, 0xffffffffU, 0xffffffffU);
    volatile unsigned *piVar2 = (volatile unsigned*)((uintptr_t)&g_settings_handlers) /*=0x2000a10c*/;
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
    k_mutex_unlock(((uintptr_t)&g_settings_lock) /*=0x20003868*/);
    return r4res;
}

