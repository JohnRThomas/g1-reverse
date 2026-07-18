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
extern void buffer_write(void *, const void *, uint32_t, void *); /* buffer_write */

void log_output_dropped_process(const uint32_t *output, uint32_t count)
{
    char text[5];
    void *out = (void *)(uintptr_t)output[0];
    void *ctx = *(void **)(uintptr_t)(output[1] + 4U);
    uint32_t limited = count < 10000U ? count : 9999U;
    int length = snprintk(text, 5U, (const char *)0x000f26c1UL, limited);

    buffer_write(out, (const void *)0x000f0f45UL, 11U, ctx);
    buffer_write(out, text, (uint32_t)length, ctx);
    buffer_write(out, (const void *)0x000f0f29UL, 27U, ctx);
}
