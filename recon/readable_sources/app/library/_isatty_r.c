#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00078570 @ 0x00078570
 * public-name: _isatty_r
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   _isatty_r                                <= FUN_00078570 @ 0x00078570
 *   _isatty                                  <= FUN_000807de @ 0x000807de
 * address symbols (name @ address):
 *   g_errno                                  @ 0x2000cc24
 */
/* Reconstructed FUN_00078570 @ 0x78570  (parity: 300/300 trials, PROVEN) */

extern int _isatty(unsigned int);
void _isatty_r(int *param_1,unsigned int param_2)
{
  *(volatile int *)((unsigned long)&g_errno) /*=0x2000cc24*/ = 0;
  int iVar2 = _isatty(param_2);
  if (iVar2 == -1) {
    int v = *(volatile int *)((unsigned long)&g_errno) /*=0x2000cc24*/;
    if (v != 0) {
      *(volatile int *)param_1 = v;
    }
  }
}
