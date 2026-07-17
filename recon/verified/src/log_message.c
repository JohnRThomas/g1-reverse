/* Reconstructed log_message @ 0x7dda4  (CFG-directed candidate) */
#include <stdarg.h>
extern int vprintf(const char *restrict format, va_list ap);
void log_message(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    (void)vprintf(format, ap);
    va_end(ap);
}
