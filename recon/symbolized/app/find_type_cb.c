#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000583d0 @ 0x000583d0
 * public-name: find_type_cb
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   find_type_cb                             <= FUN_000583d0 @ 0x000583d0
 *   net_buf_pool_get                         <= FUN_0005ee08 @ 0x0005ee08
 *   net_buf_frag_last                        <= FUN_0005f304 @ 0x0005f304
 *   net_buf_frag_add                         <= FUN_0005f390 @ 0x0005f390
 *   net_buf_simple_add                       <= FUN_0005f5d0 @ 0x0005f5d0
 *   bt_uuid_cmp                              <= FUN_00080d3e @ 0x00080d3e
 *   bt_uuid_create                           <= FUN_00080d9a @ 0x00080d9a
 *   net_buf_frags_len_0                      <= FUN_00081bc0 @ 0x00081bc0
 *   att_log_emit_3arg                        <= FUN_00081ddc @ 0x00081ddc
 *   bt_conn_alloc_pdu_buf                    <= FUN_000836de @ 0x000836de
 *   net_buf_simple_tailroom                  <= FUN_00083730 @ 0x00083730
 *   memcmp                                   <= FUN_00086be4 @ 0x00086be4
 * address symbols (name @ address):
 *   rodata_88100                             @ 0x00088100
 *   rodata_f43ca                             @ 0x000f43ca
 *   rodata_f43e9                             @ 0x000f43e9
 */
/* Reconstructed FUN_000583d0 @ 0x583d0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern uint64_t net_buf_pool_get(int);
extern int net_buf_frag_last(int);
extern void net_buf_frag_add(int, int);
extern int net_buf_simple_add(int, int);
extern int bt_uuid_cmp(int, int);
extern int bt_uuid_create(int, int, int);
extern uint64_t net_buf_frags_len_0(int);
extern void att_log_emit_3arg(int, int, int);
extern int bt_conn_alloc_pdu_buf(int, int, int, int);
extern unsigned long net_buf_simple_tailroom(void*);
extern int memcmp(int, int);

uint32_t find_type_cb(uint32_t *param_1, unsigned param_2, int *param_3)
{
    int iVar1, iVar3, iVar6;
    unsigned uVar2, uVar4;
    uint64_t uVar7;
    int puVar5;
    volatile uint32_t local_78, local_74, local_70, local_64;
    volatile uint8_t auStack_60[16];
    volatile uint8_t auStack_50[20];
    volatile uint8_t sdesc[4];

    iVar6 = *param_3;
    local_64 = *(volatile uint32_t*)(iVar6 + 8);
    sdesc[0] = 0;
    *(volatile uint16_t*)(sdesc + 2) = 0x2801;
    iVar1 = bt_uuid_cmp(*param_1, (int)(intptr_t)sdesc);
    if (iVar1 == 0) goto LAB_584fc;
    sdesc[0] = 0;
    *(volatile uint16_t*)(sdesc + 2) = 0x2800;
    iVar1 = bt_uuid_cmp(*param_1, (int)(intptr_t)sdesc);
    if (iVar1 != 0) {
        iVar1 = param_3[2];
        if (iVar1 == 0) return 1;
        if (param_2 <= *(volatile uint16_t*)(iVar1 + 2)) return 1;
        goto LAB_58420;
    }
    uVar7 = net_buf_frags_len_0(param_3[1]);
    if ((unsigned)*(volatile uint16_t*)(iVar6 + 0x1e) < (unsigned)*(volatile uint16_t*)(iVar6 + 0x2e))
        uVar2 = (unsigned)*(volatile uint16_t*)(iVar6 + 0x1e) - (int)uVar7;
    else
        uVar2 = (unsigned)*(volatile uint16_t*)(iVar6 + 0x2e) - (int)uVar7;
    if (uVar2 < 4) return 0;
    iVar1 = net_buf_frag_last((int)(uVar7 >> 0x20));
    iVar3 = (int)net_buf_frags_len_0(param_3[1]);
    if ((unsigned)*(volatile uint16_t*)(iVar6 + 0x1e) < (unsigned)*(volatile uint16_t*)(iVar6 + 0x2e))
        uVar2 = (unsigned)*(volatile uint16_t*)(iVar6 + 0x1e) - iVar3;
    else
        uVar2 = (unsigned)*(volatile uint16_t*)(iVar6 + 0x2e) - iVar3;
    uVar4 = net_buf_simple_tailroom(iVar1 + 0xc);
    if (uVar2 < uVar4) {
        iVar3 = (int)net_buf_frags_len_0(param_3[1]);
        if ((unsigned)*(volatile uint16_t*)(iVar6 + 0x1e) < (unsigned)*(volatile uint16_t*)(iVar6 + 0x2e))
            iVar3 = (unsigned)*(volatile uint16_t*)(iVar6 + 0x1e) - iVar3;
        else
            iVar3 = (unsigned)*(volatile uint16_t*)(iVar6 + 0x2e) - iVar3;
    } else {
        iVar3 = net_buf_simple_tailroom(iVar1 + 0xc);
    }
    if (iVar3 == 0) {
        uVar7 = net_buf_pool_get(*(volatile uint8_t*)(param_3[1] + 10));
        iVar1 = bt_conn_alloc_pdu_buf((int)uVar7, (int)(uVar7 >> 0x20), 0, 0);
        if (iVar1 == 0) return 0;
        net_buf_frag_add(param_3[1], iVar1);
    }
    local_70 = 0;
    uVar2 = ((unsigned(*)(uint32_t, uint32_t*, void*, int))(uintptr_t)param_1[1])(local_64, param_1, (void*)auStack_60, 0x10);
    if ((int)uVar2 < 0) goto LAB_584fc;
    if (*(volatile uint8_t*)((int)(intptr_t)param_3 + 0x10) == uVar2) {
        iVar6 = memcmp(param_3[3], (int)(intptr_t)auStack_60);
LAB_58534:
        if (iVar6 == 0) {
            *(volatile uint8_t*)((int)(intptr_t)param_3 + 0x11) = 0;
            puVar5 = net_buf_simple_add(iVar1 + 0xc, 4);
            param_3[2] = puVar5;
            *(volatile uint16_t*)puVar5 = (uint16_t)param_2;
            iVar1 = param_3[2];
LAB_58420:
            *(volatile uint16_t*)(iVar1 + 2) = (uint16_t)param_2;
            return 1;
        }
    } else {
        iVar6 = bt_uuid_create((int)(intptr_t)sdesc, param_3[3], 0);
        if (iVar6 == 0) {
            local_74 = ((unsigned long)&rodata_f43ca) /*=0xf43ca*/;
            local_70 = *(volatile uint8_t*)((int)(intptr_t)param_3 + 0x10);
        } else {
            iVar6 = bt_uuid_create((int)(intptr_t)auStack_50, (int)(intptr_t)auStack_60, uVar2 & 0xff);
            if (iVar6 != 0) {
                iVar6 = bt_uuid_cmp((int)(intptr_t)sdesc, (int)(intptr_t)auStack_50);
                goto LAB_58534;
            }
            local_74 = ((unsigned long)&rodata_f43e9) /*=0xf43e9*/;
            local_70 = uVar2;
        }
        local_78 = 3;
        att_log_emit_3arg(((unsigned long)&rodata_88100) /*=0x88100*/, 0x1880, (int)(intptr_t)&local_78);
    }
LAB_584fc:
    param_3[2] = 0;
    return 1;
}
