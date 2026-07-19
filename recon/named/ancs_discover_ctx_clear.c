/* readable reconstruction; identity: FUN_0007f8c6 @ 0x0007f8c6
 * public-name: ancs_discover_ctx_clear
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ancs_discover_ctx_clear                  <= FUN_0007f8c6 @ 0x0007f8c6
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 */
/* Reconstructed FUN_0007f8c6 @ 0x7f8c6  (parity: 300/300 trials, PROVEN) */

extern void memset_bytes(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);

unsigned int ancs_discover_ctx_clear(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned int uVar1;
    if (param_1 == 0) {
        uVar1 = 0xffffffea;
    } else {
        memset_bytes(param_1, 0, 0x2c, param_4, param_4);
        uVar1 = 0;
    }
    return uVar1;
}
