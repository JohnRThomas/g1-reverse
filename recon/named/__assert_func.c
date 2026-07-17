/* readable reconstruction; identity: FUN_00076a94 @ 0x00076a94
 * public-name: __assert_func
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   rodata_a8ea0                             @ 0x000a8ea0
 *   rodata_f8a2e                             @ 0x000f8a2e
 *   rodata_f8a3b                             @ 0x000f8a3b
 *   g_libc_heap_ctrl                         @ 0x20002d20
 */
/* Reconstructed __assert_func @ 0x76a94 (raw FUN_00076a94).
 * Reviewed executable extent: 0x2a bytes; literals begin at 0x76ac0. */
#include <stdint.h>

#define NEWLIB_IMPURE_PTR_ADDRESS ((void **)0x20002d20u)
#define ASSERT_MESSAGE_FORMAT ((const char *)0x000f8a3bu)
#define FUNCTION_PREFIX ((const char *)0x000f8a2eu)
#define EMPTY_STRING ((const char *)0x000a8ea0u)

extern int fiprintf(void *stream, const char *format, ...)
    __asm__("FUN_00076cc8");
extern void abort(void) __attribute__((noreturn));

void __assert_func(const char *source_file, int line,
                   const char *function_name, const char *failed_expression)
{
    void *newlib_reent = *NEWLIB_IMPURE_PTR_ADDRESS;
    void *stderr_stream = *(void **)((uint8_t *)newlib_reent + 0x0c);
    const char *function_prefix = EMPTY_STRING;

    if (function_name == 0) {
        function_name = EMPTY_STRING;
    } else {
        function_prefix = FUNCTION_PREFIX;
    }

    fiprintf(stderr_stream, ASSERT_MESSAGE_FORMAT, failed_expression,
             source_file, line, function_prefix, function_name);
    abort();
}
