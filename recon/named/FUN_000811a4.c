/* readable reconstruction; identity: FUN_000811a4 @ 0x000811a4
 * public-name: FUN_000811a4
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   atomic_and_1                             <= FUN_00081180 @ 0x00081180
 */
/* Reconstructed FUN_000811a4 @ 0x811a4  (parity: 300/300 trials, PROVEN) */

extern void atomic_and_1(unsigned int*, unsigned int);
void FUN_000811a4(unsigned int *param_1, unsigned int param_2, int param_3)
{
    unsigned int uVar1 = 1u << (param_2 & 0xff);
    if (param_3 == 0) {
        atomic_and_1(param_1, ~uVar1);
        return;
    }
    (void)__atomic_fetch_or(param_1, uVar1, __ATOMIC_SEQ_CST);
}
