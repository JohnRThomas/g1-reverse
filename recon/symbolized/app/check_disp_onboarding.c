#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00026a08 @ 0x00026a08
 * public-name: check_disp_onboarding
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   onboarding_retry_watchdog_update         <= FUN_00040708 @ 0x00040708
 *   onboarding_sync_data                     <= FUN_00042c8c @ 0x00042c8c
 *   device_addr_is_default                   <= FUN_0007c132 @ 0x0007c132
 *   k_uptime_get_1                           <= FUN_0007cb2c @ 0x0007cb2c
 *   onboarding_clear_active_flag             <= FUN_0007d39e @ 0x0007d39e
 * address symbols (name @ address):
 *   rodata_9fcc1                             @ 0x0009fcc1   [INLINED -- G6 literal batch]
 *   rodata_a1aea                             @ 0x000a1aea   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   onboarding_pending_flag                  @ 0x20018d93
 *   onboarding_secondary_reset_flag          @ 0x2001cdce
 */
/* Reconstructed check_disp_onboarding @ 0x26a08  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void log_message(int,int);
extern int get_device_info(void);
extern void debug_print(void);
extern void onboarding_retry_watchdog_update(void);
extern int onboarding_sync_data(void*,int);
extern int device_addr_is_default(void);
extern unsigned long long k_uptime_get_1(void);
extern void onboarding_clear_active_flag(void);
extern void update_persist_task_status(int,int,int);
#define VB(a) (*(volatile unsigned char*)(a))
#define VI(a) (*(volatile int*)(a))

void check_disp_onboarding(int param_1, unsigned int param_2, unsigned int param_3){
  volatile char *pg70 = (volatile char*)((unsigned long)&onboarding_pending_flag) /*=0x20018d93*/;
  volatile unsigned char *pg74 = (volatile unsigned char*)((unsigned long)&onboarding_secondary_reset_flag) /*=0x2001cdce*/;
  volatile int *pg78 = (volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/;
  volatile int *pg7c = (volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
  int iVar3, iVar5; unsigned long long uVar6;
  (void)param_2;(void)param_3;
  if ((param_1 != 0) || (*pg70 == 0) ||
      (device_addr_is_default() != 0 && (iVar3=get_device_info(), VB(VI(iVar3+0x1014)+2) == 0))) {
    if (VB(get_device_info()) != 1) return;
    onboarding_clear_active_flag();
    return;
  }
  if (*pg70 == 0) return;
  iVar3 = get_device_info();
  if (VI(VI(iVar3+0x1054)) != 0) return;
  iVar3 = get_device_info();
  if (VB(iVar3+0xd5) != 0) return;
  if (VB(get_device_info()) != 1) return;
  if (device_addr_is_default() != 0) { iVar3=get_device_info(); if (VB(VI(iVar3+0x1014)+1)==0) return; }
  if (device_addr_is_default() == 0) { iVar3=get_device_info(); VB(VI(iVar3+0x1014)+2)=0; }
  iVar3=get_device_info(); VB(VI(iVar3+0x1014)+3)=0;
  iVar3=get_device_info(); *pg74 = VB(VI(iVar3+0x1014)+3);
  iVar3=get_device_info(); (void)VB(VI(iVar3+0x1014)+2); (void)(*pg74);
  if (onboarding_sync_data((void*)0,3) != 0) return;
  if (0 < *pg78) {
    if (*pg7c == 0) log_message(((unsigned long)"%s(): ready to show onboarding...\n") /*=0x9fcc1*/,((unsigned long)"check_disp_onboarding") /*=0xa1aea*/);
    else debug_print();
  }
  onboarding_retry_watchdog_update();
  iVar3=get_device_info(); VB(VI(iVar3+0x1014))=1;
  update_persist_task_status(get_device_info(),0xe,2);
  iVar3=get_device_info(); iVar5=get_device_info(); VB(VI(iVar5+0x1014)+0x20)=VB(iVar3+0xed5);
  iVar3=get_device_info(); VB(iVar3+0xed5)=0x2a;
  uVar6=k_uptime_get_1();
  iVar3=get_device_info(); { int b=VI(iVar3+0x1014); VI(b+8)=(int)(uVar6>>32); VI(b+4)=(int)uVar6; }
  iVar3=get_device_info(); iVar5=VI(iVar3+0x1014);
  iVar3=get_device_info(); VB(iVar3+0xcd)=VB(iVar5+3);
}
