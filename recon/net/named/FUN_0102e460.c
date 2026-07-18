/* readable reconstruction; identity: FUN_0102e460 @ 0x0102e460
 * public-name: FUN_0102e460
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core formatted log output adapter @ 0x0102e460.
 * Raw/address back-map: FUN_0102e460 / 0x0102e460.
 */
#include <stdint.h>
#include <stdarg.h>

extern int FUN_0102fa4c(const void *output_cb, uint32_t context,
                        const char *format, va_list args);

int FUN_0102e460(uint32_t context, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    int result = FUN_0102fa4c((const void *)0x0102eca1u, context, format, args);
    va_end(args);
    return result;
}
