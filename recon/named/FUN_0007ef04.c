/* readable reconstruction; identity: FUN_0007ef04 @ 0x0007ef04
 * public-name: FUN_0007ef04
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed FUN_0007ef04 @ 0x7ef04  (parity: 300/300 trials, PROVEN) */

int FUN_0007ef04(int param_1, unsigned char *param_2, int param_3, unsigned char param_4) {
    int bVar1 = (param_1 == 1);
    if (bVar1) param_4 = 3;
    if (bVar1) param_2[1] = (unsigned char)param_1;
    if (bVar1) {
        param_2[4] = (unsigned char)param_1;
        param_2[0] = param_4;
        param_1 = 0;
    }
    if (bVar1) {
        param_2[2] = param_4;
    } else {
        param_1 = 1;
    }
    if (bVar1) param_2[3] = param_4;
    return param_1;
}
