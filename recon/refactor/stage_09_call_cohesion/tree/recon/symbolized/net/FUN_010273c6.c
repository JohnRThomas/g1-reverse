#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010273c6 @ 0x010273c6
 * public-name: FUN_010273c6
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_010273c6 @ 0x10273c6  (CFG-directed candidate) */
#include <stdint.h>
extern void FUN_01027196(void *,uint32_t);
extern void FUN_010271b8(void *,void *);
void FUN_010273c6(void *first,void *second,uint32_t value_arg) {
    uint16_t value=(uint16_t)value_arg;
    FUN_01027196(second,value);
    FUN_010271b8(second,first);
}
