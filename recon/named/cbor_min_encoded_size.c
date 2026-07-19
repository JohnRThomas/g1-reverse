/* readable reconstruction; identity: FUN_0007158c @ 0x0007158c
 * public-name: cbor_min_encoded_size
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cbor_min_encoded_size                    <= FUN_0007158c @ 0x0007158c
 */
/* Reconstructed FUN_0007158c @ 0x7158c  (parity: 300/300 trials, PROVEN) */

typedef unsigned int uint;

uint cbor_min_encoded_size(char *param_1, uint param_2)
{
    uint uVar1;
    signed char sVar2;
    do {
        uVar1 = param_2;
        if (uVar1 == 0) {
            return 0;
        }
        param_2 = uVar1 - 1;
    } while (*(volatile char*)(param_1 + (uVar1 - 1)) == 0);
    if (uVar1 > 2) {
        if (uVar1 - 2 < 7) {
            sVar2 = *(volatile signed char*)(0x000f7c37UL + (uVar1 - 2));
        } else {
            sVar2 = 0;
        }
        uVar1 = 1 << sVar2;
    }
    return uVar1;
}
