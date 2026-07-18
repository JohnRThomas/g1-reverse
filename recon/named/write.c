/* readable reconstruction; identity: FUN_0004b0dc @ 0x0004b0dc
 * public-name: write
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   _check_fd                                <= FUN_0004b01c @ 0x0004b01c
 *   write                                    <= FUN_0004b0dc @ 0x0004b0dc
 *   k_mutex_lock                             <= FUN_000723b8 @ 0x000723b8
 * address symbols (name @ address):
 *   g_posix_fd_table                         @ 0x20002548
 */
/* Reconstructed FUN_0004b0dc @ 0x4b0dc  (parity: 300/300 trials, PROVEN) */

extern long long _check_fd(void);
extern void k_mutex_lock(int a, int b, int c, int d);
extern void thunk_FUN_00072558(int a);
typedef unsigned int (*fnptr4b0dc)(unsigned int, unsigned int, unsigned int);

unsigned int write(int param_1, unsigned int param_2, unsigned int param_3)
{
  long long uVar4;
  int iVar1;
  unsigned int uVar2;
  int iVar3;

  uVar4 = _check_fd();
  iVar1 = 0x20002548;
  if ((int)uVar4 < 0) {
    uVar2 = 0xffffffff;
  } else {
    param_1 = param_1 * 0x28;
    iVar3 = param_1 + 0xc + iVar1;
    k_mutex_lock(iVar3, (int)(uVar4 >> 32), -1, -1);
    unsigned int mid = *(volatile unsigned int*)(iVar1 + param_1 + 4);
    fnptr4b0dc f = *(volatile fnptr4b0dc*)(mid + 4);
    uVar2 = f(*(volatile unsigned int*)(iVar1 + param_1), param_2, param_3);
    thunk_FUN_00072558(iVar3);
  }
  return uVar2;
}
