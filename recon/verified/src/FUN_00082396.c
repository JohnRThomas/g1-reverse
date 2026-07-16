/* Reconstructed FUN_00082396 @ 0x82396  (parity: 300/300 trials, PROVEN) */

extern int FUN_00058f34(void*,int,int);
extern void* FUN_0005f5d0(int,int);
extern int FUN_00081c22(void*);
extern int FUN_000821a4(void*,int);
unsigned FUN_00082396(unsigned* param_1,int param_2){
  unsigned short uVar1; int iVar2; unsigned char* puVar3;
  uVar1 = **(unsigned short**)(param_2+0xc);
  if(uVar1 < 0x17){ return 4; }
  iVar2 = FUN_00058f34(param_1,3,2);
  if(iVar2==0){ return 0xe; }
  puVar3 = (unsigned char*)FUN_0005f5d0(iVar2+0xc,2);
  *puVar3=0xf2;
  puVar3[1]=1;
  FUN_000821a4(param_1,iVar2);
  *(unsigned short*)((int)param_1+0x1e)=0x1f2;
  *(unsigned short*)((int)param_1+0x2e)=uVar1;
  (void)__atomic_fetch_or((unsigned*)(*(int*)*param_1+4), 0x1000u,
                          __ATOMIC_ACQ_REL);
  FUN_00081c22(param_1);
  return 0;
}
