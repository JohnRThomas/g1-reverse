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

/* Ghidra's name for this same entry; never the distinct debug_print@0x19c70. */
extern __typeof(log_message) log_message_ghidra_alias
    __asm__("DEBUG_PRINT") __attribute__((alias("log_message")));
