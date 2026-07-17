/* readable reconstruction; identity: FUN_00084f2e @ 0x00084f2e
 * public-name: sllist_insert_after
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   sllist_insert_after                      <= FUN_00084f2e @ 0x00084f2e
 */
/* Reconstructed FUN_00084f2e @ 0x84f2e  (parity: 300/300 trials, PROVEN) */

int sllist_insert_after(int *param_1, int *param_2)
{
    if (param_2 != 0) {
        if (param_1 == 0) {
            return 0;
        }
        if (param_2 != param_1) {
            if (param_1[2] == 0) {
                param_1[2] = (int)param_2;
                param_2[0] = 0;
                param_2[1] = (int)param_2;
            } else {
                int *puVar1 = *(int**)(param_1[2] + 4);
                if (puVar1 != 0) {
                    puVar1[0] = (int)param_2;
                    param_2[1] = (int)puVar1;
                    *(int**)(param_1[2] + 4) = param_2;
                }
            }
            return 1;
        }
    }
    return 0;
}
