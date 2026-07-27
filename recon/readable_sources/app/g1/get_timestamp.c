#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007d224 @ 0x0007d224
 * public-name: get_timestamp
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed get_timestamp @ 0x7d224  (parity: 300/300 trials, PROVEN) */

extern int get_device_info(void);
unsigned int get_timestamp(void){
    unsigned int iVar1 = get_device_info();
    return *(unsigned int*)(iVar1 + 0xd0);
}
