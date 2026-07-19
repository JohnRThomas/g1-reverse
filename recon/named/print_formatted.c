/* readable reconstruction; identity: FUN_0004da6c @ 0x0004da6c
 * public-name: print_formatted
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cbvprintf_wrapper                        <= FUN_0007eec0 @ 0x0007eec0
 * address symbols (name @ address):
 *   rodata_4daad                             @ 0x0004daad
 */
/* Reconstructed print_formatted @ 0x4da6c  (CFG-directed candidate) */
#include <stdint.h>
#include <stdarg.h>
typedef int (*out_func_t)(int, void *);
extern int cbvprintf_wrapper(out_func_t out, void *ctx, const char *fmt, va_list args);
int print_formatted(void *output, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    int length = cbvprintf_wrapper((out_func_t)0x0004daadu, output, format, args);
    va_end(args);
    return length;
}
