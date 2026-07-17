/* readable reconstruction; identity: FUN_01039972 @ 0x01039972
 * public-name: FUN_01039972
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01039972 @ 0x1039972  (parity 300 trials PROVEN) */
extern int FUN_01039768(void);
extern unsigned int FUN_010397d2(unsigned int, int);
extern int FUN_0103973c(int, int, int);
extern void FUN_01039752(int, int, int, int);

void FUN_01039972(int param_1, int param_2)
{
  int iVar1;
  int iVar2;
  int uVar3;
  unsigned int uVar4;

  uVar4 = *(unsigned int *)(param_1 + 8);
  iVar1 = FUN_01039768();
  if (0x7fff < uVar4 && iVar1 == 1) {
    return;
  }
  uVar4 = FUN_010397d2(uVar4, iVar1);
  iVar2 = param_1 + (int)(uVar4 * 4);
  iVar1 = *(int *)(iVar2 + 0x10);
  if (iVar1 == 0) {
    *(unsigned int *)(param_1 + 0xc) = *(unsigned int *)(param_1 + 0xc) | (1u << (uVar4 & 0xff));
    *(int *)(iVar2 + 0x10) = param_2;
    FUN_01039752(param_1, param_2, 2, param_2);
    uVar3 = 3;
    iVar1 = param_2;
  } else {
    uVar3 = FUN_0103973c(param_1, iVar1, 2);
    FUN_01039752(param_1, param_2, 2, uVar3);
    FUN_01039752(param_1, param_2, 3, iVar1);
    FUN_01039752(param_1, uVar3, 3, param_2);
    uVar3 = 2;
  }
  FUN_01039752(param_1, iVar1, uVar3, param_2);
  return;
}
