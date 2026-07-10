#include "g1_app_symbols.h"
/* named: ble_rng_seed_from_uptime */
/* Reconstructed ble_rng_seed_from_uptime @ 0x55bf8  (parity: 300/300 trials, PROVEN) */
extern int bt_hci_le_rand(void*, int);
extern long long thunk_FUN_00074f68(void);
extern int tc_hmac_prng_reseed(unsigned, void*, int, void*, int);
extern void FUN_0004d944(unsigned, int, void*, int);
int ble_rng_seed_from_uptime(void){
    unsigned char auStack_30[36];
    unsigned local_50, uStack_4c, local_38, local_34;
    int iVar1 = bt_hci_le_rand(auStack_30, 0x20);
    if (iVar1 == 0){
        long long lVar3 = thunk_FUN_00074f68();
        unsigned long long prod = (unsigned long long)(lVar3 * 1000);
        uStack_4c = (unsigned)(prod >> 32);
        local_50 = ((unsigned)prod >> 0xf) | (uStack_4c << 17);
        uStack_4c = uStack_4c >> 0xf;
        int iVar2 = tc_hmac_prng_reseed(((uintptr_t)&g_hmac_prng_ctx) /*=0x20006000*/, auStack_30, 0x20, &local_50, 8);
        if (iVar2 == 0){
            local_34 = "Failed to re-seed PRNG" /*=0xf394f*/;
            local_38 = 2;
            iVar1 = -5;
            FUN_0004d944(((uintptr_t)&tbl_880d8) /*=0x88148*/, 0x1040, &local_38, 0);
        }
    }
    (void)uStack_4c; (void)local_34;
    return iVar1;
}

