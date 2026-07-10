/* named: settings_save_one */
/* globals referenced:
//   0x20003868  g_settings_lock              
//   0x2000a104  g_settings_stores            
*/
/* Reconstructed settings_save_one @ 0x4e434  (parity: 300/300 trials, PROVEN) */

extern void k_mutex_lock(unsigned int, unsigned int, int, int, unsigned int);
extern void k_mutex_unlock(unsigned int);
typedef void (*fnptr)(int *, void *);

unsigned int settings_save_one(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
  int *piVar1;
  unsigned int local_14;
  unsigned int uStack_10;
  unsigned int local_c;
  fnptr fp;
  local_14 = param_1;
  uStack_10 = param_2;
  local_c = param_3;
  k_mutex_lock(0x20003868, param_2, -1, -1, param_1);
  for (piVar1 = *(int * volatile *)0x2000a104UL; piVar1 != 0; piVar1 = *(int **)piVar1) {
    fp = *(fnptr *)(piVar1[1]);
    fp(piVar1, &local_14);
  }
  k_mutex_unlock(0x20003868);
  return 0;
}

