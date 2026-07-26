#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007e2fa @ 0x0007e2fa
 * public-name: printk
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   vprintf                                  <= FUN_0004b1cc @ 0x0004b1cc
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 */
/* Reconstructed FUN_0007e2fa @ 0x7e2fa  (parity: 300/300 trials, PROVEN) */

#include <stdarg.h>
#include <stdint.h>
#include "../../headers/g1_log.h"
extern void vprintf(unsigned int, va_list);
void printk(uintptr_t param_1, ...)
{
  va_list args;
  va_start(args, param_1);
  vprintf(param_1, args);
  va_end(args);
}
