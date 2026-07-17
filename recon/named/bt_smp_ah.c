/* readable reconstruction; identity: FUN_00080ca0 @ 0x00080ca0
 * public-name: bt_smp_ah
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_smp_ah                                <= FUN_00080ca0 @ 0x00080ca0
 *   bt_encrypt_le                            <= FUN_00081326 @ 0x00081326
 *   memcmp                                   <= FUN_00086be4 @ 0x00086be4
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 */
/* Reconstructed FUN_00080ca0 @ 0x80ca0  (parity: 300/300 trials, PROVEN) */

extern void memset_bytes(void *a, int b, int c);
extern int bt_encrypt_le(int a, void *b);
extern int memcmp(int a, void *b, int c);

int bt_smp_ah(int param_1, int param_2)
{
    unsigned char decoded[16];
    unsigned char key[3];
    int iVar2;

    decoded[0] = *(volatile unsigned char *)(param_2 + 3);
    decoded[1] = *(volatile unsigned char *)(param_2 + 4);
    decoded[2] = *(volatile unsigned char *)(param_2 + 5);
    memset_bytes(decoded + 3, 0, 13);
    iVar2 = bt_encrypt_le(param_1, decoded);
    if (iVar2 == 0) {
        key[0] = decoded[0];
        key[1] = decoded[1];
        key[2] = decoded[2];
        iVar2 = memcmp(param_2, key, 3);
        return iVar2 == 0;
    }
    return 0;
}
