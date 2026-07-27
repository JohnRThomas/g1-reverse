/* Reconstructed FUN_000365ec @ 0x365ec  (parity: 300/300 trials, PROVEN) */
extern void DEBUG_PRINT(unsigned long, ...);
extern int  FUN_000167a8(void);
extern void FUN_00036558(int,int);
extern int  FUN_00076d6c(int);
extern void FUN_00076d7c(int);
extern void FUN_000777f0(int);
extern int  FUN_0007d1c8(void*);
extern void FUN_00086c04(int,int,int);
extern void FUN_00086c78(void*,int,int);
extern int  FUN_00087036(void*,int,int);
#define VI(a) (*(volatile int*)(a))
#define VB(a) (*(volatile unsigned char*)(a))
typedef int (*fp_t)(int,int,void*,int);

void FUN_000365ec(void){
  int iVar3,iVar5,iVar6,iVar7,iVar10,iVar11,iVar14; int uVar4;
  int puVar2, pcVar12;
  int local_60[3]; short local_54v;
  int local_50[2]; unsigned char auStack_48[8]; short local_42;
  puVar2 = FUN_00076d6c(0x50);
  if (puVar2 == 0) { DEBUG_PRINT(0x000a8d69,0x000a8e27,0x54); return; }
  FUN_00086c78((void*)puVar2,0,0x50);
  iVar3 = FUN_000167a8();
  pcVar12 = VI(iVar3+0x1030);
  uVar4 = FUN_000167a8();
  iVar3 = ((fp_t)pcVar12)(uVar4,0x1c0000,(void*)puVar2,0x50);
  if (iVar3 != 0) { DEBUG_PRINT(0x000a8d7f,0x000a8e27,0x5a); goto END; }
  local_60[0]=VI(puVar2); local_60[1]=VI(puVar2+4); local_60[2]=VI(puVar2+8);
  local_54v=(short)VI(puVar2+0xc);
  iVar3 = FUN_00087036(local_60,0x000a8da5,2);
  if (iVar3 != 0) { DEBUG_PRINT(0x000a8da8); goto END; }
  { int s=puVar2+0xe; int d=0;
    do { local_50[d]=VI(s); local_50[d+1]=VI(s+4); s+=8; d+=2; } while (s != puVar2+0x36); }
  iVar3 = FUN_0007d1c8((void*)((int)&local_60[0]+ ( (int)&local_60[2] - (int)&local_60[0]) +2)); /* uStack_58+2 */
  iVar5 = FUN_0007d1c8(&local_50[1]);
  iVar6 = FUN_0007d1c8(auStack_48);
  if (local_42 == 1) {
    iVar10 = iVar5 + 7;
    VI(0x20009fc4) = 0;
    if (iVar10 < 0) iVar10 = iVar5 + 0xe;
    VI(0x20009fc8) = 0;
    iVar11 = iVar5 + 0x1f;
    if (iVar11 < 0) iVar11 = iVar5 + 0x3e;
    iVar14 = iVar3 + 0x1c0000 + (iVar6 + -1) * (iVar11 >> 5) * 4;
    for (iVar3 = 0; iVar3 < iVar6; iVar3 = iVar3 + 1) {
      VI(0x20009fc4) = 0;
      FUN_00086c78((void*)puVar2,0,0x50);
      iVar7 = FUN_000167a8();
      pcVar12 = VI(iVar7+0x1030);
      uVar4 = FUN_000167a8();
      iVar7 = ((fp_t)pcVar12)(uVar4,iVar14,(void*)puVar2,iVar10>>3);
      if (iVar7 != 0) { DEBUG_PRINT(0x000a8d7f,0x000a8e27,0x7e); goto END; }
      for (iVar7 = 0; iVar7 < iVar10>>3; iVar7 = iVar7 + 1) {
        FUN_00036558((int)(unsigned char)~VB(puVar2+iVar7), iVar5);
      }
      if (VI(0x20009fcc) != 0) {
        VI(0x20009fc8) = 0;
        iVar7 = FUN_000167a8();
        FUN_00086c04(VI(iVar7 + iVar3*4 + 0xb90), VI(0x20009fcc), 0x140);
      }
      iVar14 = iVar14 + (iVar11 >> 5) * -4;
    }
  } else {
    FUN_000777f0(0x000a8dc1);
  }
END:
  FUN_00076d7c(puVar2);
}

