/* readable reconstruction; identity: FUN_00082932 @ 0x00082932
 * public-name: FUN_00082932
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 */
/* Reconstructed FUN_00082932 @ 0x82932  (parity: 300/300 trials, PROVEN) */

typedef unsigned int uint;
extern void memcpy(unsigned int a, unsigned int b, unsigned int c, int d, int e);

uint FUN_00082932(unsigned int param_1, uint param_2, uint param_3, int param_4, unsigned short param_5)
{
    uint uVar1;
    if (param_5 < param_3) {
        uVar1 = 0xfffffff9;
    } else {
        uVar1 = param_5 - param_3;
        if ((int)param_2 <= (int)uVar1) {
            uVar1 = param_2;
        }
        uVar1 = uVar1 & 0xffff;
        memcpy(param_1, param_4 + param_3, uVar1, param_4, param_4);
    }
    return uVar1;
}
