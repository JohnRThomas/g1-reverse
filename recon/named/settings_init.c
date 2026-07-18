/* readable reconstruction; identity: FUN_0004e484 @ 0x0004e484
 * public-name: settings_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   settings_store_init                      <= FUN_0004e474 @ 0x0004e474
 *   settings_init                            <= FUN_0004e484 @ 0x0004e484
 * address symbols (name @ address):
 *   g_settings_handlers                      @ 0x2000a10c
 */
/* Reconstructed FUN_0004e484 @ 0x4e484  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
typedef struct { unsigned int a; unsigned int b; } S;
extern void settings_store_init(void);

void settings_init(void)
{
    volatile S * volatile p1 = (volatile S *)0x2000a10cUL;
    p1->a = 0;
    p1->b = 0;
    settings_store_init();
}
