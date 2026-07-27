#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0005d964 @ 0x0005d964
 * public-name: smp_send_security_req
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   conn_auth_cb_get_or_init                 <= FUN_0005cac0 @ 0x0005cac0
 *   smp_auth_get_pairing_method              <= FUN_0005caec @ 0x0005caec
 *   smp_init                                 <= FUN_0005cc30 @ 0x0005cc30
 *   smp_build_auth_flags                     <= FUN_0005d568 @ 0x0005d568
 *   smp_send_security_req                    <= FUN_0005d964 @ 0x0005d964
 *   bt_keys_get_addr                         <= FUN_0005e6a8 @ 0x0005e6a8
 *   bt_keys_find                             <= FUN_0005e7c8 @ 0x0005e7c8
 *   net_buf_unref                            <= FUN_0005f24c @ 0x0005f24c
 *   net_buf_simple_add                       <= FUN_0005f5d0 @ 0x0005f5d0
 *   bt_conn_create_pdu                       <= FUN_00081820 @ 0x00081820
 *   atomic_test_bit                          <= FUN_00082ff6 @ 0x00082ff6
 *   smp_chan_lookup                          <= FUN_0008307a @ 0x0008307a
 *   atomic_set_bit                           <= FUN_00083090 @ 0x00083090
 *   smp_create_pdu                           <= FUN_000830b0 @ 0x000830b0
 * address symbols (name @ address):
 *   g_bt_settings_load_done                  @ 0x2001d532
 */
/* Reconstructed FUN_0005d964 @ 0x5d964  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int conn_auth_cb_get_or_init(int);
extern int smp_auth_get_pairing_method(int);
extern int smp_init(int);
extern unsigned int smp_build_auth_flags(int, unsigned int);
extern int bt_keys_get_addr(int, int);
extern int bt_keys_find(int, int, int);
extern void net_buf_unref(int);
extern int net_buf_simple_add(int, int);
extern int bt_conn_create_pdu(int, int, int, int, int);
extern int atomic_test_bit(int, int);
extern int smp_chan_lookup(void);
extern void atomic_set_bit(int, int);
extern int smp_create_pdu(int, int);

int smp_send_security_req(int param_1)
{
    int iVar2, iVar3, iVar6, iVar8, cac;
    unsigned uVar7;
    int puVar5;
    uint8_t uVar1;

    if (*(volatile uint8_t*)(param_1 + 3) != 1) return -0x16;
    iVar2 = smp_chan_lookup();
    if (iVar2 == 0) return -0x80;
    iVar8 = iVar2 + 4;
    iVar3 = atomic_test_bit(iVar8, 4);
    if (iVar3 != 0) return -5;
    iVar3 = atomic_test_bit(iVar8, 3);
    if (iVar3 != 0) return -0x10;
    iVar3 = atomic_test_bit(iVar8, 1);
    if (iVar3 != 0) return -0x10;
    cac = conn_auth_cb_get_or_init(iVar2);
    uVar7 = *(volatile uint8_t*)(*(volatile int*)(iVar2 + 0xf0) + 10);
    if (uVar7 == 3) {
        iVar6 = smp_auth_get_pairing_method(iVar2);
        if (iVar6 != 3) goto LAB_5da60;
        if (cac != 0) {
            uVar7 = *(volatile uint32_t*)(cac + 0xc);
            if (uVar7 == 0) goto MAIN;
            goto LAB_5da60;
        }
    } else if (uVar7 > 3) {
        if (uVar7 != 4) goto MAIN;
        iVar6 = smp_auth_get_pairing_method(iVar2);
        if (iVar6 == 3) {
            if (cac == 0) goto MAIN;
            if (*(volatile int*)(cac + 0xc) == 0) goto MAIN;
        }
        uVar7 = *(volatile uint8_t*)((unsigned long)&g_bt_settings_load_done) /*=0x2001d532*/;
        if (uVar7 == 0) goto MAIN;
        goto LAB_5da60;
    } else {
        if ((uint32_t)(uVar7 - 1) <= 1) goto LAB_5da60;
    }
MAIN:
    iVar3 = atomic_test_bit(param_1 + 4, 0xb);
    if (iVar3 != 0) return -0x16;
    if (*(volatile int*)(param_1 + 0xc0) == 0) {
        iVar3 = bt_keys_find(0x20, *(volatile uint8_t*)(param_1 + 8), param_1 + 0x90);
        *(volatile int*)(param_1 + 0xc0) = iVar3;
        if (iVar3 == 0) {
            iVar3 = bt_keys_find(4, *(volatile uint8_t*)(param_1 + 8), param_1 + 0x90);
            *(volatile int*)(param_1 + 0xc0) = iVar3;
        }
    }
    iVar3 = *(volatile int*)(param_1 + 0xc0);
    if (iVar3 == 0) return -0x16;
    if ((*(volatile uint16_t*)(iVar3 + 0xe) & 0x24) == 0) return -0x16;
    if (*(volatile uint8_t*)(param_1 + 10) <= 2) goto LAB_5da60;
    if ((*(volatile uint8_t*)(iVar3 + 0xd) & 1) == 0) return -0x16;
    if (*(volatile uint8_t*)(param_1 + 10) == 3) goto LAB_5da60;
    if ((*(volatile uint16_t*)(iVar3 + 0xe) & 0x20) == 0) return -0x16;
    if (*(volatile int8_t*)(iVar3 + 0xc) != 0x10) return -0x16;
LAB_5da60:
    iVar3 = *(volatile int*)(param_1 + 0xc0);
    if (iVar3 == 0) {
        iVar3 = bt_keys_get_addr(*(volatile uint8_t*)(param_1 + 8), param_1 + 0x90);
        *(volatile int*)(param_1 + 0xc0) = iVar3;
        if (iVar3 == 0) return -0xc;
    }
    iVar3 = smp_init(iVar2);
    if (iVar3 != 0) return -0x69;
    iVar6 = smp_create_pdu(iVar2, 0xb);
    if (iVar6 == 0) return -0x69;
    puVar5 = net_buf_simple_add(iVar6 + 0xc, 1);
    uVar1 = (uint8_t)smp_build_auth_flags(iVar2, 9);
    *(volatile uint8_t*)puVar5 = uVar1;
    {
        int rv = bt_conn_create_pdu(param_1, 6, iVar6, 0, 0);
        if (rv == 0) {
            atomic_set_bit(iVar8, 0xf);
            atomic_set_bit(iVar2, 1);
            return 0;
        }
        net_buf_unref(iVar6);
        return rv;
    }
}
