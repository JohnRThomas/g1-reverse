/* named: att_cfm_sent */
/* Reconstructed att_cfm_sent @ 0x82346  (parity: 300/300 trials, PROVEN) */

extern void FUN_000822ae(void);
extern void atomic_clear_bit_0(int,unsigned int);
extern void FUN_0005833c(int*);
void att_cfm_sent(unsigned int param_1,int *param_2,int param_3)
{
  if (param_3 == 0) {
    FUN_000822ae();
  }
  atomic_clear_bit_0(*param_2 + 0x120,0);
  FUN_0005833c(param_2);
  return;
}

