#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00085014 @ 0x00085014
 * public-name: cjson_print_pretty
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cjson_print                              <= FUN_00064a88 @ 0x00064a88
 *   cjson_print_pretty                       <= FUN_00085014 @ 0x00085014
 */
/* Reconstructed FUN_00085014 @ 0x85014  (parity: 300/300 trials, PROVEN) */

extern void cjson_print(unsigned int, unsigned int);
void cjson_print_pretty(unsigned int param_1)
{
    cjson_print(param_1, 1);
}
