#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00055698 @ 0x00055698
 * public-name: adv_is_directed
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   rodata_f2b3a                             @ 0x000f2b3a
 */
/* Reconstructed adv_is_directed @ 0x00055698 from NCS 2.5.1 adv.c.
 * Raw backmap: FUN_00055698@0x00055698. */

#include <stdint.h>
extern int memcmp(const void*,const void*,uint32_t);
int adv_is_directed(const void *advertisement){return memcmp((const uint8_t*)advertisement+9u,(const void*)((unsigned long)&rodata_f2b3a) /*=0xf2b3a*/,7u)!=0;}
