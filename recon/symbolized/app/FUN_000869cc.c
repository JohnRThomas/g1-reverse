#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000869cc @ 0x000869cc
 * public-name: FUN_000869cc
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Double absolute-value helper FUN_000869cc @ 0x869cc. */
double FUN_000869cc(double x){union{double d; unsigned long long u;}v={x};v.u&=0x7fffffffffffffffull;return v.d;}
