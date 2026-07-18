/* readable reconstruction; identity: FUN_000868ee @ 0x000868ee
 * public-name: fabsf
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   fabsf                                    <= FUN_000868ee @ 0x000868ee
 */
/* Float absolute-value helper FUN_000868ee @ 0x868ee. */
float fabsf(float x){union{float f; unsigned u;}v={x};v.u&=0x7fffffffu;return v.f;}
