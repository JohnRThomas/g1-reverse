#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004e3c0 @ 0x0004e3c0
 * public-name: settings_src_register
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   settings_src_register                    <= FUN_0004e3c0 @ 0x0004e3c0
 * address symbols (name @ address):
 *   g_settings_stores                        @ 0x2000a104
 */
/* Reconstructed FUN_0004e3c0 @ 0x4e3c0  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
typedef struct { void *a; void *b; } S;

void settings_src_register(unsigned int *param_1)
{
    *param_1 = 0;
    volatile S *r3 = (volatile S *)((unsigned long)&g_settings_stores) /*=0x2000a104*/;
    void *r2 = r3->b;
    if (r2 != 0) {
        *(unsigned int *)r2 = (unsigned int)(uintptr_t)param_1;
        r3->b = param_1;
        return;
    }
    r3->a = param_1;
    r3->b = param_1;
}
