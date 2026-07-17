/* readable reconstruction; identity: FUN_010106dc @ 0x010106dc
 * public-name: FUN_010106dc
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_lookup_table_desc                  @ 0x21000f14
 */
/* net-core FUN_010106dc @ 0x10106dc  (parity 300 trials PROVEN) */
#define P_01010778 0x21000f14

int FUN_010106dc(unsigned int param_1, unsigned int param_2, unsigned char *param_3)
{
  signed char cVar1;
  unsigned int uVar3, uVar4, uVar5, uVar7, uVar8;
  int iVar6, iVar9;

  cVar1 = *(signed char *)P_01010778;
  *param_3 = 0;
  if (cVar1 == 0) {
    return 0;
  }
  iVar9 = *(int *)(P_01010778 + 4);
  uVar4 = (unsigned int)(unsigned char)(cVar1 - 1);
  uVar7 = 0;
  for (;;) {
    uVar8 = uVar4;
    iVar6 = (int)(uVar7 + uVar8) >> 1;
    uVar3 = ((uVar7 + uVar8) * 0x800000u) >> 0x18;
    if ((int)(uVar8 - uVar7) < 2) break;
    uVar5 = *(unsigned int *)(iVar9 + iVar6 * 8 + 4);
    uVar4 = uVar3;
    if (uVar5 <= param_2 &&
        (unsigned int)(param_1 <= *(unsigned int *)(iVar9 + iVar6 * 8) ? 1 : 0) <= uVar5 - param_2) {
      uVar4 = uVar8;
      uVar7 = uVar3;
    }
  }
  uVar3 = *(unsigned int *)(iVar9 + uVar7 * 8);
  uVar4 = *(unsigned int *)(iVar9 + uVar7 * 8 + 4);
  if (uVar4 == param_2 && uVar3 == param_1) {
    *param_3 = (unsigned char)uVar7;
    return 1;
  }
  if (param_2 <= uVar4 &&
      (unsigned int)(uVar3 <= param_1 ? 1 : 0) <= param_2 - uVar4) {
    *param_3 = (unsigned char)uVar7;
    return 0;
  }
  uVar7 = *(unsigned int *)(iVar9 + uVar8 * 8);
  uVar4 = *(unsigned int *)(iVar9 + uVar8 * 8 + 4);
  if (uVar4 == param_2 && uVar7 == param_1) {
    *param_3 = (unsigned char)uVar8;
    return 1;
  }
  if (uVar4 < param_2 || param_2 - uVar4 < (unsigned int)(uVar7 <= param_1 ? 1 : 0)) {
    uVar8 = uVar8 + 1;
  }
  *param_3 = (unsigned char)uVar8;
  return 0;
}
