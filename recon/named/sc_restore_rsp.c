/* readable reconstruction; identity: FUN_00082bd4 @ 0x00082bd4
 * public-name: sc_restore_rsp
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   find_sc_cfg_59bcc                        <= FUN_00059bcc @ 0x00059bcc
 *   find_cf_cfg                              <= FUN_00059c04 @ 0x00059c04
 *   log_gatt_sc_store_failure                <= FUN_0005a0e8 @ 0x0005a0e8
 *   const_return_one                         <= FUN_0008256e @ 0x0008256e
 *   set_change_aware                         <= FUN_00082bb8 @ 0x00082bb8
 *   sc_restore_rsp                           <= FUN_00082bd4 @ 0x00082bd4
 */
/* Reconstructed FUN_00082bd4 @ 0x82bd4  (parity: 300/300 trials, PROVEN) */

extern unsigned int const_return_one(void);
extern unsigned char* find_cf_cfg(int);
extern void set_change_aware(void *a, int b);
extern void *find_sc_cfg_59bcc(unsigned char a, int b);
extern void log_gatt_sc_store_failure(void *a);

void sc_restore_rsp(int param_1, unsigned int param_2, int param_3, unsigned int param_4)
{
    int iVar1;
    unsigned char *puVar2;

    iVar1 = const_return_one();
    if (iVar1 != 0) {
        void *r = find_cf_cfg(param_1);
        if (r != 0) {
            if ((int)((unsigned int)(*(volatile unsigned char *)((int)r + 8)) << 0x1f) < 0) {
                set_change_aware(r, 1);
            }
        }
    }
    if (param_3 == 0) {
        puVar2 = find_sc_cfg_59bcc(*(volatile unsigned char *)(param_1 + 8), param_1 + 0x90);
        if (puVar2 != 0) {
            *(volatile int *)(puVar2 + 8) = param_3;
            log_gatt_sc_store_failure(puVar2);
            return;
        }
    }
}
