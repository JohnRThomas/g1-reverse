/* readable reconstruction; identity: FUN_00080a82 @ 0x00080a82
 * public-name: img_mgmt_my_version
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   img_mgmt_read_info                       <= FUN_00052038 @ 0x00052038
 *   img_mgmt_my_version                      <= FUN_00080a82 @ 0x00080a82
 */
/* Reconstructed FUN_00080a82 @ 0x80a82  (parity: 300/300 trials, PROVEN) */

extern void img_mgmt_read_info(unsigned int, unsigned int,
                         unsigned int, unsigned int);

void img_mgmt_my_version(unsigned int param_1)
{
  img_mgmt_read_info(0, param_1, 0, 0);
}
