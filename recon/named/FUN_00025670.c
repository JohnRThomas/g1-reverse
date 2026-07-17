/* readable reconstruction; identity: FUN_00025670 @ 0x00025670
 * public-name: FUN_00025670
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   sleep_fixed_33_ticks                     <= FUN_0007c87a @ 0x0007c87a
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 * address symbols (name @ address):
 *   rodata_9f1eb                             @ 0x0009f1eb
 */
/* Reconstructed FUN_00025670 @ 0x25670 CFG_VERIFY_CALL_ARITIES=3,4,0,2 */
#include <stdint.h>
extern void memcpy(uint8_t *, const uint8_t *, uint32_t);
extern int FUN_0007c85e(uint32_t, void *, uint32_t, uint32_t);
extern void sleep_fixed_33_ticks(void);
extern void DEBUG_PRINT(uint32_t, int);
struct part { uint8_t *data; uint32_t length; uint8_t type; };
int FUN_00025670(uint32_t *dev, uint32_t op, uint32_t command,
                 uint32_t value, uint32_t n)
{
    uint8_t bytes[n + 2];
    bytes[0] = command >> 8; bytes[1] = command;
    memcpy(bytes + 2, (const uint8_t *)(uintptr_t)value, n);
    struct part p = {bytes, n + 2, 2};
    int r = FUN_0007c85e(*dev, &p, 1, op);
    sleep_fixed_33_ticks();
    if (r < 0) DEBUG_PRINT(0x9f1eb, r);
    return r;
}
