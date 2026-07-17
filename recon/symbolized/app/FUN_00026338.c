#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00026338 @ 0x00026338
 * public-name: FUN_00026338
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 * address symbols (name @ address):
 *   rodata_9fb89                             @ 0x0009fb89
 *   rodata_9fb9f                             @ 0x0009fb9f
 *   rodata_9fbda                             @ 0x0009fbda
 *   rodata_9fc79                             @ 0x0009fc79
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Full reconstruction FUN_00026338 @ 0x26338, exact extent 190 bytes.
 * CFG_VERIFY_CALL_ARITIES=1 */
#include <stdint.h>
extern void log_message(uintptr_t,...);
extern void debug_print(uintptr_t,...);
extern void FUN_00067248(void*);
unsigned FUN_00026338(uintptr_t event){
 struct mapping{uint32_t base,tag;};
 struct mapping mode3,mode4;
 mode3.base=0x5000c000u; *(uint8_t *)&mode3.tag=0;
 mode4.base=0x5000a000u; *(uint8_t *)&mode4.tag=1;
 if(*(volatile uint32_t*)(event+0x14)==0)return 0;
 uint32_t mode=*(volatile uint8_t*)(event+0x18);int level=*(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/;
 const struct mapping *m;
 if(mode==3)m=&mode3;else if(mode==4)m=&mode4;else{
  if(level>0){int alternate=*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;if(alternate)debug_print(((unsigned long)&rodata_9fb89) /*=0x9fb89*/,((unsigned long)&rodata_9fc79) /*=0x9fc79*/,mode,(uint32_t)alternate);else log_message(((unsigned long)&rodata_9fb89) /*=0x9fb89*/,((unsigned long)&rodata_9fc79) /*=0x9fc79*/);}return 0;
 }
 *(volatile uint32_t*)(event+0xc)=m->base;*(volatile uint32_t*)(event+0x10)=m->tag;
 if(level>2){
  if(*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)debug_print(((unsigned long)&rodata_9fb9f) /*=0x9fb9f*/,((unsigned long)&rodata_9fc79) /*=0x9fc79*/,mode,*(uint8_t*)(event+0x1d),*(uint8_t*)(event+0x19),*(uint8_t*)(event+0x1a),*(uint8_t*)(event+0x1b),*(uint8_t*)(event+0x1c));
  else log_message(((unsigned long)&rodata_9fb9f) /*=0x9fb9f*/,((unsigned long)&rodata_9fc79) /*=0x9fc79*/,mode,*(uint8_t*)(event+0x1d),*(uint8_t*)(event+0x19),*(uint8_t*)(event+0x1a),*(uint8_t*)(event+0x1b),*(uint8_t*)(event+0x1c));
 }
 FUN_00067248((void*)(event+0xc));
 if(*(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/>2){if(*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)debug_print(((unsigned long)&rodata_9fbda) /*=0x9fbda*/,((unsigned long)&rodata_9fc79) /*=0x9fc79*/,mode);else log_message(((unsigned long)&rodata_9fbda) /*=0x9fbda*/,((unsigned long)&rodata_9fc79) /*=0x9fc79*/,mode);}
 *(volatile uint32_t*)(event+0x14)=0;return 0;
}
