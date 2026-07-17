/* readable reconstruction; identity: FUN_0007de54 @ 0x0007de54
 * public-name: FUN_0007de54
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   chunk_set                                <= FUN_0007de02 @ 0x0007de02
 */
/* Reconstructed FUN_0007de54 @ 0x7de54  (parity: 300/300 trials, PROVEN) */

extern void chunk_set(unsigned int, unsigned int, unsigned int, unsigned int);
void FUN_0007de54(unsigned int param_1, unsigned int param_2, int param_3)
{
    chunk_set(param_1, param_2, 1, (unsigned int)(param_3 << 1));
}
