/* named: u64_sub */
/* Reconstructed u64_sub @ 0x7d3c2  (parity: 300/300 trials, PROVEN) */

long long u64_sub(unsigned int param_1,int param_2,unsigned int param_3,int param_4)
{
  long long a = ((long long)param_2 << 32) | (unsigned long long)param_1;
  long long b = ((long long)param_4 << 32) | (unsigned long long)param_3;
  return (a >= b) ? (a - b) : (b - a);
}

