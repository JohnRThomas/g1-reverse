/* named: FUN_00084602 */
/* Reconstructed FUN_00084602 @ 0x84602  (parity: 300/300 trials, PROVEN) */

unsigned FUN_00084602(int *param_1,int param_2,unsigned param_3,unsigned short *param_4){
  unsigned short ip = *(unsigned short*)((int)param_1+0xa);
  unsigned short r4 = *(unsigned short*)((int)param_1+8);
  int r7 = param_1[0];
  unsigned r6 = (unsigned)param_1[1];
  int r5 = (int)(r6*((unsigned)ip-(unsigned)r4)) + r7;
  if((int)param_3 < r7) return 0xffffffea;
  if(param_2 > r5) return 0xffffffea;
  if(param_2 < r7){ ip = r4; goto L8462c; }
  if((int)param_3 <= r5) goto L8463a;
  L8462c: *param_4 = ip; return 0xffffffde;
  L8463a:
  if(r6 != 0) goto L84642;
  *param_4 = r4; return 0;
  L84642: {
    unsigned r1 = (unsigned)(param_2 - r7) + (r6 - 1);
    r1 = r1 / r6;
    unsigned r4n = ((unsigned)r4 + r1) & 0xffff;
    *param_4 = (unsigned short)r4n;
    unsigned short r3h = *(unsigned short*)((int)param_1+8);
    unsigned r4d = r4n - (unsigned)r3h;
    unsigned r3b = (unsigned)param_1[1]*r4d + (unsigned)param_1[0];
    if(r3b <= param_3) return 0;
    return 0xffffffea;
  }
}

