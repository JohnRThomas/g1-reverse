/* readable reconstruction; identity: FUN_0007f98a @ 0x0007f98a
 * public-name: FUN_0007f98a
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Full reconstruction FUN_0007f98a @ 0x7f98a (exact extent 14 bytes). */
#include <stdint.h>
void FUN_0007f98a(uint32_t *object, uint32_t r1, uint32_t r2, uint32_t r3)
{
    void (*callback)(uint32_t, uint32_t, uint32_t, uint32_t) =
        (void (*)(uint32_t, uint32_t, uint32_t, uint32_t))(uintptr_t)object[0];
    callback(object[3], r1, r2, r3);
}
