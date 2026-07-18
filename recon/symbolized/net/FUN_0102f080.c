#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0102f080 @ 0x0102f080
 * public-name: FUN_0102f080
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_01039bb0 @ 0x01039bb0
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 * address symbols (name @ address):
 *   rodata_103c0c4                           @ 0x0103c0c4
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103d922                           @ 0x0103d922
 *   rodata_103da8d                           @ 0x0103da8d
 *   rodata_103daa3                           @ 0x0103daa3
 *   rodata_103dad6                           @ 0x0103dad6
 *   rodata_103daee                           @ 0x0103daee
 *   rodata_103db04                           @ 0x0103db04
 *   rodata_103db23                           @ 0x0103db23
 */
/* net-core FUN_0102f080 @ 0x102f080  (parity 300 trials PROVEN) */

typedef unsigned int u32;
typedef int i32;
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"

extern u32 FUN_0102ed18(u32 a, u32 b);
extern void assert_post_action(u32 a, u32 b);
extern void assert_print(u32 a, u32 b, u32 c);
extern void FUN_0103a3d6(u32 a, u32 b, u32 *c);

#define SCB 0xe000ed00u

u32 FUN_0102f080(u32 param_1, i32 param_2, unsigned char *param_3)
{
    u32 uVar4;
    u32 uVar5;
    u32 scratch[8];

    scratch[1] = ((unsigned long)&rodata_103da8d) /*=0x103da8d*/;
    scratch[0] = 2;
    FUN_0103a3d6(((unsigned long)&rodata_103c0c4) /*=0x103c0c4*/, 0x1040, &scratch[0]);

    if ((i32)(*(volatile u32*)(SCB+0x28) << 0x1b) < 0) {
        scratch[0] = 2;
        scratch[1] = ((unsigned long)&rodata_103daa3) /*=0x103daa3*/;
        uVar4 = 0x11;
        FUN_0103a3d6(((unsigned long)&rodata_103c0c4) /*=0x103c0c4*/, 0x1040, &scratch[0]);
    } else {
        uVar4 = 0x10;
    }
    if ((i32)(*(volatile u32*)(SCB+0x28) << 0x1c) < 0) {
        uVar4 = 0x12;
        scratch[1] = ((unsigned long)&rodata_103d922) /*=0x103d922*/;
        scratch[0] = 2;
        FUN_0103a3d6(((unsigned long)&rodata_103c0c4) /*=0x103c0c4*/, 0x1040, &scratch[0]);
    }
    if ((i32)(*(volatile u32*)(SCB+0x28) << 0x1e) < 0) {
        scratch[1] = ((unsigned long)&rodata_103dad6) /*=0x103dad6*/;
        scratch[0] = 2;
        FUN_0103a3d6(((unsigned long)&rodata_103c0c4) /*=0x103c0c4*/, 0x1040, &scratch[0]);
        uVar5 = *(volatile u32*)(SCB+0x34);
        if ((i32)(*(volatile u32*)(SCB+0x28) << 0x18) < 0) {
            scratch[1] = ((unsigned long)&rodata_103daee) /*=0x103daee*/;
            scratch[0] = 3;
            scratch[2] = uVar5;
            FUN_0103a3d6(((unsigned long)&rodata_103c0c4) /*=0x103c0c4*/, 0x1840, &scratch[0]);
            if (param_2 != 0) {
                *(volatile u32*)(SCB+0x28) = *(volatile u32*)(SCB+0x28) & 0xffffff7f;
            }
        } else {
            uVar5 = 0xffffffea;
        }
        uVar4 = 0x13;
    } else {
        uVar5 = 0xffffffea;
    }
    if ((i32)(*(volatile u32*)(SCB+0x28) << 0x1f) < 0) {
        uVar4 = 0x14;
        scratch[1] = ((unsigned long)&rodata_103db04) /*=0x103db04*/;
        scratch[0] = 2;
        FUN_0103a3d6(((unsigned long)&rodata_103c0c4) /*=0x103c0c4*/, 0x1040, &scratch[0]);
    }
    if (((i32)(*(volatile u32*)(SCB+0x28) << 0x1b) < 0) || ((i32)(*(volatile u32*)(SCB+0x28) << 0x1e) < 0)) {
        if ((i32)(*(volatile u32*)(SCB+4) << 0x14) < 0) {
            u32 r0v = FUN_0102ed18(uVar5, param_1);
            if (r0v == 0) {
                if ((i32)(*(volatile u32*)(SCB+0x28) << 0x1b) < 0) {
                    assert_print(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103db23) /*=0x103db23*/, 0x15d);
                    assert_post_action(((unsigned long)&rodata_103db23) /*=0x103db23*/, 0x15d);
                    __builtin_unreachable();
                }
            } else {
                __set_PSP(r0v);
                uVar4 = 2;
            }
        }
    }
    *(volatile u32*)(SCB+0x28) = *(volatile u32*)(SCB+0x28) | 0xff;
    *param_3 = 0;
    return uVar4;
}
