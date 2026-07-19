#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_2          => struct g1_layout_param_0101_false_union__param_0101     [param_0101; G1-original]
 *   local_40         => struct g1_layout_img_mgmt_info_local__stack_1124        [stack_1124; G1-original]
 * Raw function identity: 0x00052038.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00052038 @ 0x00052038
 * public-name: img_mgmt_read_info
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   img_mgmt_read                            <= FUN_000517d8 @ 0x000517d8
 *   img_mgmt_erased_val                      <= FUN_00051a5c @ 0x00051a5c
 *   img_mgmt_read_info                       <= FUN_00052038 @ 0x00052038
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 */
/* Reconstructed FUN_00052038 @ 0x52038  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int img_mgmt_read(int, int, void*, ...);
extern int img_mgmt_erased_val(int, void*);
extern int memset_bytes(void*, int, int);

int img_mgmt_read_info(int param_1, uint32_t *param_2, int param_3, uint32_t *param_4)
{
    int iVar1, iVar2;
    unsigned int uVar3, uVar4, uVar5, uVar6, uVar7;
    unsigned char local_45;
    short local_44;
    unsigned short local_42;
    int local_40[2];
    unsigned short local_38;
    int local_34;
    uint32_t local_30, local_2c, uStack_28;

    iVar1 = img_mgmt_erased_val(param_1, &local_45);
    if (iVar1 != 0) return 2;
    iVar2 = img_mgmt_read(param_1, 0, local_40, 0x20);
    iVar1 = (int)0x96f3b83d;
    if (iVar2 != 0) return iVar2;
    if (param_2 == (uint32_t *)0x0) {
        if (local_40[0] != (int)0x96f3b83d) {
control_label_000520f6:
            if (local_40[0] == (int)((unsigned int)local_45 * 0x1010101)) return 3;
            return 0x17;
        }
    } else {
        memset_bytes(param_2, (unsigned int)local_45, 8);
        if (local_40[0] != iVar1) goto control_label_000520f6;
        *param_2 = local_2c;
        param_2[1] = uStack_28;
    }
    if (param_4 != (uint32_t *)0x0) {
        *param_4 = local_30;
    }
    iVar2 = (unsigned int)local_38 + local_34;
    iVar1 = img_mgmt_read(param_1, iVar2, &local_44);
    if ((iVar1 == 0) && (local_44 == 0x6908)) {
        iVar2 = iVar2 + (unsigned int)local_42;
    }
    iVar1 = img_mgmt_read(param_1, iVar2, &local_44);
    if ((iVar1 == 0) && (local_44 == 0x6907)) {
        uVar5 = (unsigned int)local_42 + iVar2 + 4U;
        uVar7 = 0;
        uVar4 = iVar2 + 4U;
        while (uVar6 = uVar4 + 4, uVar6 <= uVar5) {
            iVar1 = img_mgmt_read(param_1, uVar4, &local_44);
            if (iVar1 != 0) return iVar1;
            uVar3 = (unsigned int)local_42;
            if (local_44 == 0xff) {
                if (uVar3 == 0xffff) return 5;
control_label_00052142:
                uVar4 = uVar3 + 4 + uVar4;
            } else {
                if ((local_44 != 0x10) || (uVar3 != 0x20)) goto control_label_00052142;
                if (uVar7 != 0) return 6;
                if (param_3 != 0) {
                    if (uVar5 < uVar4 + 0x24) return 7;
                    iVar1 = img_mgmt_read(param_1, uVar6, (void*)(intptr_t)param_3);
                    if (iVar1 != 0) return iVar1;
                }
                uVar7 = 1;
                uVar4 = uVar6;
            }
        }
        iVar1 = (uVar7 ^ 1) << 3;
    } else {
        iVar1 = 4;
    }
    return iVar1;
}
