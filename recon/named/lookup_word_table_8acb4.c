/* readable reconstruction; identity: FUN_0004d420 @ 0x0004d420
 * public-name: lookup_word_table_8acb4
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   lookup_word_table_8acb4                  <= FUN_0004d420 @ 0x0004d420
 * address symbols (name @ address):
 *   rodata_8acb4                             @ 0x0008acb4
 */
/* Reconstructed FUN_0004d420 @ 0x4d420  (parity: 300/300 trials, PROVEN) */

unsigned int lookup_word_table_8acb4(int param_1)
{
    return *(volatile unsigned int*)(0x8acb4UL + (unsigned int)param_1 * 4);
}
