/* readable reconstruction; identity: FUN_0007f198 @ 0x0007f198
 * public-name: settings_delete
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   settings_save_one                        <= FUN_0004e374 @ 0x0004e374
 *   settings_delete                          <= FUN_0007f198 @ 0x0007f198
 */
/* Reconstructed FUN_0007f198 @ 0x7f198. */
/* Tail wrapper: clear the callee's second and third ABI arguments. */
extern void settings_save_one(unsigned int, unsigned int, unsigned int);

void settings_delete(unsigned int param_1)
{
    settings_save_one(param_1, 0, 0);
}
