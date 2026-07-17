/* readable reconstruction; identity: FUN_00086344 @ 0x00086344
 * public-name: cbor_encode_array_indef_start
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cbor_encode_put_type_byte                <= FUN_000861d4 @ 0x000861d4
 *   cbor_encode_array_indef_start            <= FUN_00086344 @ 0x00086344
 */
/* Reconstructed FUN_00086344 @ 0x86344  (parity: 300/300 trials, PROVEN) */

extern void cbor_encode_put_type_byte(unsigned int, unsigned int, unsigned int);
void cbor_encode_array_indef_start(unsigned int param_1)
{
    cbor_encode_put_type_byte(param_1, 4, 0x1f);
}
