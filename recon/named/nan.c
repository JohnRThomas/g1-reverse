/* readable reconstruction; identity: FUN_00013e50 @ 0x00013e50
 * public-name: nan
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nan                                      <= FUN_00013e50 @ 0x00013e50
 */
/* Reconstructed FUN_00013e50 @ 0x13e50  (parity: 200/200 trials, PROVEN) */

static double bits64(unsigned long long u){ double d; __builtin_memcpy(&d,&u,8); return d; }
double nan(void){ return bits64(0x7ff8000000000000ULL); }
