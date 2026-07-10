/* Reconstructed FUN_0005c80c @ 0x5c80c  (parity: 300/300 trials, PROVEN) */

extern int FUN_00053050(unsigned,unsigned,void*,int);
extern int FUN_00082a42(unsigned,unsigned,void*);
extern int FUN_00082c9c(int,unsigned,unsigned,void*);
int FUN_0005c80c(unsigned param_1, unsigned param_2){
  unsigned char* puVar1; int iVar2;
  unsigned local_f0, local_ec; int iStack_e8; unsigned local_dc; unsigned char local_d8;
  unsigned char auStack_d4[192]; int local_14;
  local_d8=(unsigned char)param_1;
  local_14=0;
  local_dc=param_2;
  FUN_00082c9c(1,0xffff,0x5a329,&local_dc);
  if(local_14==0){ puVar1=0; iVar2=0; }
  else { iVar2=local_14<<2; puVar1=auStack_d4; }
  iVar2=FUN_00053050(param_1,param_2,puVar1,iVar2);
  if(iVar2!=0){
    local_ec=0xf4db4; local_f0=3; iStack_e8=iVar2;
    FUN_00082a42(0x88128,0x1840,&local_f0);
  }
  return iVar2;
}

