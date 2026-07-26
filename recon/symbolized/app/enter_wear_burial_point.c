#include "g1_app_symbols.h"
#include "../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_0004a890 @ 0x0004a890
 * public-name: enter_wear_burial_point
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   enter_wear_burial_point                  <= FUN_0004a890 @ 0x0004a890
 *   k_uptime_get_10                          <= FUN_0007daa4 @ 0x0007daa4
 *   get_current_burial_point_type            <= FUN_0007dac0 @ 0x0007dac0
 * address symbols (name @ address):
 *   rodata_f0337                             @ 0x000f0337   [INLINED -- G6 literal batch]
 *   rodata_f04a9                             @ 0x000f04a9   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed FUN_0004a890 @ 0x4a890  (parity: 300/300 trials, PROVEN) */
extern int get_device_info(void);
extern unsigned get_current_burial_point_type(void);
extern unsigned long long k_uptime_get_10(void);
void enter_wear_burial_point(void){
  int iVar1; unsigned uVar2; unsigned long long uVar3;
  iVar1 = get_device_info();
  if (*(volatile unsigned char*)(iVar1+0x10ac) != 1){
    uVar2 = get_current_burial_point_type();
    if (uVar2 < 7){
      iVar1 = get_device_info();
      *(volatile unsigned char*)(iVar1+0x10ac) = 1;
      iVar1 = get_device_info();
      *(volatile unsigned char*)(iVar1+0x10ad) = (unsigned char)uVar2;
      iVar1 = get_device_info();
      uVar3 = k_uptime_get_10();
      *(volatile unsigned*)(iVar1+0x10b2) = (unsigned)(uVar3>>32);
      *(volatile unsigned*)(iVar1+0x10ae) = (unsigned)uVar3;
      iVar1 = get_device_info();
      iVar1 = uVar2*0xc + iVar1;
      *(volatile int*)(iVar1+0x10e6) = *(volatile int*)(iVar1+0x10e6) + 1;
      iVar1 = get_device_info();
      *(volatile int*)(iVar1+0x10ce) = *(volatile int*)(iVar1+0x10ce) + 1;
      if (1 < *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/){
        if (*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ != 0){
          iVar1 = get_device_info();
          debug_print(((unsigned long)"%s(): [enter_wear_burial_point] start_time is %d\n") /*=0xf0337*/,((unsigned long)"enter_wear_burial_point") /*=0xf04a9*/,*(volatile unsigned*)(iVar1+0x10ae),*(volatile unsigned*)(iVar1+0x10b2));
          return;
        }
        iVar1 = get_device_info();
        log_message(((unsigned long)"%s(): [enter_wear_burial_point] start_time is %d\n") /*=0xf0337*/,((unsigned long)"enter_wear_burial_point") /*=0xf04a9*/,*(volatile unsigned*)(iVar1+0x10ae),*(volatile unsigned*)(iVar1+0x10b2));
        return;
      }
    }
  }
  return;
}
