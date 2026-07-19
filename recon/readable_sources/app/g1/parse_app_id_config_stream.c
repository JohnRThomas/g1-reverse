#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_app_id_config_stream_ctx__param_0159   [param_0159; G1-original]
 * Raw function identity: 0x0004f1d0.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0004f1d0 @ 0x0004f1d0
 * public-name: parse_app_id_config_stream
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_log_msg_runtime_create                 <= FUN_0004d944 @ 0x0004d944
 *   parse_app_id_config_stream               <= FUN_0004f1d0 @ 0x0004f1d0
 *   invoke_object_callback_864               <= FUN_0007f7c8 @ 0x0007f7c8
 * address symbols (name @ address):
 *   rodata_880e8                             @ 0x000880e8
 *   rodata_f15f9                             @ 0x000f15f9
 */
/* Reconstructed FUN_0004f1d0 @ 0x4f1d0 (CFG-directed parity: PASS) */
#include <stdint.h>
typedef unsigned int uint;
typedef unsigned char undefined1;
typedef unsigned undefined4;
extern void z_log_msg_runtime_create(unsigned a, int b, void *c, int d);
extern void invoke_object_callback_864(int a, int b);

#define B8(o)  (*(volatile unsigned char*)(param_1 + (o)))
#define S16(o) (*(volatile short*)(param_1 + (o)))
#define U16(o) (*(volatile unsigned short*)(param_1 + (o)))
#define I32(o) (*(volatile int*)(param_1 + (o)))
#define U32(o) (*(volatile uint*)(param_1 + (o)))

