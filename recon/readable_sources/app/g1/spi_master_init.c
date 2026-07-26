#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00026418 @ 0x00026418
 * public-name: spi_master_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   spi_master_init                          <= FUN_00026418 @ 0x00026418
 *   arch_irq_priority_set                    <= FUN_0005010c @ 0x0005010c
 *   nrfx_spim_init                           <= FUN_000671d8 @ 0x000671d8
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_883b0                             @ 0x000883b0
 *   rodata_883b4                             @ 0x000883b4
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_9fb89                             @ 0x0009fb89   [INLINED -- G6 literal batch]
 *   rodata_9fb9f                             @ 0x0009fb9f   [INLINED -- G6 literal batch]
 *   rodata_9fbfd                             @ 0x0009fbfd   [INLINED -- G6 literal batch]
 *   rodata_9fc15                             @ 0x0009fc15   [INLINED -- G6 literal batch]
 *   rodata_9fc2c                             @ 0x0009fc2c   [INLINED -- G6 literal batch]
 *   rodata_9fc4d                             @ 0x0009fc4d   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_20018c6c                               @ 0x20018c6c
 *   g_20018c6d                               @ 0x20018c6d
 */
/* Full reconstruction FUN_00026418 @ 0x26418, exact extent 320 bytes.
 * CFG_VERIFY_CALL_ARITIES=3,4,2 */
#include <stdint.h>
#include "../../../headers/g1_log.h"
extern void arch_irq_priority_set(uint32_t,uint32_t);
extern uint32_t nrfx_spim_init(void*,void*,uintptr_t,uintptr_t);
extern void assert_post_action(uintptr_t,uint32_t);
extern void memset_bytes(void*,int,uint32_t);
struct spi_map { uint32_t base, tag; };
unsigned spi_master_init(uintptr_t event)
{
    struct spi_map mode3;
    mode3.base=0x5000c000u; *(uint8_t *)&mode3.tag=0;
    struct spi_map mode4;
    mode4.base=*(volatile uint32_t*)((unsigned long)&rodata_883b0) /*=0x883b0*/;
    *(uint32_t*)((uint8_t*)&mode4+4)=*(volatile uint32_t*)((unsigned long)&rodata_883b4) /*=0x883b4*/;
    uint32_t cfg[10];
    memset_bytes(&cfg,0,0x28);
    cfg[4]=0x00ff0700u;
    cfg[7]=0xffffffffu;
    cfg[8]=0x00020002u;
    if(*(volatile uint32_t*)(event+0x14)==1)return 0;
    cfg[5]=*(volatile uint8_t*)(event+0x1d)*1000000u;
    uint32_t mode=*(volatile uint8_t*)(event+0x18);
    cfg[0]=*(volatile uint8_t*)(event+0x19);
    cfg[1]=*(volatile uint8_t*)(event+0x1a);
    cfg[2]=*(volatile uint8_t*)(event+0x1b);
    cfg[3]=*(volatile uint8_t*)(event+0x1c);
    int level=*(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/;
    struct spi_map *map;
    if(mode==3)map=&mode3; else if(mode==4)map=&mode4; else {
        if(level>0){int alt=*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;if(alt)debug_print(((unsigned long)"%s():  SPIM BUS ERR!\n") /*=0x9fb89*/,((unsigned long)"spi_master_init") /*=0x9fc4d*/,mode,(uint32_t)alt);else log_message(((unsigned long)"%s():  SPIM BUS ERR!\n") /*=0x9fb89*/,((unsigned long)"spi_master_init") /*=0x9fc4d*/);} return 0;
    }
    *(volatile uint32_t*)(event+0xc)=map->base;
    *(volatile uint32_t*)(event+0x10)=map->tag;
    if(level>2){
        if(*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)debug_print(((unsigned long)"%s(): *SPIM(%d)speed=%dM, sck=%d, mosi=%d, miso=%d, ss=%d\n") /*=0x9fb9f*/,((unsigned long)"spi_master_init") /*=0x9fc4d*/,mode,*(uint8_t*)(event+0x1d),*(uint8_t*)(event+0x19),*(uint8_t*)(event+0x1a),*(uint8_t*)(event+0x1b),*(uint8_t*)(event+0x1c));
        else log_message(((unsigned long)"%s(): *SPIM(%d)speed=%dM, sck=%d, mosi=%d, miso=%d, ss=%d\n") /*=0x9fb9f*/,((unsigned long)"spi_master_init") /*=0x9fc4d*/,mode,*(uint8_t*)(event+0x1d),*(uint8_t*)(event+0x19),*(uint8_t*)(event+0x1a),*(uint8_t*)(event+0x1b),*(uint8_t*)(event+0x1c));
    }
    uintptr_t callback=mode==3?0x0007ca77u:0;
    uintptr_t callback_context=mode==3?event:0;
    if(nrfx_spim_init((void*)(event+0xc),&cfg,callback,callback_context)!=0x0bad0000u){
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)"status == NRFX_SUCCESS") /*=0x9fc15*/,((unsigned long)"../src/spim_spis/spim.c") /*=0x9fbfd*/,0x68);
        assert_post_action(((unsigned long)"../src/spim_spis/spim.c") /*=0x9fbfd*/,0x68);
    }
    volatile uint8_t *once=(volatile uint8_t*)(mode==3?((unsigned long)&g_20018c6c) /*=0x20018c6c*/:((unsigned long)&g_20018c6d) /*=0x20018c6d*/);
    if(!*once){*once=1;arch_irq_priority_set(mode==3?12:10,6);}
    if(*(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/>2){if(*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)debug_print(((unsigned long)"%s(): spim(bus=%d): init finish\n") /*=0x9fc2c*/,((unsigned long)"spi_master_init") /*=0x9fc4d*/,mode);else log_message(((unsigned long)"%s(): spim(bus=%d): init finish\n") /*=0x9fc2c*/,((unsigned long)"spi_master_init") /*=0x9fc4d*/,mode);}
    *(volatile uint32_t*)(event+0x14)=1;
    return 0;
}
