/* Reconstructed FUN_00083cde @ 0x83cde  (parity: 300/300 trials, PROVEN) */

extern int FUN_00083eb8(unsigned int *, unsigned int *, unsigned int **, unsigned int, unsigned int *);
extern void FUN_00083ede(unsigned int, unsigned char, unsigned int);

void FUN_00083cde(unsigned int *param_1, unsigned int *param_2, unsigned int param_3, unsigned int param_4)
{
  int iVar1;
  unsigned int *local_c;

  local_c = param_2;
  iVar1 = FUN_00083eb8(param_1,param_2,&local_c,param_4,param_1);
  if (-1 < iVar1) {
    FUN_00083ede(*local_c,*(unsigned char *)(local_c + 1),*param_1);
  }
  return;
}

