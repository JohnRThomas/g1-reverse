/* Reconstructed ipc0_ept_recv @ 0x25a48  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);
void ipc0_ept_recv(unsigned char *param_1,int param_2){
  int iVar4=0;
  unsigned uVar1=*param_1;
  int *piVar3=(int*)(*(volatile int*)0x20007a84UL + 4);
  int iVar2=*piVar3;
  unsigned char *pbVar5;
  while(1){
    if(iVar2<=iVar4){
      if(1 < *(volatile int*)0x2000230cUL){
        if(*(volatile int*)0x20007554UL == 0){
          DEBUG_PRINT(0x9f4a1,0x9f6e3,uVar1,iVar2,param_2,uVar1,(unsigned)param_1[1],(unsigned)param_1[2],(unsigned)param_1[3],(unsigned)param_1[4],(unsigned)param_1[5],(unsigned)param_1[6],(unsigned)param_1[7]);
        } else {
          FUN_00019c70(0x9f4a1,0x9f6e3,uVar1,iVar2,param_2,uVar1,
                       (unsigned)param_1[1],(unsigned)param_1[2],
                       (unsigned)param_1[3],(unsigned)param_1[4],
                       (unsigned)param_1[5],(unsigned)param_1[6],
                       (unsigned)param_1[7]);
        }
      }
      return;
    }
    piVar3++;
    pbVar5=(unsigned char*)*piVar3;
    if(pbVar5!=0 && *pbVar5==uVar1) break;
    iVar4++;
  }
  (*(void(*)(int,int,int))*(void**)(pbVar5+8))(*(volatile int*)0x20007a84UL - 0x714, (int)(param_1+1), param_2-1);
}
