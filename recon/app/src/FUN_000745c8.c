/* Reconstructed FUN_000745c8 @ 0x745c8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_000501d4(int,...);
extern int FUN_00072040(int,...);
extern int FUN_0007205c(int,...);
extern int FUN_00072078(int,...);
extern int FUN_000737d8(int,...);
extern int FUN_00073cdc(int,...);
extern int FUN_0007e2ec(int,...);
extern int FUN_0007e2fa(int,...);
void FUN_000745c8(void)
{
  int iVar2 = FUN_00072040(0x2000b490);
  int iVar3 = 0x2000b448;
  if (iVar2 == 0) {
    FUN_0007e2fa(0x99cbd,0xf0920,0xf08c7,0x72);
    FUN_0007e2fa(0xf0935,0x2000b490);
    FUN_0007e2ec(0xf08c7,0x72);
    return;
  }
  FUN_00072078(0x2000b490);
  int *puVar9 = (int*)(iVar3+0x1c);
  *(unsigned char*)(*(int*)(iVar3+8)+0xd) &= 0x7f;
  FUN_00073cdc((int)puVar9);
  int *piVar8 = *(int**)(iVar3+8);
  *(unsigned char*)((int)piVar8+0xd) |= 0x80;
  if (piVar8 == (int*)0x20006720) {
    FUN_0007e2fa(0x99cbd,0xf84d6,0xf82f4,0xc1);
    FUN_0007e2ec(0xf82f4,0xc1);
    return;
  }
  int *puVar6 = *(int**)(iVar3+0x1c);
  int *puVar5 = *(int**)(iVar3+0x20);
  if (puVar6 == puVar9) puVar6 = 0;
  for (; puVar6 != 0; puVar6 = (int*)*puVar6) {
    if ((*(signed char*)((int)piVar8+0xe) != *(signed char*)((int)puVar6+0xe)) &&
        (*(signed char*)((int)piVar8+0xe) < *(signed char*)((int)puVar6+0xe))) {
      int *pv = (int*)puVar6[1];
      *piVar8 = (int)puVar6; piVar8[1]=(int)pv; *pv=(int)piVar8; puVar6[1]=(int)piVar8;
      goto L;
    }
    if (puVar6 == puVar5) break;
  }
  *piVar8 = (int)puVar9; piVar8[1]=(int)puVar5; *puVar5=(int)piVar8; *(int**)(iVar3+0x20)=piVar8;
L:
  FUN_000737d8(1);
  int r = FUN_0007205c(0x2000b490);
  if (r != 0) { FUN_000501d4(0); return; }
  FUN_0007e2fa(0x99cbd,0xf08f4,0xf08c7,0x111);
  FUN_0007e2fa(0xf090b,0x2000b490);
  FUN_0007e2ec(0xf08c7,0x111);
}

