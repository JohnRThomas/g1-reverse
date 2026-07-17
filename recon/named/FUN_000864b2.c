/* readable reconstruction; identity: FUN_000864b2 @ 0x000864b2
 * public-name: FUN_000864b2
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed FUN_000864b2 @ 0x864b2  (parity: 300/300 trials, PROVEN) */

extern unsigned int FUN_00074060(void);
unsigned int FUN_000864b2(int param_1,int param_2)
{
  if (*(signed char *)(param_1 + 0xe) != param_2) {
    return FUN_00074060();
  }
  return 0;
}
