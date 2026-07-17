/* readable reconstruction; identity: FUN_000868ee @ 0x000868ee
 * public-name: FUN_000868ee
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Float absolute-value helper FUN_000868ee @ 0x868ee. */
float FUN_000868ee(float x){union{float f; unsigned u;}v={x};v.u&=0x7fffffffu;return v.f;}
