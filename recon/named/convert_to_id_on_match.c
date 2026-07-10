/* named: convert_to_id_on_match */
/* Reconstructed convert_to_id_on_match @ 0x831e2  (parity: 300/300 trials, PROVEN) */

extern int memcmp(int a, int b, int c);
extern void FUN_00083062(int a, int b);
void convert_to_id_on_match(int param_1, int *param_2)
{
  int iVar1;
  iVar1 = memcmp(param_1 + 0x90, *param_2, 7);
  if (iVar1 == 0) {
    FUN_00083062(param_1 + 0x90, param_2[1]);
  }
}

