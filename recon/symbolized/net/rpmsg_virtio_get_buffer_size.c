#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010357ec @ 0x010357ec
 * public-name: rpmsg_virtio_get_buffer_size
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   rpmsg_virtio_get_buffer_size             <= FUN_010357ec @ 0x010357ec
 *   thunk_FUN_01036824                       <= FUN_0103aec2 @ 0x0103aec2
 */
/* net-core FUN_010357ec @ 0x10357ec  (parity 300 trials PROVEN) */

extern void FUN_0103aec6(int a);
extern int FUN_0103ad1a(unsigned int a);
extern void thunk_FUN_01036824(int a);

int rpmsg_virtio_get_buffer_size(int param_1)
{
    int iVar1;
    if (param_1 == 0) return (int)0xfffff82d;
    FUN_0103aec6(param_1 + 0x58);
    if (*(int*)(*(int*)(param_1+0xa0)+0x18) == 1) {
        iVar1 = FUN_0103ad1a(*(unsigned int*)(param_1+0xa8));
        iVar1 = iVar1 - 0x10;
        if (0 < iVar1) goto done;
    }
    iVar1 = (int)0xfffff82e;
done:
    thunk_FUN_01036824(param_1 + 0x58);
    return iVar1;
}
