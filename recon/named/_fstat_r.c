/* readable reconstruction; identity: FUN_00077e4c @ 0x00077e4c
 * public-name: _fstat_r
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   _fstat_r                                 <= FUN_00077e4c @ 0x00077e4c
 *   _fstat                                   <= FUN_000807e8 @ 0x000807e8
 * address symbols (name @ address):
 *   g_errno                                  @ 0x2000cc24
 */
/* Reconstructed FUN_00077e4c @ 0x77e4c  (parity: 300/300 trials, PROVEN) */

extern int _fstat(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);

void _fstat_r(int *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  volatile int *piVar1;
  int iVar2;

  piVar1 = (volatile int *)0x2000cc24UL;
  *piVar1 = 0;
  iVar2 = _fstat(param_2,param_3,param_3,0,param_4);
  if ((iVar2 == -1) && (*piVar1 != 0)) {
    *param_1 = *piVar1;
  }
  return;
}
