/* named: _fstat */
/* Reconstructed _fstat @ 0x807e8  (parity: 300/300 trials, PROVEN) */

unsigned int _fstat(unsigned int param_1, int param_2)
{
  *(volatile unsigned int *)(param_2 + 4) = 0x2000;
  return 0;
}

