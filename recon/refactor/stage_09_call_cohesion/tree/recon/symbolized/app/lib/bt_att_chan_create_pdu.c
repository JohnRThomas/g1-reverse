#include "g1_app_symbols.h"
#include "../../../headers/g1_dedupe.h"
struct k_thread;
/* readable reconstruction; identity: FUN_000585f0 @ 0x000585f0
 * public-name: bt_att_chan_create_pdu
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   att_op_get_type                          <= FUN_000582b8 @ 0x000582b8
 *   bt_att_chan_create_pdu                   <= FUN_000585f0 @ 0x000585f0
 *   net_buf_reset                            <= FUN_0005ee6c @ 0x0005ee6c
 *   net_buf_unref                            <= FUN_0005f24c @ 0x0005f24c
 *   net_buf_ref                              <= FUN_0005f2d4 @ 0x0005f2d4
 *   net_buf_simple_reserve                   <= FUN_0005f4d4 @ 0x0005f4d4
 *   net_buf_simple_add                       <= FUN_0005f5d0 @ 0x0005f5d0
 *   net_buf_pool_get_727ac                   <= FUN_000727ac @ 0x000727ac
 *   k_current_get                            <= FUN_000748ac @ 0x000748ac
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   att_create_pdu_reserve4                  <= FUN_0008181a @ 0x0008181a
 *   att_log_emit_3arg                        <= FUN_00081ddc @ 0x00081ddc
 * address symbols (name @ address):
 *   rodata_88100                             @ 0x00088100
 *   rodata_f0000                             @ 0x000f0000
 *   rodata_f3ec2                             @ 0x000f3ec2
 *   rodata_f4475                             @ 0x000f4475
 *   rodata_f449a                             @ 0x000f449a
 *   rodata_f44c2                             @ 0x000f44c2
 *   g_bt_att_pool                            @ 0x20003a28
 */
/* Reconstructed FUN_000585f0 @ 0x585f0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../../../headers/g1_log.h"
extern int att_op_get_type(int);
extern int net_buf_reset(void);
extern int net_buf_unref(int);
extern int net_buf_ref(void);
extern int net_buf_simple_reserve(int,int);
extern int net_buf_simple_add(int,int);
extern int net_buf_pool_get_727ac(int);
extern struct k_thread *k_current_get(void);
extern void assert_post_action(const char *, unsigned int);
extern int att_create_pdu_reserve4(int,int,int,int);
extern int att_log_emit_3arg(int,int,void*);

int bt_att_chan_create_pdu(unsigned int param_1, unsigned int param_2, int param_3)
{
    int iVar1;
    unsigned char *puVar2;
    unsigned int *puVar3;
    unsigned int uVar4, uVar5;
    int local_48, local_44;
    unsigned int uStack_40, local_3c;
    int local_28, local_24;

    uStack_40 = (unsigned int)*(unsigned short *)(param_1 + 0x2e);
    if ((unsigned int)*(unsigned short *)(param_1 + 0x1e) <= (unsigned int)*(unsigned short *)(param_1 + 0x2e)) {
        uStack_40 = (unsigned int)*(unsigned short *)(param_1 + 0x1e);
    }
    if (uStack_40 < param_3 + 1U) {
        local_44 = ((unsigned long)&rodata_f4475) /*=0xf4475*/;
        uVar4 = 0x2080;
        local_48 = 4;
        local_3c = param_3 + 1U;
        goto LAB_00058624;
    }
    iVar1 = att_op_get_type(param_2);
    if (iVar1 == 2) {
        if ((param_2 == 0xf) || (param_2 == 0x21)) goto LAB_000586e2;
        if (*(int *)(param_1 + 0x148) == 0) {
            puVar3 = (unsigned int *)(param_1 + 0x148);
            if (*(int *)(param_1 + 0x144) == 0) {
                G1_ASSERT_FAIL((0, 0, 0, 0x2cd), (0, 0x2cd));
            }
            iVar1 = net_buf_ref();
            net_buf_reset();
            net_buf_simple_reserve(iVar1 + 0xc, 9);
            goto LAB_000586ce;
        }
        local_44 = ((unsigned long)&rodata_f449a) /*=0xf449a*/;
        uStack_40 = param_1;
    } else {
        if (iVar1 == 4) {
LAB_000586e2:
            uVar5 = ((unsigned long)&rodata_f0000) /*=0xf0000*/;
            uVar4 = 0;
        } else {
            uVar5 = 0xffffffff;
            uVar4 = 0xffffffff;
        }
        iVar1 = att_create_pdu_reserve4(0, 0, uVar5, uVar4);
        if (iVar1 != 0) {
            k_current_get();
            puVar3 = (unsigned int *)net_buf_pool_get_727ac(((unsigned long)&g_bt_att_pool) /*=0x20003a28*/);
            if (puVar3 == (unsigned int *)0x0) {
                local_24 = ((unsigned long)&rodata_f44c2) /*=0xf44c2*/;
                local_28 = 2;
                att_log_emit_3arg(((unsigned long)&rodata_88100) /*=0x88100*/, 0x1080, &local_28);
                net_buf_unref(iVar1);
                return 0;
            }
LAB_000586ce:
            *puVar3 = param_1;
            *(unsigned int **)(iVar1 + 0x18) = puVar3;
            puVar2 = (unsigned char *)net_buf_simple_add(iVar1 + 0xc, 1);
            *puVar2 = (char)param_2;
            return iVar1;
        }
        local_44 = ((unsigned long)&rodata_f3ec2) /*=0xf3ec2*/;
        uStack_40 = param_2;
    }
    uVar4 = 0x1840;
    local_48 = 3;
LAB_00058624:
    (void)local_44; (void)uStack_40; (void)local_3c;
    att_log_emit_3arg(((unsigned long)&rodata_88100) /*=0x88100*/, uVar4, &local_48);
    return 0;
}
