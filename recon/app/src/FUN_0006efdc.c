/* Reconstructed FUN_0006efdc @ 0x6efdc  (parity: 300/300 trials, PROVEN) */
extern void FUN_00068908(int,int,int,...);
#define VI(a) (*(volatile int*)(a))
void FUN_0006efdc(int param_1,int *param_2,int param_3,int param_4){
  unsigned int uVar4,uVar5,uVar6; int iVar2,iVar3,iVar7; unsigned char bVar1;
  volatile int *p2=(volatile int*)param_2;
  (void)param_3;
  uVar5 = VI(param_1+0x20);
  uVar4 = uVar5 + 5;
  iVar2 = p2[0];
  if ((int)uVar4 < 0x21) {
    VI(param_1+0x20) = uVar4;
    VI(param_1+0x1c) = VI(param_1+0x1c) | (iVar2 << (uVar5 & 0xff));
    uVar5 = uVar5 + 10;
    iVar2 = p2[1];
    if ((int)uVar5 < 0x21) goto LAB_effe;
LAB_f0f2:
    FUN_00068908(param_1,iVar2,5);
    uVar5 = VI(param_1+0x20);
    uVar4 = uVar5 + 1;
    iVar2 = p2[2] >> 1;
    if (0x20 < (int)uVar4) goto LAB_f108;
LAB_f014:
    VI(param_1+0x20) = uVar4;
    VI(param_1+0x1c) = VI(param_1+0x1c) | (iVar2 << (uVar5 & 0xff));
  } else {
    FUN_00068908(param_1,iVar2,5);
    uVar4 = VI(param_1+0x20);
    iVar2 = p2[1];
    uVar5 = uVar4 + 5;
    if (0x20 < (int)uVar5) goto LAB_f0f2;
LAB_effe:
    VI(param_1+0x20) = uVar5;
    VI(param_1+0x1c) = VI(param_1+0x1c) | (iVar2 << (uVar4 & 0xff));
    uVar4 = uVar5 + 1;
    iVar2 = p2[2] >> 1;
    if ((int)uVar4 < 0x21) goto LAB_f014;
LAB_f108:
    FUN_00068908(param_1,iVar2,1);
    uVar4 = VI(param_1+0x20);
  }
  iVar7 = p2[4];
  uVar6 = p2[3];
  uVar5 = p2[2] & 1;
  iVar3 = (int)uVar6 >> uVar5;
  if (iVar2 == 0) {
    if (uVar5 == 0) uVar6 = (unsigned int)*(unsigned char*)((int)param_2+0x19) + (p2[5]+1)*2;
    else uVar6 = uVar6 & 1;
    uVar5 = uVar4 + 1;
    iVar7 = 0x002477f4 * uVar6 + iVar7;
    if ((int)uVar5 < 0x21) {
      VI(param_1+0x20) = uVar5;
      VI(param_1+0x1c) = VI(param_1+0x1c) | (iVar3 << (uVar4 & 0xff));
    } else { FUN_00068908(param_1,iVar3,1); uVar5 = VI(param_1+0x20); }
    uVar6 = uVar5 + 1;
    bVar1 = *(unsigned char*)((int)param_2+0x18);
    if ((int)uVar6 < 0x21) {
      VI(param_1+0x20) = uVar6;
      VI(param_1+0x1c) = VI(param_1+0x1c) | ((unsigned int)bVar1 << (uVar5 & 0xff));
    } else { FUN_00068908(param_1,(unsigned int)bVar1,1); uVar6 = VI(param_1+0x20); }
    iVar2 = uVar6 + 0x19;
    if (0x20 < iVar2) { FUN_00068908(param_1,iVar7,0x19,param_4); return; }
    goto LAB_f0ac;
  }
  if (uVar5 == 0) {
    if ((int)(uVar4+2) < 0x21) goto LAB_f086;
LAB_f116:
    FUN_00068908(param_1,iVar3,2);
    uVar5 = VI(param_1+0x20);
    bVar1 = *(unsigned char*)((int)param_2+0x18);
    uVar6 = uVar5 + 1;
  } else {
    iVar7 = (uVar6 & 1) + (iVar7 + 0x73a600)*2;
    if (0x20 < (int)(uVar4+2)) goto LAB_f116;
LAB_f086:
    uVar5 = uVar4 + 2;
    VI(param_1+0x20) = uVar5;
    uVar6 = uVar4 + 3;
    VI(param_1+0x1c) = VI(param_1+0x1c) | (iVar3 << (uVar4 & 0xff));
    bVar1 = *(unsigned char*)((int)param_2+0x18);
  }
  if ((int)uVar6 < 0x21) {
    VI(param_1+0x20) = uVar6;
    VI(param_1+0x1c) = VI(param_1+0x1c) | ((unsigned int)bVar1 << (uVar5 & 0xff));
  } else { FUN_00068908(param_1,(unsigned int)bVar1,1); uVar6 = VI(param_1+0x20); }
  iVar2 = uVar6 + 0x18;
  if (0x20 < iVar2) { FUN_00068908(param_1,iVar7,0x18,param_4); return; }
LAB_f0ac:
  VI(param_1+0x1c) = VI(param_1+0x1c) | (iVar7 << (uVar6 & 0xff));
  VI(param_1+0x20) = iVar2;
}

