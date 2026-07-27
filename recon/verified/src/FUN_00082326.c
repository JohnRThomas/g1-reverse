/* Reconstructed FUN_00082326 @ 0x82326  (parity: 300/300 trials, PROVEN) */

extern void FUN_000822ae(unsigned long, unsigned long);
extern void FUN_00081e14(volatile int *, int);
extern void FUN_0005833c(int*);
void FUN_00082326(unsigned int param_1,int *param_2,int param_3)
{
  if (param_3 == 0) {
    FUN_000822ae(param_1, param_2);
  }
  FUN_00081e14(*param_2 + 0x120,1);
  FUN_0005833c(param_2);
  return;
}

