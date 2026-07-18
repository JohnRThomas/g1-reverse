/* readable reconstruction; identity: FUN_00081cee @ 0x00081cee
 * public-name: bt_gatt_foreach_attr
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed bt_gatt_foreach_attr @ 0x00081cee from NCS 2.5.1 gatt.h.
 * Raw backmap: FUN_00081cee@0x00081cee. */

#include <stdint.h>
typedef uint8_t (*bt_gatt_attr_func_t)(const void*,void*);
extern void bt_gatt_foreach_attr_type(uint16_t,uint16_t,const void*,const void*,uint16_t,bt_gatt_attr_func_t,void*);
void bt_gatt_foreach_attr(uint16_t start,uint16_t end,bt_gatt_attr_func_t callback,void *user_data){bt_gatt_foreach_attr_type(start,end,0,0,0,callback,user_data);}
