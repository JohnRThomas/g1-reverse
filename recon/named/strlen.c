/* named: strlen */
/* Reconstructed strlen @ 0xef12  (parity: 300/300 trials, PROVEN) */

unsigned int strlen(char *param_1) {
  char *p = param_1;
  while (*p != 0) p++;
  return (unsigned int)((p + 1) - 1 - param_1);
}

