/* readable reconstruction; identity: FUN_0103689c @ 0x0103689c
 * public-name: FUN_0103689c
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_01039bb0 @ 0x01039bb0
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103d3b6                           @ 0x0103d3b6
 *   rodata_103eacd                           @ 0x0103eacd
 */
/* net-core FUN_0103689c @ 0x103689c  (parity 300 trials PROVEN) */

#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"
static inline int isCurrentModePrivileged(void){return (__get_CONTROL() & 1u) == 0;}
static inline unsigned int getBasePriority(void){return __get_BASEPRI();}
static inline void setBasePriority(int p){__set_BASEPRI((unsigned int)p);}
static inline void InstructionSynchronizationBarrier(int x){(void)x; __ISB();}
static inline unsigned int readIPSR(void){return __get_IPSR();}

extern int FUN_0103610c(void *);
extern int FUN_01036128(void *);
extern void FUN_01036144(void *);
extern int FUN_010375b8(void*, unsigned int, void*, unsigned int, unsigned int, unsigned int);
extern void assert_post_action(unsigned int, unsigned int);
extern void assert_print(unsigned int, unsigned int, unsigned int);

int FUN_0103689c(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned int ipsr = readIPSR();
    if (ipsr == 0 || (param_3 | param_4) == 0) {
        unsigned int uVar5 = 0;
        if (isCurrentModePrivileged()) {
            uVar5 = getBasePriority();
        }
        if (isCurrentModePrivileged()) {
            unsigned int uVar4b = getBasePriority();
            if (uVar4b == 0 || uVar4b > 0x40) {
                setBasePriority(0x40);
            }
        }
        InstructionSynchronizationBarrier(0xf);

        volatile int * const p54 = (volatile int *)0x21004b4c;
        int iVar2 = FUN_0103610c((void*)p54);
        if (iVar2 == 0) {
            assert_print(0x0103d2a7, 0x0103d3b6, 0x72);
            assert_post_action(0x0103d3b6, 0x72);
            __builtin_unreachable();
        }

        FUN_01036144((void*)p54);

        if (*(volatile int *)(param_1 + 8) == 0) {
            if ((param_3 | param_4) != 0) {
                return FUN_010375b8((void*)p54, uVar5, (void*)param_1, param_3 | param_4, param_3, param_4);
            }
            int iVar2b = FUN_01036128((void*)p54);
            if (iVar2b != 0) {
                if (isCurrentModePrivileged()) {
                    setBasePriority((int)uVar5);
                }
                InstructionSynchronizationBarrier(0xf);
                return 0xfffffff0;
            }
        } else {
            *(volatile int *)(param_1 + 8) = *(volatile int *)(param_1 + 8) - 1;
            int iVar2c = FUN_01036128((void*)p54);
            if (iVar2c != 0) {
                if (isCurrentModePrivileged()) {
                    setBasePriority((int)uVar5);
                }
                InstructionSynchronizationBarrier(0xf);
                return 0;
            }
        }

        assert_print(0x0103d2a7, 0x0103d3b6, 0xf0);
        assert_post_action(0x0103d3b6, 0xf0);
        __builtin_unreachable();
    } else {
        assert_print(0x0103d2a7, 0x0103eacd, 0x80);
        assert_post_action(0x0103eacd, 0x80);
        __builtin_unreachable();
    }
}
