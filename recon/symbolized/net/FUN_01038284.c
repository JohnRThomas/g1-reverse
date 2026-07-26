#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01038284 @ 0x01038284
 * public-name: FUN_01038284
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_01039bb0 @ 0x01039bb0
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103d3b6                           @ 0x0103d3b6
 *   g_net_kernel_curr_tick                   @ 0x210044f0
 */
/* net-core FUN_01038284 @ 0x1038284  (parity 300 trials PROVEN) */

extern int FUN_0103610c(unsigned int);
extern void FUN_01036144(unsigned int);
extern unsigned int FUN_01037f00(void);
extern int FUN_01036128(unsigned int);
extern int assert_print(int, int, int);
extern void assert_post_action(int, int) __attribute__((noreturn));
#include <stdint.h>
#include <cmsis_gcc.h>

unsigned long long FUN_01038284(void)
{
    unsigned int basepri_save;
    basepri_save = __get_BASEPRI();
    __set_BASEPRI_MAX(0x40);
    __ISB();

    int iVar2 = FUN_0103610c(0x21004b70);
    if (iVar2 == 0) {
        assert_print(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0x72);
        assert_post_action(((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0x72);
    }
    FUN_01036144(0x21004b70);
    unsigned int uVar3 = FUN_01037f00();
    volatile unsigned int *p = (volatile unsigned int*)((unsigned long)&g_net_kernel_curr_tick) /*=0x210044f0*/;
    unsigned int uVar4 = p[0];
    unsigned int uVar5 = p[1];
    unsigned int r4 = uVar3 + uVar4;
    unsigned int carry = (r4 < uVar3) ? 1 : 0;
    unsigned int r5 = uVar5 + ((unsigned int)((int)uVar3 >> 31)) + carry;
    iVar2 = FUN_01036128(0x21004b70);
    if (iVar2 == 0) {
        assert_print(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0xf0);
        assert_post_action(((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0xf0);
    }
    __set_BASEPRI(basepri_save);
    __ISB();
    return ((unsigned long long)r5 << 32) | r4;
}
