/* readable reconstruction; identity: FUN_00085c12 @ 0x00085c12
 * public-name: FUN_00085c12
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed FUN_00085c12 @ 0x85c12  (parity: 300/300 trials, PROVEN) */

int FUN_00085c12(int param_1)
{
    if (param_1 != 0 && *(char *)(param_1 + 0x10) != 0) {
        return *(int *)(param_1 + 0xc) == 0;
    }
    return 1;
}
