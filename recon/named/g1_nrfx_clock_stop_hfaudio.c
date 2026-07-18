/* readable reconstruction; identity: FUN_00083874 @ 0x00083874
 * public-name: g1_nrfx_clock_stop_hfaudio
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   g1_nrfx_clock_stop_checked               <= FUN_00065324 @ 0x00065324
 *   g1_nrfx_clock_stop_hfaudio               <= FUN_00083874 @ 0x00083874
 */
/* Reconstructed FUN_00083874 @ 0x83874; HFAUDIO stop tail veneer. */
extern void g1_nrfx_clock_stop_checked(int domain);
void g1_nrfx_clock_stop_hfaudio(void) { g1_nrfx_clock_stop_checked(3); }