void parse_app_id_config_stream(int param_1, int param_2, uint param_3)
{
    undefined4 *puVar1;
    unsigned char *pbVar2;
    undefined1 *puVar3;
    char cVar4;
    unsigned short uVar5;
    uint uVar6, uVar9;
    unsigned char uVar7;
    int iVar8;
    int bVar10;
    undefined4 local_20, local_1c;

    uVar6 = 0;
switchD_caseD_8:
    uVar9 = uVar6;
    if (param_3 <= uVar9) return;
    uVar7 = B8(0x908);
    uVar6 = param_3;
    switch (uVar7) {
    case 0:
        cVar4 = *(volatile char *)(param_2 + uVar9);
        uVar9 = uVar9 + 1;
        B8(0x909) = cVar4;
        if (cVar4 == '\0') {
            B8(0x918) = 0;
            I32(0x8fc) = param_1 + 0x868;
            U32(0x900) = 8;
            uVar7 = 1;
        } else if (cVar4 == '\x01') {
            B8(0x918) = 1;
            U32(0x900) = 1;
            U32(0x914) = 0;
            I32(0x8fc) = param_1 + 0x8e8;
            uVar7 = 2;
        } else {
            uVar7 = 8;
        }
        break;
    case 1:
        puVar1 = (undefined4 *)(param_2 + uVar9);
        uVar9 = uVar9 + 4;
        U32(0x928) = *puVar1;
        uVar7 = 3;
        break;
    case 2:
        uVar6 = U32(0x914);
        if (0xff < uVar6) {
            local_1c = ((unsigned long)&rodata_f15f9) /*=0xf15f9*/; /* DAT_0004f410 */
            local_20 = 2;
            z_log_msg_runtime_create(((unsigned long)&rodata_880e8) /*=0x880e8*/ /* DAT_0004f414 */, 0x1080, &local_20, 0);
            goto control_label_0004f296;
        }
        cVar4 = *(volatile char *)(param_2 + uVar9);
        uVar9 = uVar9 + 1;
        *(volatile char *)(param_1 + uVar6 + 0x92c) = cVar4;
        if (cVar4 == '\0') {
            uVar7 = 3;
        } else {
            U32(0x914) = uVar6 + 1;
        }
        break;
    case 3:
        uVar6 = (uint)*(volatile unsigned char *)(param_2 + uVar9);
        uVar9 = uVar9 + 1;
        U32(0x920) = uVar6;
        if (uVar6 < U32(0x900)) {
            U32(0x924) = *(volatile undefined4 *)(I32(0x8fc) + uVar6 * 0x10 + 0xc);
            if (I32(0x904) != 0) {
                if (*(volatile char *)(I32(0x8fc) + uVar6 * 0x10) != '\0') {
                    I32(0x904) = I32(0x904) + -1;
                }
                uVar7 = 4;
                break;
            }
        }
control_label_0004f296:
        uVar7 = 8;
        break;
    case 4:
        pbVar2 = (unsigned char *)(param_2 + uVar9);
        uVar9 = uVar9 + 1;
        U16(0x91c) = (unsigned short)*pbVar2;
        uVar7 = 5;
        break;
    case 5:
        uVar6 = (uint)U16(0x91c) | (uint)*(volatile unsigned char *)(param_2 + uVar9) << 8;
        U16(0x910) = 0;
        uVar9 = uVar9 + 1;
        S16(0x91c) = (short)uVar6;
        iVar8 = I32(0x8fc) + I32(0x920) * 0x10;
        if (uVar6 == 0) {
            if (*(volatile char *)(I32(0x8fc) + I32(0x920) * 0x10) != '\0') {
                invoke_object_callback_864(param_1, param_1 + 0x918);
            }
            iVar8 = I32(0x904);
            bVar10 = iVar8 != 0;
            if (bVar10) iVar8 = 3;
            uVar7 = (undefined1)iVar8;
            if (!bVar10) uVar7 = 8;
        } else if (*(volatile short *)(iVar8 + 8) == 0) {
            uVar7 = 7;
        } else {
            iVar8 = *(volatile int *)(iVar8 + 0xc);
            bVar10 = iVar8 != 0;
            if (bVar10) iVar8 = 6;
            uVar7 = (undefined1)iVar8;
            if (!bVar10) uVar7 = 7;
        }
        break;
    case 6:
        uVar6 = (uint)U16(0x910);
        if ((uVar6 < *(volatile unsigned short *)(I32(0x8fc) + I32(0x920) * 0x10 + 8)) &&
            (uVar6 < U16(0x91c))) {
            U16(0x910) = U16(0x910) + 1;
            puVar3 = (undefined1 *)(param_2 + uVar9);
            uVar9 = uVar9 + 1;
            *(volatile undefined1 *)(U32(0x924) + uVar6) = *puVar3;
        }
        uVar6 = (uint)U16(0x910);
        if ((U16(0x91c) == uVar6) ||
            (uVar6 == (uint)(*(volatile unsigned short *)(I32(0x8fc) + I32(0x920) * 0x10 + 8) - 1))) {
            if (*(volatile char *)(I32(0x8fc) + I32(0x920) * 0x10) != '\0') {
                *(volatile undefined1 *)(U32(0x924) + uVar6) = 0;
            }
            if (U16(0x91c) <= U16(0x910)) goto control_label_0004f3be;
            uVar7 = 7;
        }
        break;
    case 7:
        uVar5 = U16(0x910);
        bVar10 = uVar5 < U16(0x91c);
        if (bVar10) uVar5 = uVar5 + 1;
        if (bVar10) U16(0x910) = uVar5;
        if (bVar10) uVar9 = uVar9 + 1;
        if (U16(0x910) == U16(0x91c)) {
control_label_0004f3be:
            if (*(volatile char *)(I32(0x8fc) + I32(0x920) * 0x10) != '\0') {
                invoke_object_callback_864(param_1, param_1 + 0x918);
            }
            iVar8 = I32(0x904);
            bVar10 = iVar8 != 0;
            if (bVar10) iVar8 = 3;
            uVar7 = (undefined1)iVar8;
            if (!bVar10) uVar7 = 8;
        }
        break;
    case 8:
        goto switchD_caseD_8;
    default:
        uVar7 = 8;
    }
    B8(0x908) = uVar7;
    uVar6 = uVar9;
    goto switchD_caseD_8;
}
