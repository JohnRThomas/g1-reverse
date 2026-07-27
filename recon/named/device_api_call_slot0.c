/* readable reconstruction; identity: FUN_0007d120 @ 0x0007d120
 * public-name: device_api_call_slot0
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   device_api_call_slot0                    <= FUN_0007d120 @ 0x0007d120
 */
/* Reconstructed FUN_0007d120 @ 0x7d120 */
#include <stdint.h>
typedef uint32_t (*dispatch_t)(uint32_t,uint32_t,uint32_t,uint32_t);
int device_api_call_slot0(void*object, unsigned long b, void*c, unsigned long d) {
  dispatch_t fn=**(dispatch_t volatile **)(object+8); return fn((uint32_t)(uintptr_t)object,b,c,d);
}
