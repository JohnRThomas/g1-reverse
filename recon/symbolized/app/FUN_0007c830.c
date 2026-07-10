#include "g1_app_symbols.h"
/* named: FUN_0007c830 */
/* Reconstructed FUN_0007c830 @ 0x7c830  (parity: 300/300 trials, PROVEN) */

extern int adc_nfc_run(void);

unsigned int FUN_0007c830(int *param_1)
{
    int v = adc_nfc_run();
    *param_1 = v * 10;
    return 1;
}

