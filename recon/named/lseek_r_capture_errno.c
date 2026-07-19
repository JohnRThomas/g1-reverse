/* readable reconstruction; identity: FUN_00078598 @ 0x00078598
 * public-name: lseek_r_capture_errno
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   lseek                                    <= FUN_0004b17c @ 0x0004b17c
 *   lseek_r_capture_errno                    <= FUN_00078598 @ 0x00078598
 * address symbols (name @ address):
 *   g_errno                                  @ 0x2000cc24
 */
/* Reconstructed FUN_00078598 @ 0x78598  (parity: 300/300 trials, PROVEN) */

extern int lseek(unsigned int,unsigned int,unsigned int,unsigned int,unsigned int);
void lseek_r_capture_errno(int *param_1,unsigned int param_2,unsigned int param_3,unsigned int param_4)
{
  int *piVar1;
  int iVar2;
  piVar1 = (int*)0x2000cc24UL;
  *(volatile int*)0x2000cc24UL = 0;
  iVar2 = lseek(param_2,param_3,param_4,param_4,param_4);
  if ((iVar2 == -1) && (*(volatile int*)piVar1 != 0)) {
    *param_1 = *(volatile int*)piVar1;
  }
  return;
}
