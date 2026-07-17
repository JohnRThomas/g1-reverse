/* readable reconstruction; identity: FUN_0005f638 @ 0x0005f638
 * public-name: adc_context_start_sampling
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   adc_context_start_sampling               <= FUN_0005f638 @ 0x0005f638
 * address symbols (name @ address):
 *   REG_5000e000                             @ 0x5000e000
 *   REG_5000e004                             @ 0x5000e004
 *   REG_5000e00c                             @ 0x5000e00c
 *   REG_5000e500                             @ 0x5000e500
 */
/* Reconstructed FUN_0005f638 @ 0x5f638  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
void adc_context_start_sampling(void *param_1) {
    *(volatile uint32_t*)0x5000e500UL = 1;
    if (*(volatile char*)((char*)param_1 + 0x86) != 0) {
        *(volatile uint32_t*)0x5000e00cUL = 1;
        return;
    }
    *(volatile uint32_t*)0x5000e000UL = 1;
    *(volatile uint32_t*)0x5000e004UL = 1;
}
