#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00065584 @ 0x00065584
 * public-name: FUN_00065584
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f09d1                             @ 0x000f09d1
 *   rodata_f0a04                             @ 0x000f0a04
 *   rodata_f7a30                             @ 0x000f7a30
 */
/* Full reconstruction FUN_00065584 @ 0x65584, exact extent 80 bytes. */
#include <stdint.h>
extern uint64_t FUN_000850f6(uint32_t,void*,uint32_t,uint32_t,uint32_t);
extern void printk(uintptr_t,uintptr_t,uintptr_t,uint32_t,...);
extern __attribute__((noreturn)) void assert_post_action(uintptr_t,uint32_t);
uintptr_t FUN_00065584(uint32_t *descriptor,uint32_t a,uint32_t b,uint32_t context){
 (void)a;(void)b; uint32_t encoded=*descriptor;
 uint64_t slot=FUN_000850f6(encoded,descriptor,encoded,context,context);
 if((uint32_t)slot==0){printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/,((unsigned long)&rodata_f0a04) /*=0xf0a04*/,((unsigned long)&rodata_f09d1) /*=0xf09d1*/,0x32f);assert_post_action(((unsigned long)&rodata_f09d1) /*=0xf09d1*/,0x32f);}
 *(uint32_t*)(uintptr_t)(slot>>32)=encoded&0x1f;
 if((encoded>>5)==0)return 0x50842500u;
 if((encoded>>5)==1)return 0x50842800u;
 printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/,((unsigned long)&rodata_f7a30) /*=0xf7a30*/,((unsigned long)&rodata_f09d1) /*=0xf09d1*/,0x338);assert_post_action(((unsigned long)&rodata_f09d1) /*=0xf09d1*/,0x338);
}
