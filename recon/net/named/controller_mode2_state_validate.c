/* readable reconstruction; identity: FUN_010218e4 @ 0x010218e4
 * public-name: controller_mode2_state_validate
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_mode2_state_validate          <= FUN_010218e4 @ 0x010218e4
 * address symbols (name @ address):
 *   g_net_radio_ops_table_ptr                @ 0x21000530
 */
/* net-core FUN_010218e4 @ 0x10218e4  (parity 300 trials PROVEN) */

#include <stdint.h>
typedef long long (*code)(void);
void controller_mode2_state_validate(void) {
    uint32_t v = *(volatile uint32_t*)0x21000530;
    code fn = *(code*)(v + 0x14);
    fn();
}
