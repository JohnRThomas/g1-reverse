/* readable reconstruction; identity: FUN_0005a91c @ 0x0005a91c
 * public-name: gatt_cf_store_all
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_gatt_store_cf                         <= FUN_0005a8bc @ 0x0005a8bc
 *   gatt_cf_store_all                        <= FUN_0005a91c @ 0x0005a91c
 *   bt_addr_le_eq_0                          <= FUN_000826b2 @ 0x000826b2
 *   set_change_aware_no_store                <= FUN_00082b98 @ 0x00082b98
 * address symbols (name @ address):
 *   rodata_f2b3a                             @ 0x000f2b3a
 *   g_bt_gatt_cf_cfg                         @ 0x2000aed4
 */
/* Reconstructed FUN_0005a91c @ 0x5a91c  (parity: 300/300 trials, PROVEN) */

extern int bt_addr_le_eq_0(void *a, unsigned int b);
extern void set_change_aware_no_store(void *a, unsigned int b);
extern void bt_gatt_store_cf(unsigned int a, void *b);

void gatt_cf_store_all(void)
{
    unsigned int uVar1 = 0x000f2b3aUL;
    int iVar4 = 0;
    unsigned char *puVar3 = (unsigned char *)0x2000aed4UL;
    int iVar2;
    do {
        iVar2 = bt_addr_le_eq_0((void*)(puVar3+1), uVar1);
        if (iVar2 == 0) {
            set_change_aware_no_store((void*)puVar3, 0);
            bt_gatt_store_cf(*(volatile unsigned char*)puVar3, (void*)(puVar3+1));
        }
        iVar4 = iVar4 + 1;
        puVar3 = puVar3 + 0x10;
    } while (iVar4 != 3);
}
