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
#include "../headers/g1_log.h"
/* Reconstructed FUN_0004d4a8 @ 0x4d4a8  (parity: 300/300 trials, PROVEN) */

extern unsigned long z_log_dropped_read_and_clear_0(void);
extern int assert_post_action(int, int);

void log_dropped(void)
{
  unsigned int uVar2;
  int *r4 = (int*)0x882a0UL;
  int *r6 = (int*)0x882b0UL;

  uVar2 = z_log_dropped_read_and_clear_0();

  for (;;) {
    if ((unsigned int)r4 > (unsigned int)r6) {
      printk((unsigned long)((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"),(void*)((unsigned long)"backend <= _log_backend_list_end"),(void*)0xf0caeUL,0x1d1);
      printk((unsigned long)((unsigned long)"\tunexpected list end location\n"), 0, 0, 0);
      assert_post_action((void*)0xf0caeUL,0x1d1);
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
