#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007c830 @ 0x0007c830
 * public-name: FUN_0007c830
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   adc_nfc_run                              <= FUN_00024c14 @ 0x00024c14
 */
/* Reconstructed FUN_0007c830 @ 0x7c830  (parity: 300/300 trials, PROVEN) */

extern int adc_nfc_run(void);

unsigned int FUN_0007c830(int *param_1)
{
    int v = adc_nfc_run();
    *param_1 = v * 10;
    return 1;
}
