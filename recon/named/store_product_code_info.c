/* readable reconstruction; identity: FUN_000232dc @ 0x000232dc
 * public-name: store_product_code_info
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   store_product_code_info                  <= FUN_000232dc @ 0x000232dc
 *   snprintf                                 <= FUN_00077914 @ 0x00077914
 * address symbols (name @ address):
 *   rodata_a8c37                             @ 0x000a8c37
 *   g_product_code_buf                       @ 0x20002fe3
 */
/* Reconstructed FUN_000232dc @ 0x232dc  (parity: 300/300 trials, PROVEN) */

extern unsigned int snprintf(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
unsigned int store_product_code_info(unsigned int param_1,unsigned int param_2,unsigned int param_3,unsigned int param_4)
{
  snprintf(0x20002fe3UL, 0x10, 0xa8c37UL, param_1, param_4);
  return 0;
}
