#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007d3c2 @ 0x0007d3c2
 * public-name: u64_sub
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   u64_sub                                  <= FUN_0007d3c2 @ 0x0007d3c2
 */
/* Reconstructed FUN_0007d3c2 @ 0x7d3c2  (parity: 300/300 trials, PROVEN) */

long long u64_sub(unsigned int param_1,int param_2,unsigned int param_3,int param_4)
{
  long long a = ((long long)param_2 << 32) | (unsigned long long)param_1;
  long long b = ((long long)param_4 << 32) | (unsigned long long)param_3;
  return (a >= b) ? (a - b) : (b - a);
}
