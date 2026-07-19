#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007d120 @ 0x0007d120
 * public-name: device_api_call_slot0
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   device_api_call_slot0                    <= FUN_0007d120 @ 0x0007d120
 */
/* Reconstructed FUN_0007d120 @ 0x7d120 */
#include <stdint.h>
typedef uint32_t (*dispatch_t)(uint32_t,uint32_t,uint32_t,uint32_t);
uint32_t device_api_call_slot0(uint8_t *object,uint32_t b,uint32_t c,uint32_t d){
  dispatch_t fn=**(dispatch_t volatile **)(object+8); return fn((uint32_t)(uintptr_t)object,b,c,d);
}
