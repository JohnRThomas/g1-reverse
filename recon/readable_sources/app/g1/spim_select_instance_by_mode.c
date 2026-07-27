#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_spi_bus_config__param_0065             [param_0065; G1-original]
 * Raw function identity: 0x00026338.  See ../include/g1_recovered_layouts.h. */
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
#include "../../../headers/g1_log.h"
extern void nrfx_spim_uninit(void*);
unsigned spim_select_instance_by_mode(uintptr_t event){
 struct mapping{uint32_t base,tag;};
 struct mapping mode3,mode4;
 mode3.base=0x5000c000u; *(uint8_t *)&mode3.tag=0;
 mode4.base=0x5000a000u; *(uint8_t *)&mode4.tag=1;
 if(*(volatile uint32_t*)(event+0x14)==0)return 0;
 uint32_t mode=*(volatile uint8_t*)(event+0x18);int level=*(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/;
 const struct mapping *m;
 if(mode==3)m=&mode3;else if(mode==4)m=&mode4;else{
  if(level>0){int alternate=*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;if(alternate)debug_print(((unsigned long)"%s():  SPIM BUS ERR!\n") /*=0x9fb89*/,((unsigned long)"spi_master_deinit") /*=0x9fc79*/);else log_message(((unsigned long)"%s():  SPIM BUS ERR!\n") /*=0x9fb89*/,((unsigned long)"spi_master_deinit") /*=0x9fc79*/);}return 0;
 }
 *(volatile uint32_t*)(event+0xc)=m->base;*(volatile uint32_t*)(event+0x10)=m->tag;
 if(level>2){
  if(*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)debug_print(((unsigned long)"%s(): *SPIM(%d)speed=%dM, sck=%d, mosi=%d, miso=%d, ss=%d\n") /*=0x9fb9f*/,((unsigned long)"spi_master_deinit") /*=0x9fc79*/,mode,*(uint8_t*)(event+0x1d),*(uint8_t*)(event+0x19),*(uint8_t*)(event+0x1a),*(uint8_t*)(event+0x1b),*(uint8_t*)(event+0x1c));
  else log_message(((unsigned long)"%s(): *SPIM(%d)speed=%dM, sck=%d, mosi=%d, miso=%d, ss=%d\n") /*=0x9fb9f*/,((unsigned long)"spi_master_deinit") /*=0x9fc79*/,mode,*(uint8_t*)(event+0x1d),*(uint8_t*)(event+0x19),*(uint8_t*)(event+0x1a),*(uint8_t*)(event+0x1b),*(uint8_t*)(event+0x1c));
 }
 nrfx_spim_uninit((void*)(event+0xc));
 if(*(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/>2){if(*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)debug_print(((unsigned long)"%s(): spim(bus=%d): uninit finish\n") /*=0x9fbda*/,((unsigned long)"spi_master_deinit") /*=0x9fc79*/,mode);else log_message(((unsigned long)"%s(): spim(bus=%d): uninit finish\n") /*=0x9fbda*/,((unsigned long)"spi_master_deinit") /*=0x9fc79*/,mode);}
 *(volatile uint32_t*)(event+0x14)=0;return 0;
}
