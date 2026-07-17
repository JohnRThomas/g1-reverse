/* Reconstructed FUN_00083dc8 @ 0x83dc8  (parity: 300/300 trials, PROVEN) */

extern void FUN_00083d60(unsigned int, void *, unsigned int, unsigned int, unsigned int);

void FUN_00083dc8(unsigned int *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned char request[3];

  request[0] = (unsigned char)param_2;
  request[1] = (unsigned char)param_3;
  request[2] = (unsigned char)param_4;
  FUN_00083d60(*(unsigned int *)((unsigned char*)param_1 + 4), request, 3,
                param_4, (unsigned int)param_1);
  return;
}
