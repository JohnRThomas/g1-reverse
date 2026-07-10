/* net-core FUN_01022774 @ 0x1022774  (parity 300 trials PROVEN) */
extern int FUN_01025028(void);

#define DAT_01022868 0x210016f0

unsigned int FUN_01022774(int param_1)
{
  unsigned char bVar1;
  unsigned char bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  unsigned int uVar6;
  int iVar7;
  unsigned int uVar8;
  unsigned int uVar9;
  unsigned int uVar10;
  int bVar11;
  int bVar12;

  iVar3 = DAT_01022868;
  bVar1 = *(unsigned char *)(param_1 * 3 + DAT_01022868 + 0x30);
  if (*(char *)(DAT_01022868 + 0x2a) == '\0') {
    uVar9 = 2;
  } else {
    uVar9 = 0;
  }
  iVar4 = FUN_01025028();
  uVar6 = (unsigned int)bVar1;
  uVar10 = 0x20;
  do {
    uVar8 = uVar6;
    iVar7 = iVar3 + uVar8 * 0x20;
    iVar5 = *(int *)(iVar7 + 0xd8);
    uVar6 = (iVar5 - iVar4) & 0xffffff;
    if ((((*(int *)(iVar7 + 0xe0) + iVar5) - iVar4) & 0xffffffU) < 0x800001) {
      bVar12 = uVar6 <= uVar9;
      bVar11 = uVar9 == uVar6;
      if (!bVar12 || bVar11) {
        bVar12 = 0x7fffff < uVar6;
        bVar11 = uVar6 == 0x800000;
      }
      uVar6 = uVar8;
      if (!bVar12 || bVar11) break;
    }
    uVar6 = (unsigned int)*(unsigned char *)(iVar3 + (param_1 * 0x20 + uVar8) * 2 + 0x51);
    uVar10 = uVar8;
  } while (uVar6 != 0x20);
  if (uVar10 == 0x20) {
    return uVar6;
  }
  iVar4 = param_1 * 0x20;
  iVar5 = param_1 * 3 + iVar3;
  bVar1 = *(unsigned char *)(iVar5 + 0x30);
  *(unsigned char *)(iVar5 + 0x30) = *(unsigned char *)(iVar3 + (uVar10 + param_1 * 0x20) * 2 + 0x51);
  uVar9 = (unsigned int)bVar1;
  do {
    uVar6 = uVar9;
    iVar5 = iVar3 + (iVar4 + uVar6) * 2;
    uVar9 = (unsigned int)*(unsigned char *)(iVar5 + 0x51);
    *(unsigned char *)(iVar5 + 0x50) = 4;
  } while (uVar10 != uVar6);
  iVar5 = param_1 * 3 + iVar3;
  bVar2 = *(unsigned char *)(iVar5 + 0x32);
  if (bVar2 == 0x20) {
    *(unsigned char *)(iVar5 + 0x31) = bVar1;
  } else {
    *(unsigned char *)(iVar3 + ((unsigned int)bVar2 + iVar4) * 2 + 0x51) = bVar1;
  }
  *(unsigned char *)(iVar3 + (uVar6 + iVar4) * 2 + 0x51) = 0x20;
  *(char *)(iVar3 + param_1 * 3 + 0x32) = (char)uVar6;
  return uVar9;
}

