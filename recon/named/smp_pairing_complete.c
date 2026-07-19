/* readable reconstruction; identity: FUN_0005daf0 @ 0x0005daf0
 * public-name: smp_pairing_complete
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ble_notify_remote_info_available         <= FUN_00056da8 @ 0x00056da8
 *   smp_send_security_req                    <= FUN_0005d964 @ 0x0005d964
 *   smp_pairing_complete                     <= FUN_0005daf0 @ 0x0005daf0
 *   bt_keys_clear                            <= FUN_0005ea18 @ 0x0005ea18
 *   bt_keys_store                            <= FUN_0005ec18 @ 0x0005ec18
 *   atomic_test_bit                          <= FUN_00082ff6 @ 0x00082ff6
 *   smp_log_message                          <= FUN_00083074 @ 0x00083074
 *   att_chan_reset                           <= FUN_00083204 @ 0x00083204
 * address symbols (name @ address):
 *   rodata_88180                             @ 0x00088180
 *   rodata_f4f89                             @ 0x000f4f89
 *   rodata_f520f                             @ 0x000f520f
 *   rodata_f5220                             @ 0x000f5220
 *   g_bt_conn_auth_info_cb_list              @ 0x2000ad20
 */
/* Reconstructed FUN_0005daf0 @ 0x5daf0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int ble_notify_remote_info_available(int,int,int);
extern int smp_send_security_req(int);
extern int bt_keys_clear(int);
extern int bt_keys_store(int);
extern int atomic_test_bit(int,int);
extern int smp_log_message(int,int,void*);
extern int att_chan_reset(int);

void smp_pairing_complete(int param_1, int param_2)
{
    int iVar1;
    unsigned char uVar2;
    unsigned int uVar3;
    int *piVar4;
    void (*pcVar5)(int,int);
    uint32_t *puVar6;
    int iVar7;
    int iVar8;
    uint32_t *puVar9;
    int local_20, local_1c;

    iVar7 = *(int *)(param_1 + 0xf0);
    iVar8 = param_1 + 4;
    if (*(char *)(iVar7 + 0xd) == '\a') {
        if (param_2 == 0) {
            iVar8 = atomic_test_bit(iVar8, 0xd);
            if (iVar8 != 0) {
                bt_keys_store(*(uint32_t *)(iVar7 + 0xc0));
            }
            puVar6 = (uint32_t *)*(void * volatile *)0x2000ad20;
            if (puVar6 != (uint32_t *)0x0) {
                puVar9 = (uint32_t *)*puVar6;
                if (puVar9 != (uint32_t *)0x0) {
                    puVar9 = puVar9 + -3;
                }
                pcVar5 = (void (*)(int,int))puVar6[-3];
                if (pcVar5 == 0) goto LAB_0005dba4;
                do {
                    (*pcVar5)(iVar7, iVar8);
LAB_0005dba4:
                    if (puVar9 == (uint32_t *)0x0) break;
                    do {
                        pcVar5 = (void (*)(int,int))*puVar9;
                        if (puVar9[3] == 0) {
                            puVar9 = (uint32_t *)0x0;
                            if (pcVar5 == 0) goto LAB_0005dbba;
                            break;
                        }
                        puVar9 = (uint32_t *)(puVar9[3] + -0xc);
                    } while (pcVar5 == 0);
                } while (1);
            }
            goto LAB_0005dbba;
        }
        uVar3 = param_2 - 1U & 0xff;
        if (uVar3 < 0xf) goto LAB_0005db1a;
        uVar3 = 9;
    } else {
        local_1c = 0x000f4f89;
        local_20 = 2;
        smp_log_message(0x00088180, 0x1080, &local_20);
        uVar3 = 7;
LAB_0005db1a:
        uVar3 = (unsigned int)*(volatile unsigned char *)(0x000f5220 + uVar3);
    }
    if ((*(int *)(iVar7 + 0xc0) != 0) &&
        ((*(char *)(*(int *)(iVar7 + 0xc0) + 0xc) == '\0' ||
          (iVar1 = atomic_test_bit(iVar8, 2), iVar1 != 0)))) {
        bt_keys_clear(*(uint32_t *)(iVar7 + 0xc0));
        *(uint32_t *)(iVar7 + 0xc0) = 0;
    }
    iVar1 = atomic_test_bit(iVar8, 2);
    if (iVar1 == 0) {
        if (uVar3 < 8) {
            uVar2 = *(volatile unsigned char *)(0x000f520f + uVar3);
        } else {
            uVar2 = 0x1f;
        }
        ble_notify_remote_info_available(iVar7, uVar2, uVar3);
    }
    iVar8 = atomic_test_bit(iVar8, 3);
    if ((iVar8 != 0) && (piVar4 = (int *)*(void * volatile *)0x2000ad20, piVar4 != (int *)0x0)) {
        iVar8 = *piVar4;
        if (iVar8 != 0) {
            iVar8 = iVar8 + -0xc;
        }
        pcVar5 = (void (*)(int,int))piVar4[-2];
        if (pcVar5 != 0) goto LAB_0005dbf8;
        while (iVar8 != 0) {
            do {
                pcVar5 = *(void (**)(int,int))(iVar8 + 4);
                if (*(int *)(iVar8 + 0xc) == 0) {
                    iVar8 = 0;
                    if (pcVar5 == 0) goto LAB_0005dbba;
                    break;
                }
                iVar8 = *(int *)(iVar8 + 0xc) + -0xc;
            } while (pcVar5 == 0);
LAB_0005dbf8:
            (*pcVar5)(iVar7, uVar3);
        }
    }
LAB_0005dbba:
    att_chan_reset(param_1);
    if ((*(char *)(iVar7 + 0xd) == '\a') && (*(char *)(iVar7 + 9) != *(char *)(iVar7 + 10))) {
        smp_send_security_req(iVar7);
        return;
    }
    return;
}
