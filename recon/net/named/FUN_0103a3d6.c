/* readable reconstruction; identity: FUN_0103a3d6 @ 0x0103a3d6
 * public-name: FUN_0103a3d6
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   z_impl_z_log_msg_static_create           <= FUN_0102e284 @ 0x0102e284
 */
/* net-core FUN_0103a3d6 @ 0x0103a3d6 */
#include <stdint.h>
extern uint32_t z_impl_z_log_msg_static_create(uint32_t,uint32_t,uint32_t,uint32_t);
uint32_t FUN_0103a3d6(uint32_t a,uint32_t b,uint32_t c,uint32_t d){(void)d;return z_impl_z_log_msg_static_create(a,b,c,0);}
