/* readable reconstruction; identity: FUN_00049858 @ 0x00049858
 * public-name: display_close_screen
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   set_dashboard_close_pending_flag         <= FUN_00036024 @ 0x00036024
 *   display_close                            <= FUN_000497b0 @ 0x000497b0
 *   mutex_unlock_syscall_handler             <= FUN_000745c8 @ 0x000745c8
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_f006d                             @ 0x000f006d   [INLINED -- G6 literal batch]
 *   rodata_f0177                             @ 0x000f0177   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed display_close_screen @ 0x49858  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void log_message(int,...);
extern int get_device_info(void);
extern int debug_print(int,...);
extern int set_dashboard_close_pending_flag(void);
extern int display_close(void*,int);
extern int mutex_unlock_syscall_handler(void);
extern int memset_bytes(int,int,int);
int display_close_screen(int param_1, uint32_t param_2){
  uint8_t loc[2];
  (void)param_2;
  loc[0] = 1;
  loc[1] = (uint8_t)param_1;
  if(param_1 != 0){
    if(*(volatile int*)0x2000230cUL > 0){
      if(*(volatile int*)0x20007554UL == 0){
        log_message(((unsigned long)"%s(): display_close_screen %d\n"), ((unsigned long)"display_close_screen"), param_1);
      } else {
        debug_print(((unsigned long)"%s(): display_close_screen %d\n"), ((unsigned long)"display_close_screen"), param_1);
      }
    }
    if(param_1 == 4){
      set_dashboard_close_pending_flag();
    }
    display_close(loc, 2);
    mutex_unlock_syscall_handler();
    int iVar1 = get_device_info();
    memset_bytes(iVar1 + 0xef, 0, 0x5dc);
  }
  return 0;
}
