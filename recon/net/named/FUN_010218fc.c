/* readable reconstruction; identity: FUN_010218fc @ 0x010218fc
 * public-name: FUN_010218fc
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_radio_ops_table_ptr                @ 0x21000530
 */
/* net-core FUN_010218fc @ 0x10218fc  (parity 300 trials PROVEN) */

#include <stdint.h>
typedef long long (*code)(void);
void FUN_010218fc(void) {
    uint32_t v = *(volatile uint32_t*)0x21000530;
    code fn = *(code*)(v + 0x24);
    fn();
}
