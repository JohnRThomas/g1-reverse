#include "g1_app_symbols.h"
#include <stddef.h>
/* readable reconstruction; identity: FUN_0005d0ac @ 0x0005d0ac
 * public-name: smp_dhkey_check_generate
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_smp_send_pdu                          <= FUN_0005cb38 @ 0x0005cb38
 *   smp_dhkey_check_generate                 <= FUN_0005d0ac @ 0x0005d0ac
 *   bt_crypto_f5                             <= FUN_0005ecdc @ 0x0005ecdc
 *   net_buf_simple_add                       <= FUN_0005f5d0 @ 0x0005f5d0
 *   smp_log_message                          <= FUN_00083074 @ 0x00083074
 *   atomic_set_bit                           <= FUN_00083090 @ 0x00083090
 *   smp_create_pdu                           <= FUN_000830b0 @ 0x000830b0
 *   bt_crypto_f6                             <= FUN_00083634 @ 0x00083634
 *   memcmp                                   <= FUN_00086be4 @ 0x00086be4
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_88180                             @ 0x00088180
 */
/* Reconstructed FUN_0005d0ac @ 0x5d0ac  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void bt_smp_send_pdu(int, unsigned int, unsigned int);
extern int bt_crypto_f5(int, int, int, int);
extern int net_buf_simple_add(int, int);
extern int smp_log_message(int, int, int);
extern void atomic_set_bit(int, int);
extern int smp_create_pdu(int, int);
extern int bt_crypto_f6(int, int, int, int);
extern int memcmp(const void *, const void *, size_t);
extern void memset_bytes(void*, int, int);

int smp_dhkey_check_generate(int param_1)
{
    uint32_t frame[12];           /* local_58 = frame+0, local_48 = frame+4 */
    uint32_t auStack_68[4];
    uint32_t *local_48 = frame + 4;
    uint32_t *local_58 = frame + 0;
    int iVar1, iVar6, iVar7, iVar8;
    unsigned sw;
    uint32_t *puVar4, *puVar5, *puVar9, *puVar10;
    volatile int logbuf[8];

    memset_bytes(local_48, 0, 0x10);
    sw = *(volatile uint8_t*)(param_1 + 8);
    switch (sw) {
        case 0:
        case 3:
            break;
        case 1:
        case 2:
            local_48[0] = *(volatile uint32_t*)(param_1 + 0xd8);
            break;
        case 5:
            puVar5 = (uint32_t*)(intptr_t)*(volatile uint32_t*)(param_1 + 0xe4);
            if (puVar5 != 0) {
                puVar9 = puVar5 + 4;
                puVar4 = local_48;
                do {
                    uint32_t a = puVar5[0], b = puVar5[1];
                    puVar5 += 2;
                    puVar4[0] = a; puVar4[1] = b;
                    puVar4 += 2;
                } while (puVar5 != puVar9);
            }
            break;
        default:
            smp_log_message(((unsigned long)&rodata_88180) /*=0x88180*/, 0x1840, (int)(intptr_t)logbuf);
            return 8;
    }
    iVar6 = param_1 + 199;
    iVar7 = param_1 + 0x37;
    iVar8 = param_1 + 0x27;
    iVar1 = bt_crypto_f5(param_1 + 0x97, iVar7, iVar8, *(volatile int*)(param_1 + 0xf0) + 0x97);
    if (iVar1 == 0) {
        iVar1 = bt_crypto_f6(iVar6, iVar8, iVar7, (int)(intptr_t)local_48);
        if (iVar1 == 0) {
            if (*(volatile int8_t*)(param_1 + 8) == 5) {
                puVar4 = (uint32_t*)(intptr_t)*(volatile uint32_t*)(param_1 + 0xe0);
                if (puVar4 == 0) {
                    memset_bytes(local_48, 0, 0x10);
                } else {
                    puVar10 = puVar4 + 4;
                    puVar9 = local_48;
                    do {
                        uint32_t a = puVar4[0], b = puVar4[1];
                        puVar4 += 2;
                        puVar9[0] = a; puVar9[1] = b;
                        puVar9 += 2;
                    } while (puVar4 != puVar10);
                }
            }
            iVar1 = bt_crypto_f6(iVar6, iVar7, iVar8, (int)(intptr_t)local_48);
            if (iVar1 == 0) {
                iVar1 = memcmp(param_1 + 0xb7, (int)(intptr_t)auStack_68, 0x10);
                if (iVar1 != 0) return 0xb;
                iVar1 = smp_create_pdu(param_1, 0xd);
                if (iVar1 == 0) return 8;
                puVar4 = (uint32_t*)(intptr_t)net_buf_simple_add(iVar1 + 0xc, 0x10);
                puVar5 = local_58;
                do {
                    uint32_t a = puVar5[0], b = puVar5[1];
                    puVar5 += 2;
                    puVar4[0] = a; puVar4[1] = b;
                    puVar4 += 2;
                } while (puVar5 != local_48);
                bt_smp_send_pdu(param_1, iVar1, 0);
                atomic_set_bit(param_1 + 4, 1);
                return 0;
            }
        }
    }
    smp_log_message(((unsigned long)&rodata_88180) /*=0x88180*/, 0x1040, (int)(intptr_t)logbuf);
    return 8;
}
