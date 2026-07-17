#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00085206 @ 0x00085206
 * public-name: audio_i2s_stream1_trigger_start
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   qspi_xfer                                <= FUN_00066524 @ 0x00066524
 *   audio_i2s_stream1_trigger_start          <= FUN_00085206 @ 0x00085206
 */
/* Reconstructed FUN_00085206 @ 0x85206  (parity: 300/300 trials, PROVEN) */

extern int qspi_xfer(unsigned int param_1, int param_2, int param_3, unsigned int param_4);
int audio_i2s_stream1_trigger_start(unsigned int param_1, int param_2, int param_3)
{
    return qspi_xfer(param_1, param_2, param_3, 3);
}
