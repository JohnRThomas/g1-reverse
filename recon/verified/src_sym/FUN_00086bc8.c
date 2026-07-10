/* Reconstructed FUN_00086bc8 @ 0x86bc8  (parity: 300/300 trials, PROVEN) */

char * FUN_00086bc8(char *param_1, unsigned int param_2, int param_3)
{
  unsigned char *pcVar1;
  unsigned char *pcVar2;
  unsigned char b2 = (unsigned char)param_2;

  pcVar1 = (unsigned char *)param_1;
  do {
    pcVar2 = pcVar1;
    if (pcVar2 == (unsigned char*)param_1 + param_3) {
      return (char *)0x0;
    }
    pcVar1 = pcVar2 + 1;
  } while (*pcVar2 != b2);
  return (char *)pcVar2;
}

