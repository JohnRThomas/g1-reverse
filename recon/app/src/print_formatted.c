/* Reconstructed print_formatted @ 0x4da6c  (CFG-directed candidate) */
#include <stdint.h>
#include <stdarg.h>
typedef int (*out_func_t)(int, void *);
extern int FUN_0007eec0(out_func_t out, void *ctx, const char *fmt, va_list args);
int print_formatted(void *output, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    int length = FUN_0007eec0((out_func_t)0x0004daadu, output, format, args);
    va_end(args);
    return length;
}
