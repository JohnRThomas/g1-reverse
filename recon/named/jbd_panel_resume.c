/* readable reconstruction; identity: FUN_00047638 @ 0x00047638
 * public-name: jbd_panel_resume
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   set_brightness_to_panel_reg              <= FUN_00046e3c @ 0x00046e3c
 *   panel_init                               <= FUN_00047538 @ 0x00047538
 * address symbols (name @ address):
 *   rodata_d73bc                             @ 0x000d73bc   [INLINED -- G6 literal batch]
 *   rodata_d73e0                             @ 0x000d73e0   [INLINED -- G6 literal batch]
 *   rodata_d73f8                             @ 0x000d73f8   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
#include "../headers/g1_log.h"
/* Reconstructed jbd_panel_resume @ 0x47638  (parity: 300/300 trials, PROVEN) */

extern void set_brightness_to_panel_reg(unsigned int);
extern void panel_init(void);

unsigned int jbd_panel_resume(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  volatile int *piVar1 = (volatile int*)0x2000230cUL;

  if (*piVar1 > 2) {
    unsigned int sink = *(volatile unsigned int*)0x20007554UL;
    if (sink == 0) {
      log_message((unsigned long)0xd73bcUL, (void*)0xd73f8UL, param_3, sink, param_4);
    } else {
      debug_print((unsigned long)0xd73bcUL, (void*)0xd73f8UL,
                   param_3, sink, param_4);
    }
  }
  panel_init();
  set_brightness_to_panel_reg(*(unsigned char*)(param_1+0x369));
  if (*piVar1 > 2) {
    unsigned int sink = *(volatile unsigned int*)0x20007554UL;
    if (sink == 0) {
      log_message((unsigned long)0xd73e0UL, (void*)0xd73f8UL, param_3, sink, param_4);
    } else {
      debug_print((unsigned long)0xd73e0UL, (void*)0xd73f8UL,
                   param_3, sink, param_4);
    }
  }
  return 0;
}
