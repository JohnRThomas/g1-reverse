/* readable reconstruction; identity: FUN_00013e50 @ 0x00013e50
 * public-name: dtoa_get_bias_const
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   dtoa_get_bias_const                      <= FUN_00013e50 @ 0x00013e50
 */
/* Reconstructed FUN_00013e50 @ 0x13e50  (parity: 200/200 trials, PROVEN) */

static double bits64(unsigned long long u){ double d; __builtin_memcpy(&d,&u,8); return d; }
double dtoa_get_bias_const(void){ return bits64(0x7ff8000000000000ULL); }
