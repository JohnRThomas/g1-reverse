/* readable reconstruction; identity: FUN_0002c30c @ 0x0002c30c
 * public-name: get_message_type_param
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_message_type_param                   <= FUN_0002c30c @ 0x0002c30c
 */
/* Reconstructed FUN_0002c30c @ 0x2c30c  (parity: 300/300 trials, PROVEN) */

unsigned int get_message_type_param(int param_1,unsigned int param_2)
{
  if (param_1 != 0xb) {
    if (param_1 == 0xc) {
      param_2 = 1;
    }
    return param_2;
  }
  return 0x01e13380UL;
}
