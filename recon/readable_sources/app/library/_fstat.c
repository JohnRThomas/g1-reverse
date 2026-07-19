#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000807e8 @ 0x000807e8
 * public-name: _fstat
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   _fstat                                   <= FUN_000807e8 @ 0x000807e8
 */
/* Reconstructed FUN_000807e8 @ 0x807e8  (parity: 300/300 trials, PROVEN) */

unsigned int _fstat(unsigned int param_1, int param_2)
{
  *(volatile unsigned int *)(param_2 + 4) = 0x2000;
  return 0;
}
