/* readable reconstruction; identity: FUN_00086a06 @ 0x00086a06
 * public-name: check_is_release_mode
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   strtol                                   <= FUN_00077b24 @ 0x00077b24
 *   check_is_release_mode                    <= FUN_00086a06 @ 0x00086a06
 */
/* Reconstructed FUN_00086a06 @ 0x86a06  (parity: 300/300 trials, PROVEN) */
extern long int strtol(const char * restrict,  char ** restrict,  int);
unsigned int check_is_release_mode(int param_1) {
  return strtol(param_1, 0, 0xa);
}
