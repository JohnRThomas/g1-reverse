#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_3          => struct g1_layout_bt_addr_le__param_0639                 [param_0639; library]
 *   param_4          => struct g1_layout_param_0640_mechanical__param_0640      [param_0640; G1-original]
 *   param_6          => struct g1_layout_smp_c1_param__param_0641               [param_0641; library]
 *   param_5          => struct g1_layout_bt_addr_le_t__param_0642               [param_0642; library]
 *   local_38         => struct g1_layout_smp_c1_locals__stack_1538              [stack_1538; library]
 * Raw function identity: 0x0008323a.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0008323a @ 0x0008323a
 * public-name: smp_c1
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   smp_c1                                   <= FUN_0008323a @ 0x0008323a
 */
/* CPUAPP Zephyr Bluetooth smp_c1 @ 0x0008323a.
 * Raw/address back-map: FUN_0008323a / 0x0008323a.
 */
#include <stdint.h>
extern unsigned int bt_encrypt_le(int, int, int); /* FUN_00081326 */
#define smp_c1 smp_c1

int smp_c1(const uint8_t key[16], const uint8_t random[16],
                 const uint8_t preq[7], const uint8_t pres[7],
                 const uint8_t *initiator_addr, const uint8_t *responder_addr,
                 uint8_t encrypted[16])
{
    uint8_t p1[16];
    p1[0] = initiator_addr[0];
    p1[1] = responder_addr[0];
    for (unsigned i = 0; i < 7; ++i) p1[2 + i] = preq[i];
    for (unsigned i = 0; i < 7; ++i) p1[9 + i] = pres[i];
    for (unsigned i = 0; i < 16; ++i) encrypted[i] = random[i] ^ p1[i];
    int status = bt_encrypt_le(key, encrypted, encrypted);
    if (status != 0)
        return status;
    uint8_t p2[16];
    for (unsigned i = 0; i < 6; ++i) p2[i] = responder_addr[1 + i];
    for (unsigned i = 0; i < 6; ++i) p2[6 + i] = initiator_addr[1 + i];
    for (unsigned i = 12; i < 16; ++i) p2[i] = 0;
    for (unsigned i = 0; i < 16; ++i) encrypted[i] ^= p2[i];
    return bt_encrypt_le(key, encrypted, encrypted);
}
