/* readable reconstruction; identity: FUN_0007d1d6 @ 0x0007d1d6
 * public-name: errno_wrapped_tick_call
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   store_dashboard_startup_mode_defaults    <= FUN_00016574 @ 0x00016574
 *   rate_limited_elapsed_seconds_tick        <= FUN_0004a46c @ 0x0004a46c
 *   errno_wrapped_tick_call                  <= FUN_0007d1d6 @ 0x0007d1d6
 */
/* Reconstructed FUN_0007d1d6 @ 0x7d1d6  (parity: 300/300 trials, PROVEN) */

extern void rate_limited_elapsed_seconds_tick(int *, int, int);
extern void store_dashboard_startup_mode_defaults(unsigned int);

void errno_wrapped_tick_call(int param_1, unsigned int param_2)
{
  int iVar1;
  char *base = (char*)param_1;
  int *p1 = *(int **)(base + 0xff4);

  iVar1 = *(int*)((char*)p1 + 0x164);
  if (iVar1 != 0) {
    **(int **)(base + 0xfec) = iVar1;
  }
  rate_limited_elapsed_seconds_tick((int *)param_2, 0, 0);
  p1 = *(int **)(base + 0xff4);
  if (*(int*)((char*)p1 + 0x164) != 0) {
    *(unsigned int*)((char*)p1 + 0x164) = **(unsigned int **)(base + 0xfec);
  }
  store_dashboard_startup_mode_defaults(**(unsigned int **)(base + 0xfec));
  return;
}
