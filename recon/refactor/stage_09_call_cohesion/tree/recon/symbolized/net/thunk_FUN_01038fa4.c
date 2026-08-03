#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01038d9c @ 0x01038d9c
 * public-name: thunk_FUN_01038fa4
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   ocrypto_mod_p256_to_bytes                <= FUN_01038fa4 @ 0x01038fa4
 */
/* net-core thunk_FUN_01038fa4 @ 0x01038d9c: exact tail alias of FUN_01038fa4. */
#include <stdint.h>
extern uint32_t ocrypto_mod_p256_to_bytes(uint32_t,uint32_t,uint32_t,uint32_t);
uint32_t thunk_FUN_01038fa4(uint32_t a,uint32_t b,uint32_t c,uint32_t d){return ocrypto_mod_p256_to_bytes(a,b,c,d);}
