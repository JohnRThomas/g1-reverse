/* readable reconstruction; identity: FUN_00082ff6 @ 0x00082ff6
 * public-name: atomic_test_bit
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed atomic_test_bit @ 0x82ff6  (CFG-directed candidate) */
typedef long atomic_t;
_Bool atomic_test_bit(const atomic_t *target, int bit)
{
    atomic_t value = __atomic_load_n(target, __ATOMIC_SEQ_CST);
    return (value >> bit) & 1;
}
