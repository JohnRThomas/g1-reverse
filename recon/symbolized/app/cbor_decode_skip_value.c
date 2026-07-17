#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00086064 @ 0x00086064
 * public-name: cbor_decode_skip_value
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cbor_decode_precheck                     <= FUN_00085d82 @ 0x00085d82
 *   cbor_decode_expect_break                 <= FUN_00085dd2 @ 0x00085dd2
 *   cbor_decode_extract_value                <= FUN_00085e1a @ 0x00085e1a
 *   cbor_decode_tag                          <= FUN_0008603c @ 0x0008603c
 *   cbor_decode_skip_value                   <= FUN_00086064 @ 0x00086064
 */
/* Reconstructed FUN_00086064 @ 0x86064  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_00085d36(int,...);
extern int FUN_00085d70(int,...);
extern int cbor_decode_precheck(void);
extern int cbor_decode_expect_break(int,...);
extern int cbor_decode_extract_value(void *, void *, unsigned int);
extern int cbor_decode_tag(int,...);

int cbor_decode_skip_value(unsigned *param_1, int param_2)
{
    unsigned char bVar1; int iVar2; unsigned char *pbVar3; int iVar4; unsigned uVar5;
    unsigned char *pbVar6; unsigned *puVar7; int bVar8; unsigned uVar9;
    unsigned char **ppbVar10; int bVar11;
    unsigned char auStack_3c[4];
    struct { unsigned lo, hi; } decoded_width;
#define local_38 (decoded_width.lo)
#define local_34 (decoded_width.hi)
    unsigned char *local_30[6];
#define local_24 (local_30[3])

    if(param_2 != 0){ uVar5 = 0xe; goto LAB_0008606e; }
    iVar2 = cbor_decode_precheck();
    if(iVar2 == 0) return 0;
    local_38 = 0;
    local_34 = 0;
    bVar1 = *(unsigned char*)(uintptr_t)*param_1;
    ppbVar10 = local_30;
    puVar7 = param_1;
    do {
        pbVar3 = (unsigned char*)(uintptr_t)*puVar7;
        pbVar6 = (unsigned char*)(uintptr_t)puVar7[1];
        puVar7 = puVar7 + 2;
        *ppbVar10 = pbVar3;
        ppbVar10[1] = pbVar6;
        ppbVar10 = ppbVar10 + 2;
    } while(puVar7 != param_1 + 6);
    while(1){
        uVar9 = (unsigned)(bVar1 >> 5);
        if(uVar9 != 6) break;
        iVar4 = cbor_decode_tag((int)local_30, (int)auStack_3c);
        if(iVar4 == 0) return 0;
        if(local_24 <= local_30[0]) goto LAB_0008610e;
        bVar1 = *local_30[0];
    }
    if((bVar1 & 0x1f) == 0x1f){
        if(uVar9 - 4 < 2){
            iVar4 = iVar2;
            if(uVar9 != 4){
                bVar8 = 1;
LAB_00086146:
                *(unsigned char*)&local_30[4] = (unsigned char)iVar4;
                if(local_34 != 0 || local_34 < (unsigned)(0x7fffffff < local_38)){
                    uVar5 = 5; goto LAB_0008606e;
                }
                bVar11 = ((unsigned)(local_38 + local_38) < local_38);
                local_38 = local_38 * 2;
                local_34 = local_34 * 2 + (unsigned)bVar11;
                if(!bVar8) goto LAB_00086162;
            }
            *(unsigned char*)&local_30[4] = (unsigned char)iVar4;
            bVar8 = 1;
            local_30[0] = local_30[0] + 1;
            local_38 = 0xffffffef;
            local_34 = 0;
LAB_00086162:
            local_30[2] = (unsigned char*)(uintptr_t)local_38;
            while(iVar4 = FUN_00085d36((int)local_30), iVar4 == 0){
                iVar4 = cbor_decode_skip_value((unsigned*)local_30, 0);
                if(iVar4 == 0) return 0;
            }
            if(bVar8 && (iVar4 = cbor_decode_expect_break((int)local_30), iVar4 == 0)){
                return 0;
            }
            goto LAB_000860ee;
        }
        iVar4 = cbor_decode_extract_value(local_30, &local_38, 8);
        if(iVar4 == 0) return 0;
        if(4 < uVar9) goto LAB_000860ee;
    } else {
        iVar4 = cbor_decode_extract_value(local_30, &local_38, 8);
        if(iVar4 == 0) return 0;
        if(uVar9 == 4){
            bVar8 = 0;
            *(unsigned char*)&local_30[4] = 0;
            goto LAB_00086162;
        }
        if(4 < uVar9){
            if(uVar9 != 5) goto LAB_000860ee;
            iVar4 = 0;
            bVar8 = 0;
            goto LAB_00086146;
        }
    }
    if(uVar9 - 2 < 2){
        uVar9 = (unsigned)(((int)(intptr_t)local_24 - (int)(intptr_t)local_30[0]) >> 0x1f);
        if(uVar9 <= local_34 &&
           (unsigned)(local_38 <= (unsigned)((int)(intptr_t)local_24 - (int)(intptr_t)local_30[0])) <= uVar9 - local_34){
LAB_0008610e:
            uVar5 = 8;
LAB_0008606e:
            FUN_00085d70((int)param_1, uVar5);
            return 0;
        }
        local_30[0] = local_30[0] + local_38;
    }
LAB_000860ee:
    *param_1 = (unsigned)(uintptr_t)local_30[0];
    param_1[2] = param_1[2] - 1;
    return iVar2;
#undef local_24
#undef local_34
#undef local_38
}
