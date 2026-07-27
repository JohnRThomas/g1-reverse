#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0002c180 @ 0x0002c180
 * public-name: update_persist_task_status_to_wait_blow_head
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   display_close_screen                     <= FUN_00049858 @ 0x00049858
 *   signal_persist_task_event                <= FUN_0007cdf8 @ 0x0007cdf8
 * address symbols (name @ address):
 *   rodata_a25d9                             @ 0x000a25d9
 *   rodata_a25f8                             @ 0x000a25f8   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_persist_task_status_lock               @ 0x20018d9c
 */
/* Reconstructed update_persist_task_status_to_wait_blow_head @ 0x2c180  (parity: 300/300 trials, PROVEN) */

extern void debug_print(unsigned long, ...);
extern void display_close_screen(unsigned char);
extern void signal_persist_task_event(void);
extern void log_message(unsigned long, ...);

unsigned int update_persist_task_status_to_wait_blow_head(unsigned char *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned char *pcVar1 = (unsigned char*)((unsigned long)&g_persist_task_status_lock) /*=0x20018d9c*/;
  unsigned char *puVar2;
  unsigned char *iVar3;

  while (*pcVar1 != 0) {
    signal_persist_task_event();
  }
  *pcVar1 = 1;
  if (param_1[0xd5] != 0 && param_1[0xd5] != 1) {
    display_close_screen(param_1[0xd5]);
  }
  if (*(int*)((unsigned long)&g_log_level) /*=0x2000230c*/ > 0) {
    if (*(int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
      log_message(((unsigned long)&rodata_a25d9) /*=0xa25d9*/, ((unsigned long)"update_persist_task_status_to_wait_blow_head") /*=0xa25f8*/, 1, 0, param_4);
    } else {
      debug_print(((unsigned long)&rodata_a25d9) /*=0xa25d9*/, ((unsigned long)"update_persist_task_status_to_wait_blow_head") /*=0xa25f8*/, 1, 0, param_4);
    }
  }
  param_1[0xd5] = 1;
  puVar2 = *(unsigned char**)(param_1 + 0x1054);
  puVar2[0] = 1;
  puVar2[1] = 0;
  puVar2[2] = 0;
  puVar2[3] = 0;
  iVar3 = *(unsigned char**)(param_1 + 0x1054);
  *pcVar1 = 0;
  iVar3[4] = 1;
  return 0;
}
