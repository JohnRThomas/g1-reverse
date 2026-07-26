#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01039722 @ 0x01039722
 * public-name: printk
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core printk @ 0x01039722
 * Raw/address back-map: FUN_01039722 / 0x01039722.
 */
#include <stdarg.h>
#include <stdint.h>
#include "../../headers/g1_log.h"
extern void FUN_0103a2a6(const char *fmt, va_list ap);
void printk(uintptr_t fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    FUN_0103a2a6((const char *)fmt, ap);
    va_end(ap);
}
