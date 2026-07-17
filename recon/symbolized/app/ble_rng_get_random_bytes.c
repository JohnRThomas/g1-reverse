#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00055c64 @ 0x00055c64
 * public-name: ble_rng_get_random_bytes
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_hci_le_rand                           <= FUN_00053e74 @ 0x00053e74
 *   ble_rng_seed_from_uptime                 <= FUN_00055bf8 @ 0x00055bf8
 *   ble_rng_get_random_bytes                 <= FUN_00055c64 @ 0x00055c64
 *   tc_hmac_prng_init                        <= FUN_00080652 @ 0x00080652
 * address symbols (name @ address):
 *   rodata_88148                             @ 0x00088148
 *   rodata_f3966                             @ 0x000f3966
 *   g_hmac_prng_ctx                          @ 0x20006000
 */
/* Reconstructed FUN_00055c64 @ 0x55c64  (parity: 300/300 trials, PROVEN) */

extern int FUN_0004d944(int,int,void*,int);
extern int bt_hci_le_rand(void*,int);
extern int ble_rng_seed_from_uptime(void);
extern int tc_hmac_prng_init(int,void*,int);

int ble_rng_get_random_bytes(void)
{
    unsigned char buf[24];
    int iVar1 = bt_hci_le_rand(buf, 8);
    if (iVar1 == 0) {
        iVar1 = tc_hmac_prng_init(((unsigned long)&g_hmac_prng_ctx) /*=0x20006000*/, buf, 8);
        if (iVar1 == 0) {
            struct { int f0; int f4; } s;
            s.f0 = 2;
            s.f4 = ((unsigned long)&rodata_f3966) /*=0xf3966*/;
            iVar1 = -5;
            FUN_0004d944(((unsigned long)&rodata_88148) /*=0x88148*/, 0x1040, &s, 0);
        } else {
            iVar1 = ble_rng_seed_from_uptime();
        }
    }
    return iVar1;
}
