/* readable reconstruction; identity: FUN_00016568 @ 0x00016568
 * public-name: get_device_type
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_type                          <= FUN_00016568 @ 0x00016568
 * address symbols (name @ address):
 *   device_info                              @ 0x200069fc
 */
/* Reconstructed FUN_00016568 @ 0x16568  (parity: 300/300 trials, PROVEN) */

unsigned char get_device_type(void)
{
  return *(volatile unsigned char *)(*(volatile unsigned int *)0x200069fcUL);
}
