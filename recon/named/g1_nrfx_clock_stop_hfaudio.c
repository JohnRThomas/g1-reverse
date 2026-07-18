/* readable reconstruction; identity: FUN_00083874 @ 0x00083874
 * public-name: g1_nrfx_clock_stop_hfaudio
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nrfx_clock_stop                          <= FUN_00065324 @ 0x00065324
 *   g1_nrfx_clock_stop_hfaudio               <= FUN_00083874 @ 0x00083874
 */
/* Reconstructed FUN_00083874 @ 0x83874; HFAUDIO stop tail veneer. */
extern void nrfx_clock_stop(int domain);
void g1_nrfx_clock_stop_hfaudio(void) { nrfx_clock_stop(3); }
