/* readable reconstruction; identity: FUN_000816a2 @ 0x000816a2
 * public-name: atomic_get_word
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   atomic_get_word                          <= FUN_000816a2 @ 0x000816a2
 */
/* Reconstructed FUN_000816a2 @ 0x816a2  (parity: 300/300 trials, PROVEN) */

unsigned long atomic_get_word(const unsigned long*param_1) {
    return *param_1;
}
