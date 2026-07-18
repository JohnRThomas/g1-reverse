/* Reconstructed FUN_0004de68 @ 0x4de68
 * CFG_VERIFY_CALL_ARITIES=4,4,4,4
 * Readable identity: log_output_dropped_process.
 * Raw/address backmap: log_output_dropped_process <= FUN_0004de68 @ 0x0004de68.
 */
#include <stdint.h>

extern int FUN_0007ddbe(char *, uint32_t, const char *, ...); /* snprintk */
extern void FUN_0007eea6(void *, const void *, uint32_t, void *); /* buffer_write */

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
