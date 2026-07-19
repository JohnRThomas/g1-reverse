/* readable reconstruction; identity: FUN_0007ca4e @ 0x0007ca4e
 * public-name: read_volatile_u32_a
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   read_volatile_u32_a                      <= FUN_0007ca4e @ 0x0007ca4e
 */
/* Reconstructed FUN_0007ca4e @ 0x7ca4e  (parity: 300/300 trials, PROVEN) */

unsigned int read_volatile_u32_a(volatile unsigned int *p)
{
    return *p;
}
