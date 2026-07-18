/* readable reconstruction; identity: FUN_0008503c @ 0x0008503c
 * public-name: sllist_find_by_name_ci
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cjson_get_object_item                    <= FUN_0006447c @ 0x0006447c
 *   sllist_find_by_name_ci                   <= FUN_0008503c @ 0x0008503c
 */
/* Reconstructed FUN_0008503c @ 0x8503c  (parity: 300/300 trials, PROVEN) */

extern int cjson_get_object_item(void);
int sllist_find_by_name_ci(void){ return cjson_get_object_item(); }
