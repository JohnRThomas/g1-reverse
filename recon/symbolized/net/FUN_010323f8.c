#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010323f8 @ 0x010323f8
 * public-name: FUN_010323f8
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_01039bb0 @ 0x01039bb0
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 *   z_device_is_ready                        <= FUN_0103b0f0 @ 0x0103b0f0
 * address symbols (name @ address):
 *   rodata_103bf70                           @ 0x0103bf70
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103e187                           @ 0x0103e187
 */
/* net-core FUN_010323f8 @ 0x10323f8  (parity 300 trials PROVEN) */

extern int z_device_is_ready(void *a);
extern void assert_print(unsigned int a, unsigned int b, unsigned int c);
extern void assert_post_action(unsigned int a, unsigned int b);

typedef unsigned int (*fnptr)(void*, unsigned int, unsigned short);

unsigned int FUN_010323f8(unsigned int param_1, unsigned short param_2)
{
    void *iVar1 = (void*)((unsigned long)&rodata_103bf70) /*=0x103bf70*/;
    int iVar2 = z_device_is_ready(iVar1);
    unsigned int target;
    fnptr f;
    if (iVar2 == 0) return 0xffffffed;
    target = *(unsigned int *)(*(unsigned int *)((char*)iVar1 + 8));
    if (target == 0) {
        assert_print(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103e187) /*=0x103e187*/, 0x4d);
        assert_post_action(((unsigned long)&rodata_103e187) /*=0x103e187*/, 0x4d);
    }
    f = (fnptr)target;
    return f(iVar1, param_1, param_2);
}
