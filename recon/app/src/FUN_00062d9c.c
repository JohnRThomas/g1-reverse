/* Reconstructed FUN_00062d9c @ 0x62d9c  (parity: 300/300 trials, PROVEN) */
extern void FUN_0004d944(int,int,void*,int);
extern void FUN_000500ac(int);
extern void FUN_0005010c(int,int,int);
extern int  FUN_00062ad8(int,int);
extern void FUN_00064f30(int);
extern int  FUN_0006540c(int);
extern int  FUN_00084b14(int,int);
extern void g1_recon_nrfx_gppi_channel_endpoints_setup(int,int,int);
extern void FUN_00086726(int,int,int,...);
#define VI(a) (*(volatile int*)(a))
#define VW(a) (*(volatile int*)(a))
#define VC(a) (*(volatile char*)(a))

int FUN_00062d9c(int param_1){
  int iVar1,iVar2,iVar6,uVar3;
  int puVar7 = VI(param_1+4);
  int piVar5 = VI(param_1+0x10);
  int puVar4 = VI(puVar7);
  FUN_0005010c(8,1,0);
  FUN_000500ac(8);
  VW(puVar4+0x500) = 0;
  VW(piVar5) = param_1;
  iVar1 = FUN_00084b14(VI(puVar7+0xc), 0);
  if (iVar1 < 0) return iVar1;
  iVar1 = FUN_00062ad8(param_1, piVar5+4);
  if (iVar1 != 0) return iVar1;
  if (((unsigned)VI(puVar7+4) & 2U) != 0) {
    iVar2 = FUN_0006540c(piVar5+0x1c);
    if (iVar2 != 0x0bad0000) {
      struct { unsigned severity; unsigned message; } diagnostic = {
        2, 0x000f6607
      };
      FUN_0004d944(0x00088290,0x1040,&diagnostic,0);
      return -5;
    }
    g1_recon_nrfx_gppi_channel_endpoints_setup(
        VC(piVar5+0x1c), puVar4+0x120, puVar4+0xc);
    FUN_00064f30(1 << (unsigned int)VC(piVar5+0x1c));
  }
  if (VI(piVar5+0xc) == 0) {
    VW(puVar4+0x500) = 8;
    if (VC((int)puVar7+8) == 0) {
      VW(puVar4+0x110) = 0;
      VW(puVar4+0x534) = VI(piVar5+0x18);
      VW(puVar4+0x538) = 1;
      VW(puVar4) = 1;
    }
  } else {
    iVar6 = piVar5;
    iVar2 = puVar4;
    VW(iVar2+0x304) = 4;
    uVar3 = 1;
    VW(VI(iVar6+0xc)+0xc0) = 1;
    VW(iVar2+0x304) = 0x000a0210;
    VW(iVar2+0x500) = 8;
    if (VI(iVar2+0x14c) != 0) {
      VW(iVar2+4) = 1;
      do { if (VI(iVar2+0x144) != 0) break; } while (VI(iVar2+0x124) == 0);
      VW(iVar2+0x14c) = 0;
      VW(iVar2+0x110) = 0;
      VW(iVar2+0x144) = 0;
      uVar3 = VI(iVar2+0x144);
    }
    FUN_00086726(VI(iVar6+0xc)+0x80, 0x00084b87, 0, uVar3);
    VW(VI(iVar6+0xc)+0xb4) = iVar6;
    FUN_00086726(VI(iVar6+0xc)+0x20, 0x00084c57, 0);
    VW(VI(iVar6+0xc)+0x54) = iVar6;
  }
  if (((unsigned)VI(puVar7+4) & 2U) == 0) VW(puVar4+0x304) = 0x100;
  if (((unsigned)VI(puVar7+4) & 0x10U) != 0) VW(puVar4+0x304) = 0x400000;
  VW(puVar4+0x544) = VI(piVar5+0x14);
  VW(puVar4+0x548) = 0;
  VW(puVar4+8) = 1;
  VW(puVar4+0xc) = 1;
  return iVar1;
}
