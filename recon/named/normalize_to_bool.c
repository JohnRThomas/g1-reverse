/* readable reconstruction; identity: FUN_00081130 @ 0x00081130
 * public-name: normalize_to_bool
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   normalize_to_bool                        <= FUN_00081130 @ 0x00081130
 */
/* Reconstructed FUN_00081130 @ 0x81130  (parity: 300/300 trials, PROVEN) */

int normalize_to_bool(int param_1)
{
    if (param_1 != 0) {
        param_1 = 1;
    }
    return param_1;
}
