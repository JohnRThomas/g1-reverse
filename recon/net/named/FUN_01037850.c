/* readable reconstruction; identity: FUN_01037850 @ 0x01037850
 * public-name: FUN_01037850
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_01039bb0 @ 0x01039bb0
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103d3b6                           @ 0x0103d3b6
 */
/* net-core FUN_01037850 @ 0x1037850  (parity 300 trials PROVEN) */
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"

extern int FUN_0103610c(unsigned int);
extern void FUN_01036144(unsigned int);
extern void FUN_01037814(int);
extern int FUN_01036128(unsigned int);
extern int assert_print(int, int, int);
extern void assert_post_action(int, int) __attribute__((noreturn));
extern void FUN_010380d8(int);

void FUN_01037850(int param_1)
{
    unsigned int basepri_save = __get_BASEPRI();
    __set_BASEPRI_MAX(0x40);
    __ISB();

    int iVar3 = FUN_0103610c(0x21004b68);
    if (iVar3 == 0) {
        assert_print(0x103d2a7, 0x103d3b6, 0x72);
        assert_post_action(0x103d3b6, 0x72);
    }
    FUN_01036144(0x21004b68);
    if (*(int*)(param_1 + 8) != 0) {
        FUN_01037814(param_1);
    }
    iVar3 = FUN_01036128(0x21004b68);
    if (iVar3 == 0) {
        assert_print(0x103d2a7, 0x103d3b6, 0xf0);
        assert_post_action(0x103d3b6, 0xf0);
    }
    __set_BASEPRI(basepri_save);
    __ISB();
    FUN_010380d8(param_1 + 0x18);
}
