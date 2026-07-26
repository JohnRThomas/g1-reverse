#include "g1_app_symbols.h"
#include "../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_0004d4a8 @ 0x0004d4a8
 * public-name: log_dropped
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_log_dropped_read_and_clear_0           <= FUN_0004d490 @ 0x0004d490
 *   log_dropped                              <= FUN_0004d4a8 @ 0x0004d4a8
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_882a0                             @ 0x000882a0
 *   __settings_handler_static_list_start     @ 0x000882b0
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f0cae                             @ 0x000f0cae
 *   rodata_f0cff                             @ 0x000f0cff   [INLINED -- G6 literal batch]
 *   rodata_f0d20                             @ 0x000f0d20   [INLINED -- G6 literal batch]
 */
/* Reconstructed FUN_0004d4a8 @ 0x4d4a8  (parity: 300/300 trials, PROVEN) */

extern unsigned int z_log_dropped_read_and_clear_0(void);
extern void assert_post_action(void*, int);

void log_dropped(void)
{
  unsigned int uVar2;
  int *r4 = (int*)((unsigned long)&rodata_882a0) /*=0x882a0*/;
  int *r6 = (int*)((unsigned long)&__settings_handler_static_list_start) /*=0x882b0*/;

  uVar2 = z_log_dropped_read_and_clear_0();

  for (;;) {
    if ((unsigned int)r4 > (unsigned int)r6) {
      printk((void*)((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,(void*)((unsigned long)"backend <= _log_backend_list_end") /*=0xf0cff*/,(void*)((unsigned long)&rodata_f0cae) /*=0xf0cae*/,0x1d1);
      printk((void*)((unsigned long)"\tunexpected list end location\n") /*=0xf0d20*/, 0, 0, 0);
      assert_post_action((void*)((unsigned long)&rodata_f0cae) /*=0xf0cae*/,0x1d1);
    }
    if ((unsigned int)r4 >= (unsigned int)r6) break;
    if (*(char*)(*(int*)((char*)r4+4) + 5) != 0 && *(void**)(*(int*)r4 + 4) != 0) {
      void (*fn)(void*, unsigned int) = *(void**)(*(int*)r4 + 4);
      fn(r4, uVar2);
    }
    r4 = (int*)((char*)r4 + 0x10);
  }
  return;
}
