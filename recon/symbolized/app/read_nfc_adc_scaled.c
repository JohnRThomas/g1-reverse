#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007c830 @ 0x0007c830
 * public-name: read_nfc_adc_scaled
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   adc_nfc_run                              <= FUN_00024c14 @ 0x00024c14
 *   read_nfc_adc_scaled                      <= FUN_0007c830 @ 0x0007c830
 */
/* Reconstructed FUN_0007c830 @ 0x7c830  (parity: 300/300 trials, PROVEN) */

extern int adc_nfc_run(void);

unsigned int read_nfc_adc_scaled(int *param_1)
{
    int v = adc_nfc_run();
    *param_1 = v * 10;
    return 1;
}
