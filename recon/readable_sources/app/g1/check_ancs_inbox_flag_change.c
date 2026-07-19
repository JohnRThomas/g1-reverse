#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0002eb40 @ 0x0002eb40
 * public-name: check_ancs_inbox_flag_change
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   check_ancs_inbox_flag_change             <= FUN_0002eb40 @ 0x0002eb40
 * address symbols (name @ address):
 *   rodata_a3e80                             @ 0x000a3e80
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_ancs_inbox_flag_cached                 @ 0x20018da5
 *   g_ancs_inbox_flag_current                @ 0x20018da6
 */
/* Reconstructed FUN_0002eb40 @ 0x2eb40  (parity: 300/300 trials, PROVEN) */

extern void log_message(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);
extern void debug_print(unsigned int, unsigned int, unsigned int, unsigned int);

unsigned int check_ancs_inbox_flag_change(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  (void)param_1; (void)param_2;
  volatile unsigned char *p68 = (volatile unsigned char*)((unsigned long)&g_ancs_inbox_flag_current) /*=0x20018da6*/;
  volatile unsigned char *p6c = (volatile unsigned char*)((unsigned long)&g_ancs_inbox_flag_cached) /*=0x20018da5*/;
  unsigned char bVar1 = *p68;
  unsigned int uVar3 = bVar1;
  if (*p6c != uVar3) {
    if (*(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
      log_message(((unsigned long)&rodata_a3e80) /*=0xa3e80*/, uVar3, param_3, 0, param_4);
    } else {
      debug_print(((unsigned long)&rodata_a3e80) /*=0xa3e80*/, uVar3, param_3,
                    *(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/);
    }
  }
  *p6c = bVar1;
  return uVar3;
}
