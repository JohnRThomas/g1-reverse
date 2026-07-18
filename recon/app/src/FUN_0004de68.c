/* Reconstructed FUN_0004de68 @ 0x4de68
 * CFG_VERIFY_CALL_ARITIES=4,4,4,4
 * Readable identity: log_output_dropped_process.
 * Raw/address backmap: log_output_dropped_process <= FUN_0004de68 @ 0x0004de68.
 */
#include <stdint.h>

extern int FUN_0007ddbe(char *, uint32_t, const char *, ...); /* snprintk */
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
#define FUN_0007eea6(output_, data_, length_, context_) \
    g1_buffer_write_inline((g1_log_output_func_t)(output_), (data_), \
                           (length_), (context_))
#else
extern void FUN_0007eea6(void *, const void *, uint32_t, void *); /* buffer_write */
#endif

void FUN_0004de68(const uint32_t *output, uint32_t count)
{
    char text[5];
    void *out = (void *)(uintptr_t)output[0];
    void *ctx = *(void **)(uintptr_t)(output[1] + 4U);
    uint32_t limited = count < 10000U ? count : 9999U;
    int length = FUN_0007ddbe(text, 5U, (const char *)0x000f26c1UL, limited);

    FUN_0007eea6(out, (const void *)0x000f0f45UL, 11U, ctx);
    FUN_0007eea6(out, text, (uint32_t)length, ctx);
    FUN_0007eea6(out, (const void *)0x000f0f29UL, 27U, ctx);
}
