#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007f210 @ 0x0007f210
 * public-name: settings_nvs_read_fn
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   settings_nvs_read_latest                 <= FUN_0007e9dc @ 0x0007e9dc
 *   settings_nvs_read_fn                     <= FUN_0007f210 @ 0x0007f210
 */
/* Reconstructed FUN_0007f210 @ 0x7f210  (parity: 300/300 trials, PROVEN) */

extern int settings_nvs_read_latest(int a, int b, int c, int d);
int settings_nvs_read_fn(unsigned int *param_1, int param_2, int param_3) {
    unsigned short h = *(unsigned short*)((char*)param_1 + 4);
    int iVar1 = settings_nvs_read_latest((int)param_1[0], (int)h, param_2, param_3);
    if (param_3 <= iVar1) iVar1 = param_3;
    return iVar1;
}
