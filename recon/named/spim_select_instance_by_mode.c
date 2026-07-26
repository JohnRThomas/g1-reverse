/* readable reconstruction; identity: FUN_00026338 @ 0x00026338
 * public-name: spim_select_instance_by_mode
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   spim_select_instance_by_mode             <= FUN_00026338 @ 0x00026338
 *   nrfx_spim_uninit                         <= FUN_00067248 @ 0x00067248
 * address symbols (name @ address):
 *   rodata_9fb89                             @ 0x0009fb89   [INLINED -- G6 literal batch]
 *   rodata_9fb9f                             @ 0x0009fb9f   [INLINED -- G6 literal batch]
 *   rodata_9fbda                             @ 0x0009fbda   [INLINED -- G6 literal batch]
 *   rodata_9fc79                             @ 0x0009fc79   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Full reconstruction FUN_00026338 @ 0x26338, exact extent 190 bytes.
 * CFG_VERIFY_CALL_ARITIES=1 */
#include <stdint.h>
extern void log_message(uintptr_t,...);
extern void debug_print(uintptr_t,...);
extern void nrfx_spim_uninit(void*);
unsigned spim_select_instance_by_mode(uintptr_t event){
 struct mapping{uint32_t base,tag;};
 struct mapping mode3,mode4;
 mode3.base=0x5000c000u; *(uint8_t *)&mode3.tag=0;
 mode4.base=0x5000a000u; *(uint8_t *)&mode4.tag=1;
 if(*(volatile uint32_t*)(event+0x14)==0)return 0;
 uint32_t mode=*(volatile uint8_t*)(event+0x18);int level=*(volatile int*)0x2000230cu;
 const struct mapping *m;
 if(mode==3)m=&mode3;else if(mode==4)m=&mode4;else{
  if(level>0){int alternate=*(volatile int*)0x20007554u;if(alternate)debug_print(0x0009fb89u,0x0009fc79u,mode,(uint32_t)alternate);else log_message(0x0009fb89u,0x0009fc79u);}return 0;
 }
 *(volatile uint32_t*)(event+0xc)=m->base;*(volatile uint32_t*)(event+0x10)=m->tag;
 if(level>2){
  if(*(volatile int*)0x20007554u)debug_print(0x0009fb9fu,0x0009fc79u,mode,*(uint8_t*)(event+0x1d),*(uint8_t*)(event+0x19),*(uint8_t*)(event+0x1a),*(uint8_t*)(event+0x1b),*(uint8_t*)(event+0x1c));
  else log_message(0x0009fb9fu,0x0009fc79u,mode,*(uint8_t*)(event+0x1d),*(uint8_t*)(event+0x19),*(uint8_t*)(event+0x1a),*(uint8_t*)(event+0x1b),*(uint8_t*)(event+0x1c));
 }
 nrfx_spim_uninit((void*)(event+0xc));
 if(*(volatile int*)0x2000230cu>2){if(*(volatile int*)0x20007554u)debug_print(0x0009fbdau,0x0009fc79u,mode);else log_message(0x0009fbdau,0x0009fc79u,mode);}
 *(volatile uint32_t*)(event+0x14)=0;return 0;
}
