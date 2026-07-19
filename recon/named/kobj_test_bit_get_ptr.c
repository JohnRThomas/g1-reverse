/* readable reconstruction; identity: FUN_0005caa4 @ 0x0005caa4
 * public-name: kobj_test_bit_get_ptr
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   kobj_test_bit_get_ptr                    <= FUN_0005caa4 @ 0x0005caa4
 *   atomic_test_bit                          <= FUN_00082ff6 @ 0x00082ff6
 * address symbols (name @ address):
 *   g_misc_kobj_6454                         @ 0x20006454
 */
/* Reconstructed FUN_0005caa4 @ 0x5caa4  (parity: 300/300 trials, PROVEN) */

extern int atomic_test_bit(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);

int kobj_test_bit_get_ptr(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned int base = 0x20006454UL;
    int iVar1 = atomic_test_bit(base, param_1, param_3, base, param_4);
    int iVar2 = (int)(base - 4);
    if (iVar1 == 0) {
        iVar2 = 0;
    }
    return iVar2;
}
