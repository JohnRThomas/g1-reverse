/* readable reconstruction; identity: FUN_00085046 @ 0x00085046
 * public-name: cjson_add_item_to_object_thunk
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cjson_add_item_to_object                 <= FUN_0006466c @ 0x0006466c
 *   cjson_add_item_to_object_thunk           <= FUN_00085046 @ 0x00085046
 */
/* Reconstructed FUN_00085046 @ 0x85046  (parity: 300/300 trials, PROVEN) */

extern void cjson_add_item_to_object(unsigned int, unsigned int, unsigned int, unsigned int);
void cjson_add_item_to_object_thunk(unsigned int a, unsigned int b, unsigned int c, unsigned int unused)
{
    (void)unused;
    cjson_add_item_to_object(a, b, c, 0);
}
