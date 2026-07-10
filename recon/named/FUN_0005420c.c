/* named: FUN_0005420c */
/* Reconstructed FUN_0005420c @ 0x5420c  (parity: 300/300 trials, PROVEN) */

extern int memcmp(int a,int b,int c,int d);
extern void bt_foreach_bond(int a,int b,void *c);
extern void unpair(int a,int b);
int FUN_0005420c(int param_1,int param_2,int param_3,int param_4)
{
  int iVar1;
  int uVar2;
  char flag = (char)param_1;
  if (param_1 == 0) {
    if (param_2 == 0 || (iVar1 = memcmp(param_2, 0xf2b3a, 7, param_4), iVar1 == 0)) {
      bt_foreach_bond(0, 0x80e81, (void*)&flag);
    } else {
      unpair(0, param_2);
    }
    uVar2 = 0;
  } else {
    uVar2 = 0xffffffea;
  }
  return uVar2;
}

