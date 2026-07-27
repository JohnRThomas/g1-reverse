#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0005e83c @ 0x0005e83c
 * public-name: bt_keys_find_irk
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_keys_find_irk                         <= FUN_0005e83c @ 0x0005e83c
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   bt_smp_ah                                <= FUN_00080ca0 @ 0x00080ca0
 *   memcmp                                   <= FUN_00086be4 @ 0x00086be4
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f5268                             @ 0x000f5268
 *   rodata_f52ac                             @ 0x000f52ac   [INLINED -- G6 literal batch]
 *   bt_keys_pool                             @ 0x2000af4c
 *   bt_keys_pool_0_irk                       @ 0x2000af76
 *   bt_keys_pool_1_irk                       @ 0x2000afd2
 *   bt_keys_pool_1_addr                      @ 0x2000afe2
 */
/* Reconstructed FUN_0005e83c @ 0x5e83c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../../headers/g1_log.h"
typedef unsigned int uint;
extern int assert_post_action(int, int);
extern int bt_smp_ah(uint,void*);
extern int memcmp(const void*, const void*, unsigned long);
uint8_t* bt_keys_find_irk(uint param_1, uint8_t* param_2, uint param_3, uint param_4){
    volatile uint8_t* r4=(volatile uint8_t*)((unsigned long)&bt_keys_pool) /*=0x2000af4c*/;
    int r3int; uint8_t* r7;
    if(param_2==0){
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)"addr != ((void *)0)") /*=0xf52ac*/,((unsigned long)&rodata_f5268) /*=0xf5268*/,0xe9u);
        assert_post_action(((unsigned long)&rodata_f5268) /*=0xf5268*/,0xe9);
    }
    if(*(volatile uint8_t*)param_2 != 1) return 0;
    if((param_2[6]&0xc0) != 0x40) return 0;
    if(((uint)*(volatile uint16_t*)(r4+0xe)<<0x1e)&0x80000000u) goto L894;
    if(!(((uint)*(volatile uint16_t*)(r4+0x6a)<<0x1e)&0x80000000u)) return 0;
    if((uint)*(volatile uint8_t*)(r4+0x5c) != param_1) goto L8aa;
    if(memcmp(param_2+1,((unsigned long)&bt_keys_pool) /*=0x2000af4c*/+0x96,6)!=0) goto L8a2;
    goto L8fe;
L894:
    if((uint)*(volatile uint8_t*)r4 == param_1) goto L8d4;
    if(((uint)*(volatile uint16_t*)(r4+0x6a)<<0x1e)&0x80000000u) goto L8ea;
L8a2:
    if(!(((uint)*(volatile uint16_t*)(r4+0x6a)<<0x1e)&0x80000000u)) return 0;
L8aa:
    if((uint)*(volatile uint8_t*)(r4+0x5c) != param_1) return 0;
    r7=param_2+1;
    if(bt_smp_ah(((unsigned long)&bt_keys_pool_1_irk) /*=0x2000afd2*/,r7)==0) return 0;
    r3int=0x5c;
L8c2:
    {
        uint32_t v=*(volatile uint32_t*)r7;
        *(volatile uint32_t*)((int)r4+r3int+0x3a)=v;
        uint16_t h=*(volatile uint16_t*)(r7+4);
        uint8_t* ret=(uint8_t*)((int)r4+r3int);
        *(volatile uint16_t*)((int)r4+r3int+0x3e)=h;
        return ret;
    }
L8d4:
    if(memcmp(param_2+1,((unsigned long)&bt_keys_pool) /*=0x2000af4c*/+0x3a,6)==0) return (uint8_t*)((int)r4+0);
    if(!(((uint)*(volatile uint16_t*)(r4+0x6a)<<0x1e)&0x80000000u)) goto L904;
L8ea:
    if((uint)*(volatile uint8_t*)(r4+0x5c) != param_1) goto L904;
    if(memcmp(param_2+1,((unsigned long)&bt_keys_pool_1_addr) /*=0x2000afe2*/,6)!=0) goto L904;
L8fe:
    return (uint8_t*)((int)r4+0x5c);
L904:
    if((uint)*(volatile uint8_t*)r4 != param_1) goto L8a2;
    r7=param_2+1;
    if(bt_smp_ah(((unsigned long)&bt_keys_pool_0_irk) /*=0x2000af76*/,r7)==0) goto L8a2;
    r3int=0;
    goto L8c2;
}
