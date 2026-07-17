/* readable reconstruction; identity: FUN_000778f4 @ 0x000778f4
 * public-name: _sbrk_r
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   sbrk_impl                                <= FUN_00051074 @ 0x00051074
 *   _sbrk_r                                  <= FUN_000778f4 @ 0x000778f4
 * address symbols (name @ address):
 *   g_errno                                  @ 0x2000cc24
 */
/* Reconstructed FUN_000778f4 @ 0x778f4  (parity: 300/300 trials, PROVEN) */

extern int sbrk_impl(unsigned int);
void _sbrk_r(int *param_1,unsigned int param_2)
{
  *(volatile int *)0x2000cc24UL = 0;
  int iVar2 = sbrk_impl(param_2);
  if (iVar2 == -1) {
    int v = *(volatile int *)0x2000cc24UL;
    if (v != 0) {
      *(volatile int *)param_1 = v;
    }
  }
}
