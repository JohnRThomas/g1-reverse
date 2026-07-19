#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00053bd8 @ 0x00053bd8
 * public-name: le_conn_param_update_handle
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   le_conn_param_update_handle              <= FUN_00053bd8 @ 0x00053bd8
 *   ble_conn_unref                           <= FUN_000566a4 @ 0x000566a4
 *   ble_conn_lookup_masked                   <= FUN_00056908 @ 0x00056908
 *   ble_notify_le_param_updated              <= FUN_00056ae0 @ 0x00056ae0
 *   k_work_schedule                          <= FUN_00073418 @ 0x00073418
 *   atomic_or                                <= FUN_00080e6a @ 0x00080e6a
 *   bt_log_forward_3arg                      <= FUN_00080ea2 @ 0x00080ea2
 *   atomic_and_3                             <= FUN_00080ea8 @ 0x00080ea8
 *   l2cap_send_conn_param_req                <= FUN_00081adc @ 0x00081adc
 * address symbols (name @ address):
 *   rodata_28000                             @ 0x00028000
 *   rodata_88138                             @ 0x00088138
 *   rodata_f2db7                             @ 0x000f2db7
 */
/* Reconstructed FUN_00053bd8 @ 0x53bd8 CFG_VERIFY_ORACLE0_R0_POINTER */

#include <stdint.h>
extern void ble_conn_unref(int);
extern uint64_t ble_conn_lookup_masked(uint32_t,int);
extern void ble_notify_le_param_updated(int);
extern void k_work_schedule(int,uint32_t,int,int);
extern uint64_t atomic_or(void*,int);
extern void bt_log_forward_3arg(uint32_t,int,void*);
extern void atomic_and_3(void*,uint32_t);
extern void l2cap_send_conn_param_req(int,void*);

void le_conn_param_update_handle(int param_1){
    volatile char *pcVar4 = *(char* volatile*)(param_1+0xc);
    uint16_t uVar1 = *(volatile uint16_t*)(pcVar4+1);
    uint64_t uVar6 = ble_conn_lookup_masked(uVar1, 1);
    uint32_t uVar3 = (uint32_t)(uVar6 >> 32);
    int iVar2 = (int)(uint32_t)uVar6;
    uint32_t local_30, local_2c, uStack_28, local_20, local_1c;
    if (iVar2 == 0){
        local_2c = ((unsigned long)&rodata_f2db7) /*=0xf2db7*/; local_30 = 3; uStack_28 = uVar1;
        bt_log_forward_3arg(((unsigned long)&rodata_88138) /*=0x88138*/, 0x1840, &local_30);
        return;
    }
    volatile uint32_t *piVar5 = (volatile uint32_t *)(iVar2 + 4);
    if (*pcVar4 == 0x1a){
        if (*(volatile char*)(iVar2+3) == 1){
            uVar6 = atomic_or((void*)piVar5, 0x400);
            uVar3 = (uint32_t)(uVar6 >> 32);
            if (((int32_t)((uint32_t)uVar6 << 0x15)) >= 0){
                local_20 = *(volatile uint32_t*)(iVar2+0xa8);
                local_1c = *(volatile uint32_t*)(iVar2+0xb0);
                l2cap_send_conn_param_req(iVar2, &local_20);
                goto L_c44;
            }
            goto L_c4c;
        }
        goto L_c74;
    } else {
      L_c4c:
        if (*pcVar4 != 0) goto L_c74;
        *(volatile uint16_t*)(iVar2+0xa6) = *(volatile uint16_t*)(pcVar4+3);
        *(volatile uint16_t*)(iVar2+0xac) = *(volatile uint16_t*)(pcVar4+5);
        *(volatile uint16_t*)(iVar2+0xae) = *(volatile uint16_t*)(pcVar4+7);
      L_c68:
        atomic_and_3((void*)piVar5, 0xfffffeff);
    }
    ble_notify_le_param_updated(iVar2);
  L_c44:
    ble_conn_unref(iVar2);
    return;
  L_c74:
    /* The original uses LDA then tests bit 8 via LSLS #23/BPL. */
    if (((*piVar5 & 0x100u) == 0) || (*pcVar4 != 0x20) || (*(volatile char*)(iVar2+0xb4) == 0)) goto L_c68;
    *(volatile char*)(iVar2+0xb4) = *(volatile char*)(iVar2+0xb4) - 1;
    k_work_schedule(iVar2+0x60, uVar3, ((unsigned long)&rodata_28000) /*=0x28000*/, 0);
    ble_notify_le_param_updated(iVar2);
    goto L_c44;
    (void)local_2c; (void)uStack_28; (void)local_1c;
}
