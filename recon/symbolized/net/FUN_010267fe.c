#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010267fe @ 0x010267fe
 * public-name: FUN_010267fe
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_010267fe @ 0x10267fe  (parity 300 trials PROVEN) */
typedef unsigned short ushort;
typedef unsigned int uint32_t;
typedef unsigned char undefined1;
extern undefined1 FUN_010292ec(ushort *, ushort *, uint32_t);

undefined1 FUN_010267fe(ushort *param_1, ushort *param_2, uint32_t param_3)
{
  *param_2 = *param_1;
  return FUN_010292ec(param_1, param_2, param_3);
}
