/* Reconstructed FUN_00087184 @ 0x87184  (parity: 300/300 trials, PROVEN) */

extern int FUN_000875ae(void *param_1);

unsigned int FUN_00087184(void *param_1, void *param_2)
{
  unsigned int uVar1, uVar3, uVar7, uVar10;
  unsigned int *puVar2, *puVar6, *puVar8, *puVar9, *puVar12, *puVar14, *puVar13;
  int iVar4, iVar5, iVar11;

  if (*(int*)((char*)param_1+0x10) < *(int*)((char*)param_2+0x10)) {
    uVar7 = 0;
  } else {
    iVar5 = *(int*)((char*)param_2+0x10) - 1;
    puVar6 = (unsigned int*)((char*)param_1+0x14);
    puVar8 = (unsigned int*)((char*)param_2+0x14);
    puVar9 = puVar8 + iVar5;
    puVar2 = puVar6 + iVar5;
    uVar7 = puVar6[iVar5] / (puVar8[iVar5]+1);
    if (puVar8[iVar5]+1 <= puVar6[iVar5]) {
      uVar10=0; iVar11=0;
      puVar12=puVar8; puVar14=puVar6;
      do {
        puVar13 = puVar12+1;
        uVar1 = uVar7*(*puVar12 & 0xffff) + uVar10;
        uVar3 = uVar7*(*puVar12>>16) + (uVar1>>16);
        uVar10 = uVar3>>16;
        uVar1 = ((*puVar14 & 0xffff) - (uVar1 & 0xffff)) + iVar11;
        iVar4 = (((int)uVar1 >> 16) - (uVar3 & 0xffff)) + (int)(*puVar14 >> 16);
        iVar11 = iVar4>>16;
        *puVar14 = (uVar1 & 0xffff) | (iVar4<<16);
        puVar12 = puVar13;
        puVar14 = puVar14+1;
      } while (puVar13 <= puVar9);
      if (puVar6[iVar5]==0) {
        while ((puVar2 = puVar2-1, puVar6<puVar2 && *puVar2==0)) {
          iVar5 = iVar5-1;
        }
        *(int*)((char*)param_1+0x10) = iVar5;
      }
    }
    iVar11 = FUN_000875ae(param_1);
    if (-1 < iVar11) {
      iVar11=0;
      puVar2 = puVar6;
      do {
        puVar12 = puVar8+1;
        uVar10 = ((*puVar2 & 0xffff) - (*puVar8 & 0xffff)) + iVar11;
        iVar4 = (((int)uVar10>>16) - (int)(*puVar8>>16)) + (int)(*puVar2>>16);
        iVar11 = iVar4>>16;
        *puVar2 = (uVar10 & 0xffff) | (iVar4<<16);
        puVar2 = puVar2+1;
        puVar8 = puVar12;
      } while (puVar12 <= puVar9);
      puVar8 = puVar6+iVar5;
      if (puVar6[iVar5]==0) {
        while((puVar8=puVar8-1, puVar6<puVar8 && *puVar8==0)) {
          iVar5 = iVar5-1;
        }
        *(int*)((char*)param_1+0x10) = iVar5;
      }
      uVar7 = uVar7+1;
    }
  }
  return uVar7;
}

