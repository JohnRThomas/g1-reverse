#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004da6c @ 0x0004da6c
 * public-name: print_formatted
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   rodata_4daad                             @ 0x0004daad
 */
/* Reconstructed print_formatted @ 0x4da6c  (CFG-directed candidate) */
#include <stdint.h>
#include <stdarg.h>
typedef int (*out_func_t)(int, void *);
extern int FUN_0007eec0(out_func_t out, void *ctx, const char *fmt, va_list args);
int print_formatted(void *output, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    int length = FUN_0007eec0((out_func_t)((unsigned long)&rodata_4daad) /*=0x4daad*/, output, format, args);
    va_end(args);
    return length;
}
