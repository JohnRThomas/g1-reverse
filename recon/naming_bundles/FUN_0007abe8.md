### FUN_0007abe8  @ 0x0007abe8  (size=10)

callers (2): cc_mbedtls_entropy_func, cc_mbedtls_sha256
callees (1): mbedtls_zeroize_internal

```c
/* readable reconstruction; identity: FUN_0007abe8 @ 0x0007abe8
 * public-name: FUN_0007abe8
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   mbedtls_zeroize_internal                 <= FUN_000797f4 @ 0x000797f4
 */
/* Reconstructed FUN_0007abe8 @ 0x7abe8  (parity: 300/300 trials, PROVEN) */

extern void mbedtls_zeroize_internal(int a0, int a1);
void FUN_0007abe8(int param_1)
{
  if (param_1 != 0) {
    mbedtls_zeroize_internal(param_1, 0xf4);
  }
}
```