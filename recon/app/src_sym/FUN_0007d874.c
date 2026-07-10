/* Reconstructed FUN_0007d874 @ 0x7d874  (parity: 300/300 trials, PROVEN) */

extern void display_reflash(void*,unsigned int,unsigned int,unsigned int,unsigned int);
extern void FUN_000745c8(void);
unsigned int FUN_0007d874(unsigned int param_1,unsigned int param_2,unsigned int param_3)
{
  unsigned char buf[2];
  buf[0] = 1;
  buf[1] = (unsigned char)param_1;
  display_reflash(buf,2,param_3,1,param_1);
  FUN_000745c8();
  return 0;
}

