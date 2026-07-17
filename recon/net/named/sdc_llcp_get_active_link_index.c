/* readable reconstruction; identity: FUN_0100d760 @ 0x0100d760
 * public-name: sdc_llcp_get_active_link_index
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_21000ea7                               @ 0x21000ea7
 */
/* Reconstructed sdc_llcp_get_active_link_index @ 0x0100d760.
 * Back-map: FUN_0100d760.  Exact extent: 72 bytes.
 */
#include <stdint.h>
extern int FUN_010208cc(int8_t *sample);

int sdc_llcp_get_active_link_index(void)
{
    int8_t sample = INT8_MAX;
    if (FUN_010208cc(&sample) == 0) {
        return sample;
    }
    int32_t adjusted = (int32_t)sample +
        (int32_t)(int8_t)(0u - *(volatile uint8_t *)0x21000ea7u);
    if (adjusted > 20) {
        return 20;
    }
    if (adjusted < -127) {
        return -127;
    }
    return (int8_t)adjusted;
}
