/* readable reconstruction; identity: FUN_00086588 @ 0x00086588
 * public-name: FUN_00086588
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed FUN_00086588 @ 0x86588  (parity: 300/300 trials, PROVEN) */

extern int FUN_00074a54(int *, unsigned int, unsigned int, unsigned int);

void FUN_00086588(unsigned char *param_1, unsigned int unused_r1,
                  unsigned int unused_r2, unsigned int r3) {
  (void)unused_r1;
  (void)unused_r2;
  if (param_1 != 0) {
    (void)FUN_00074a54((int *)(param_1 + 0xe0), 0, 0, r3);
  }
}
