#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01039bb0 @ 0x01039bb0
 * public-name: assert_post_action
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_01039bb0 @ 0x01039bb0
 */
/* net-core FUN_01039bb0 @ 0x1039bb0 */
#include <stdint.h>
#include <cmsis_gcc.h>
extern void z_except_reason(unsigned int reason) __attribute__((noreturn));

unsigned int assert_post_action(void)
{
    __set_BASEPRI(0);
    z_except_reason(4);
}
