#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007e9d4 @ 0x0007e9d4
 * public-name: settings_nvs_delete_id
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nvs_write                                <= FUN_0004c8f8 @ 0x0004c8f8
 *   settings_nvs_delete_id                   <= FUN_0007e9d4 @ 0x0007e9d4
 */
/* Reconstructed FUN_0007e9d4 @ 0x7e9d4. */
/* Tail wrapper: clear the callee's third and fourth ABI arguments. */
extern void nvs_write(unsigned int, unsigned int,
                         unsigned int, unsigned int);

void settings_nvs_delete_id(unsigned int param_1, unsigned int param_2)
{
    nvs_write(param_1, param_2, 0, 0);
}
