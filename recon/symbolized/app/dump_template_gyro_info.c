#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00036164 @ 0x00036164
 * public-name: dump_template_gyro_info
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   __extendsfdf2                            <= FUN_0000d848 @ 0x0000d848
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 * address symbols (name @ address):
 *   rodata_a8cf4                             @ 0x000a8cf4   [INLINED -- G6 literal batch]
 *   rodata_a8d3a                             @ 0x000a8d3a   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed dump_template_gyro_info @ 0x36164  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void log_message(int,...);
extern int get_device_info(void);
extern unsigned long long __extendsfdf2(unsigned);
extern void debug_print(int, ...);
void dump_template_gyro_info(int param_1){
  int iVar1; uint32_t raw_x,raw_y,raw_z; unsigned long long uVar2,uVar3,uVar4;
  iVar1=get_device_info();
  if(2 < *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/){
    /* These packed fields are intentionally at odd addresses.  Builtin memcpy
       lowers to the original unaligned loads on Cortex-M33 without creating
       misaligned uint32_t lvalues (which would be ISO-C undefined behavior). */
    __builtin_memcpy(&raw_x,(const void*)(uintptr_t)(iVar1+0xef),sizeof raw_x);
    __builtin_memcpy(&raw_y,(const void*)(uintptr_t)(iVar1+0xf3),sizeof raw_y);
    __builtin_memcpy(&raw_z,(const void*)(uintptr_t)(iVar1+0xf7),sizeof raw_z);
    uVar2=__extendsfdf2(raw_x);
    uVar3=__extendsfdf2(raw_y);
    uVar4=__extendsfdf2(raw_z);
    if(*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/==0){
      log_message(((unsigned long)"%s(): screen_id: %d, ypr: %.2f, %.2f, %.2f\n") /*=0xa8cf4*/,((unsigned long)"dump_template_gyro_info") /*=0xa8d3a*/,(unsigned)*(uint8_t*)(param_1+1),uVar2,uVar3,uVar4);
    } else {
      debug_print(((unsigned long)"%s(): screen_id: %d, ypr: %.2f, %.2f, %.2f\n") /*=0xa8cf4*/,((unsigned long)"dump_template_gyro_info") /*=0xa8d3a*/,(unsigned)*(uint8_t*)(param_1+1),uVar2,uVar3,uVar4);
    }
  }
  return;
}
