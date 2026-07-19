#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004de68 @ 0x0004de68
 * public-name: log_output_dropped_process
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   log_output_dropped_process               <= FUN_0004de68 @ 0x0004de68
 *   snprintk                                 <= FUN_0007ddbe @ 0x0007ddbe
 *   buffer_write                             <= FUN_0007eea6 @ 0x0007eea6
 * address symbols (name @ address):
 *   rodata_f0f29                             @ 0x000f0f29
 *   rodata_f0f45                             @ 0x000f0f45
 *   rodata_f26c1                             @ 0x000f26c1
 */
/* Reconstructed FUN_0004de68 @ 0x4de68
 * CFG_VERIFY_CALL_ARITIES=4,4,4,4
 * Readable identity: log_output_dropped_process.
 * Raw/address backmap: log_output_dropped_process <= FUN_0004de68 @ 0x0004de68.
 */
#include <stdint.h>

extern int snprintk(char *, uint32_t, const char *, ...); /* snprintk */
#ifdef G1_APP_SDK_INLINE_COHESION
typedef int (*g1_log_output_func_t)(const void *, uint32_t, void *);
/* Exact Zephyr 3.4.99 log_output.c local owner (receipt c6f068f2..., line 150). */
static __attribute__((always_inline)) inline void
g1_buffer_write_inline(g1_log_output_func_t output, const void *data,
                       uint32_t length, void *context)
{
    const uint8_t *cursor = (const uint8_t *)data;
    int processed;
    do {
        processed = output(cursor, length, context);
        length -= (uint32_t)processed;
        cursor += processed;
    } while (length != 0U);
}
#define buffer_write(output_, data_, length_, context_) \
    g1_buffer_write_inline((g1_log_output_func_t)(output_), (data_), \
                           (length_), (context_))
#else
extern void buffer_write(void *, const void *, uint32_t, void *); /* buffer_write */
#endif

void log_output_dropped_process(const uint32_t *output, uint32_t count)
{
    char text[5];
    void *out = (void *)(uintptr_t)output[0];
    void *ctx = *(void **)(uintptr_t)(output[1] + 4U);
    uint32_t limited = count < 10000U ? count : 9999U;
    int length = snprintk(text, 5U, (const char *)((unsigned long)&rodata_f26c1) /*=0xf26c1*/, limited);

    buffer_write(out, (const void *)((unsigned long)&rodata_f0f45) /*=0xf0f45*/, 11U, ctx);
    buffer_write(out, text, (uint32_t)length, ctx);
    buffer_write(out, (const void *)((unsigned long)&rodata_f0f29) /*=0xf0f29*/, 27U, ctx);
}
