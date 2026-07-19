### FUN_0007c3da  @ 0x0007c3da  (size=16)

callers (1): FUN_000250f8
callees (0): (none)

```c
/* readable reconstruction; identity: FUN_0007c3da @ 0x0007c3da
 * public-name: FUN_0007c3da
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Full reconstruction FUN_0007c3da @ 0x7c3da (exact extent 16 bytes). */
#include <stdint.h>
uint32_t FUN_0007c3da(uint8_t *object)
{
    if (object == 0) return 7;
    uint32_t (*callback)(uint8_t *) = *(uint32_t (**)(uint8_t *))(object + 12);
    return callback != 0 ? callback(object) : 15;
}
```