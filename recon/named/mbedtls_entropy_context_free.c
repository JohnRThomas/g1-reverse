/* readable reconstruction; identity: FUN_0007abe8 @ 0x0007abe8
 * public-name: mbedtls_entropy_context_free
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   mbedtls_zeroize_internal                 <= FUN_000797f4 @ 0x000797f4
 *   mbedtls_entropy_context_free             <= FUN_0007abe8 @ 0x0007abe8
 */
/* Reconstructed FUN_0007abe8 @ 0x7abe8  (parity: 300/300 trials, PROVEN) */

extern void mbedtls_zeroize_internal(int a0, int a1);
void mbedtls_entropy_context_free(int param_1)
{
  if (param_1 != 0) {
    mbedtls_zeroize_internal(param_1, 0xf4);
  }
}
