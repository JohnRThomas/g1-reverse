#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_panel_ctx__param_0117                  [param_0117; G1-original]
 * Raw function identity: 0x00046dd8.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00046dd8 @ 0x00046dd8
 * public-name: panel_on
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   power_for_panel                          <= FUN_00015df4 @ 0x00015df4
 *   get_ambient_light_sensor_ready_flag      <= FUN_0001655c @ 0x0001655c
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   opt3007_chip_init                        <= FUN_0002e67c @ 0x0002e67c
 *   panel_init                               <= FUN_00047538 @ 0x00047538
 * address symbols (name @ address):
 *   rodata_d723a                             @ 0x000d723a   [INLINED -- G6 literal batch]
 *   rodata_d72bb                             @ 0x000d72bb   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed panel_on @ 0x46dd8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void log_message(unsigned long, ...);
extern int power_for_panel(void);
extern int get_ambient_light_sensor_ready_flag(void);
extern void debug_print(unsigned long, ...);
extern int opt3007_chip_init(void);
extern int panel_init(void);
int panel_on(int param_1){
  *(volatile int*)(param_1+0x374) = param_1 - 0x5c;
  if(*(volatile int*)(param_1-0x48)==0){
    if(*(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/ > 2){
      if(*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0){
        log_message(((unsigned long)"%s(): panel_on enter!\n") /*=0xd723a*/, ((unsigned long)"panel_on") /*=0xd72bb*/);
      } else {
        debug_print(((unsigned long)"%s(): panel_on enter!\n") /*=0xd723a*/, ((unsigned long)"panel_on") /*=0xd72bb*/);
      }
    }
    power_for_panel();
    void (*fp)(int) = *(void(* volatile*)(int))(param_1-0x5c);
    fp(*(volatile int*)(param_1+0x374));
    panel_init();
    *(volatile int*)(param_1+0x35c) = 1;
    int iVar1 = get_ambient_light_sensor_ready_flag();
    if(iVar1==0){
      opt3007_chip_init();
    }
  }
  return 0;
}
