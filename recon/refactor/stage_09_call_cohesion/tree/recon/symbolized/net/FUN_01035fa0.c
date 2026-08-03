#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01035fa0 @ 0x01035fa0
 * public-name: FUN_01035fa0
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_01039bb0 @ 0x01039bb0
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 * address symbols (name @ address):
 *   rodata_103bac9                           @ 0x0103bac9
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103ea45                           @ 0x0103ea45
 */
/* net-core FUN_01035fa0 @ 0x1035fa0 */
#include <stdint.h>
#include <cmsis_gcc.h>
#include "../../headers/g1_dedupe.h"
extern void FUN_01035edc(uint32_t, uint32_t, uint32_t, uint32_t,
                         uint32_t, uint32_t, uint32_t, uint32_t,
                         uint32_t, uint32_t);
extern void FUN_0103719c(uint32_t);
extern void FUN_01037f8c(void *, uint32_t, uint32_t, uint32_t);
extern void assert_post_action(uint32_t, uint32_t) /* FUN_01039bb0 */
    __attribute__((noreturn));
extern void assert_print(uint32_t, uint32_t, uint32_t); /* FUN_01039bbe */

uint32_t FUN_01035fa0(uint32_t object, uint32_t arg2, uint32_t arg3,
                      uint32_t arg4, uint32_t arg5, uint32_t arg6,
                      uint32_t arg7, uint32_t arg8, uint32_t arg9,
                      uint32_t unused, int32_t high, int32_t low)
{
    (void)unused;
    uint32_t exception = __get_IPSR();
    if (exception != 0) {
        G1_NET_ASSERT_FAIL((((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103ea45) /*=0x103ea45*/, 0x28c), (((unsigned long)&rodata_103ea45) /*=0x103ea45*/, 0x28c));
    }
    FUN_01035edc(object, arg2, arg3, arg4, arg5, arg6, arg7, arg8,
                  arg9, exception);

    if (low != -1 || high != -1) {
        if (low == 0 && high == 0)
            FUN_0103719c(object);
        else
            FUN_01037f8c((void *)(uintptr_t)(object + 0x18),
                          ((unsigned long)&rodata_103bac9) /*=0x103bac9*/, (uint32_t)high, (uint32_t)low);
    }
    return object;
}
