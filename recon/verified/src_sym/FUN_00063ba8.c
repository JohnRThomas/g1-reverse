/* Reconstructed FUN_00063ba8 @ 0x63ba8  (parity: 300/300 trials, PROVEN) */

unsigned int FUN_00063ba8(int param_1)
{
  int i = 0;
  while (1) {
    if (*(volatile int *)(0x2000b308UL + i*4) != 0) {
      return 0;
    }
    if (!(param_1 > i)) {
      return 1;
    }
    i = i + 1;
  }
}

