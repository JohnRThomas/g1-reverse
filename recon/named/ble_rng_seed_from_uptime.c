/* readable reconstruction; identity: FUN_00055bf8 @ 0x00055bf8
 * public-name: ble_rng_seed_from_uptime
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_log_msg_runtime_create                 <= FUN_0004d944 @ 0x0004d944
 *   bt_hci_le_rand                           <= FUN_00053e74 @ 0x00053e74
 *   ble_rng_seed_from_uptime                 <= FUN_00055bf8 @ 0x00055bf8
 *   tc_hmac_prng_reseed                      <= FUN_00080692 @ 0x00080692
 * address symbols (name @ address):
 *   rodata_88148                             @ 0x00088148
 *   rodata_f394f                             @ 0x000f394f
 *   g_hmac_prng_ctx                          @ 0x20006000
 */
/* Reconstructed FUN_00055bf8 @ 0x55bf8  (parity: 300/300 trials, PROVEN) */
extern int bt_hci_le_rand(void*, int);
extern long long thunk_FUN_00074f68(void);
extern int tc_hmac_prng_reseed(unsigned, void*, int, void*, int);
extern void z_log_msg_runtime_create(unsigned, int, void*, int);
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
        int iVar2 = tc_hmac_prng_reseed(0x20006000, auStack_30, 0x20, &local_50, 8);
        if (iVar2 == 0){
            local_34 = 0xf394f;
            local_38 = 2;
            iVar1 = -5;
            z_log_msg_runtime_create(0x88148, 0x1040, &local_38, 0);
        }
    }
    (void)uStack_4c; (void)local_34;
    return iVar1;
}
