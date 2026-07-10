/* named: sllist_insert_after */
/* Reconstructed sllist_insert_after @ 0x84f2e  (parity: 300/300 trials, PROVEN) */

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

