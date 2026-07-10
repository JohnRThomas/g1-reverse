/* named: FUN_00061c40 */
/* globals referenced:
//   0x5002a000  NRF_GPIOTE1_S                
*/
/* Reconstructed FUN_00061c40 @ 0x61c40  (parity: 300/300 trials, PROVEN) */

extern void FUN_0004d944(void*, int, void*, int);

unsigned int FUN_00061c40(int param_1, unsigned int param_2, int param_3)
{
  unsigned int uVar1;
  unsigned int local_18;
  int local_14;

  if (param_3 != 0) {
    local_14 = 0xf60c5;
    local_18 = 2;
    FUN_0004d944((void*)0x881f8UL, 0x1080, &local_18, 0);
  }
  if (param_2 < 0x10 && ((int)((*(unsigned int*)(*(int*)(param_1+4)+4) >> (param_2 & 0xff)) << 0x1f) < 0)) {
    uVar1 = 0;
    *(volatile unsigned int*)(0x5002a000UL + ((param_2 & 0x3f)*4)) = 1;
  } else {
    uVar1 = 0xffffffea;
  }
  return uVar1;
}

