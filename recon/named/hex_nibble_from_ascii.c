/* readable reconstruction; identity: FUN_00087340 @ 0x00087340
 * public-name: hex_nibble_from_ascii
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   hex_nibble_from_ascii                    <= FUN_00087340 @ 0x00087340
 */
/* Reconstructed FUN_00087340 @ 0x87340  (parity: 300/300 trials, PROVEN) */

char hex_nibble_from_ascii(int param_1)
{
    char cVar1 = (char)param_1;
    if ((unsigned int)(param_1 - 0x30) < 10) {
        cVar1 = cVar1 - 0x20;
    } else if ((unsigned int)(param_1 - 0x61) < 6) {
        cVar1 = cVar1 - 0x47;
    } else if ((unsigned int)(param_1 - 0x41) < 6) {
        cVar1 = cVar1 - 0x27;
    } else {
        return 0;
    }
    return cVar1;
}
