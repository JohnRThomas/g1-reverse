#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_2          => struct g1_layout_net_buf__param_0172                    [param_0172; library]
 * Raw function identity: 0x00058cfc.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00058cfc @ 0x00058cfc
 * public-name: bt_att_recv
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   att_op_get_type                          <= FUN_000582b8 @ 0x000582b8
 *   bt_att_recv                              <= FUN_00058cfc @ 0x00058cfc
 *   net_buf_unref                            <= FUN_0005f24c @ 0x0005f24c
 *   net_buf_ref                              <= FUN_0005f2d4 @ 0x0005f2d4
 *   net_buf_simple_pull_5f594                <= FUN_0005f594 @ 0x0005f594
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   att_log_emit_3arg                        <= FUN_00081ddc @ 0x00081ddc
 *   att_send_error_rsp                       <= FUN_000821f4 @ 0x000821f4
 *   atomic_test_and_set_bit_0                <= FUN_00082236 @ 0x00082236
 *   att_exchange_mtu_req                     <= FUN_00082396 @ 0x00082396
 * address symbols (name @ address):
 *   rodata_88100                             @ 0x00088100
 *   rodata_8b2b4                             @ 0x0008b2b4
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f4388                             @ 0x000f4388
 *   rodata_f45af                             @ 0x000f45af   [INLINED -- G6 literal batch]
 */
/* Reconstructed FUN_00058cfc @ 0x58cfc  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../../../headers/g1_log.h"
extern uint64_t att_op_get_type(int);
extern void net_buf_unref(int);
extern int net_buf_ref(int);
extern int net_buf_simple_pull_5f594(int, int);
extern void assert_post_action(int, int);
extern void att_log_emit_3arg(int, int, int);
extern void att_send_error_rsp(int, int, int, int);
extern int atomic_test_and_set_bit_0(int, int);
extern int att_exchange_mtu_req(int);

int bt_att_recv(int param_1, int param_2)
{
    volatile uint8_t *pbVar3;
    int cVar1 = 0;
    int iVar7, iVar8, iVar6;
    int local_44;
    unsigned uVar5 = 0;
    uint64_t uVar9;
    volatile int logbuf[8];

    if (*(volatile int16_t*)(param_2 + 0x10) == 0) {
        att_log_emit_3arg(((unsigned long)&rodata_88100) /*=0x88100*/, 0x1040, (int)(intptr_t)logbuf);
        return 0;
    }
    pbVar3 = (volatile uint8_t*)(intptr_t)net_buf_simple_pull_5f594(param_2 + 0xc, 1);
    iVar8 = ((unsigned long)&rodata_8b2b4) /*=0x8b2b4*/;
    if (*(volatile int*)(param_1 - 8) == 0) return 0;
    iVar6 = 0;
    do {
        iVar7 = ((unsigned long)&rodata_8b2b4) /*=0x8b2b4*/ + iVar6 * 8;
        if (*(volatile uint8_t*)(((unsigned long)&rodata_8b2b4) /*=0x8b2b4*/ + iVar6 * 8) == *pbVar3) {
            local_44 = *(volatile int*)(param_1 + 0x13c);
            if (local_44 != 0) goto LAB_dbc;
            {
                int t = net_buf_ref(param_2);
                cVar1 = *(volatile int8_t*)(iVar7 + 2);
                *(volatile int*)(param_1 + 0x13c) = t;
            }
            if (cVar1 == 1) {
                iVar7 = atomic_test_and_set_bit_0(param_1 + 0x118, local_44);
                goto joined;
            } else if (cVar1 == 5) {
                iVar7 = atomic_test_and_set_bit_0(param_1 + 0x118, 1);
            joined:
                if (iVar7 != 0) {
                    att_log_emit_3arg(((unsigned long)&rodata_88100) /*=0x88100*/, 0x1080, (int)(intptr_t)logbuf);
                    goto LAB_d9c;
                }
            }
            iVar8 = iVar8 + iVar6 * 8;
            if ((unsigned)*(volatile uint16_t*)(param_2 + 0x10) < (unsigned)*(volatile uint8_t*)(iVar8 + 1)) {
                att_log_emit_3arg(((unsigned long)&rodata_88100) /*=0x88100*/, 0x2040, (int)(intptr_t)logbuf);
                if (*(volatile int8_t*)(iVar8 + 2) != 1) goto LAB_d9c;
                iVar8 = 4;
            } else {
                iVar8 = ((int(*)(int,int))(*(volatile uintptr_t*)(iVar8 + 4)))(param_1 - 8, param_2);
                if (cVar1 != 1 || iVar8 == 0) goto LAB_d9c;
            }
            uVar5 = *pbVar3;
            goto LAB_e12;
        }
        iVar6 = iVar6 + 1;
    } while (iVar6 != 0x1e);
    if (*(volatile int*)(param_1 + 0x13c) != 0) {
    LAB_dbc:
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)"!att_chan->rsp_buf") /*=0xf45af*/, ((unsigned long)&rodata_f4388) /*=0xf4388*/, 0xb54);
        assert_post_action(((unsigned long)&rodata_f4388) /*=0xf4388*/, 0xb54);
    }
    {
        int t = net_buf_ref(param_2);
        *(volatile int*)(param_1 + 0x13c) = t;
    }
    att_log_emit_3arg(((unsigned long)&rodata_88100) /*=0x88100*/, 0x1880, (int)(intptr_t)logbuf);
    uVar9 = att_op_get_type(*pbVar3);
    uVar5 = (unsigned)(uVar9 >> 0x20);
    if ((int)uVar9 != 0 && (int)uVar9 != 5) {
        iVar8 = 6;
    LAB_e12:
        att_send_error_rsp(param_1 - 8, uVar5, 0, iVar8);
    }
LAB_d9c:
    net_buf_unref(*(volatile int*)(param_1 + 0x13c));
    *(volatile int*)(param_1 + 0x13c) = 0;
    return 0;
}
