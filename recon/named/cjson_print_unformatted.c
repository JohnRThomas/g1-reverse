/* readable reconstruction; identity: FUN_0008501a @ 0x0008501a
 * public-name: cjson_print_unformatted
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cjson_print                              <= FUN_00064a88 @ 0x00064a88
 *   cjson_print_unformatted                  <= FUN_0008501a @ 0x0008501a
 */
/* Reconstructed FUN_0008501a @ 0x8501a  (parity: 300/300 trials, PROVEN) */

extern void cjson_print(unsigned int, unsigned int);
void cjson_print_unformatted(unsigned int param_1)
{
    cjson_print(param_1, 0);
}
