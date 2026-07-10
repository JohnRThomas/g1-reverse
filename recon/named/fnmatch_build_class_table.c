/* named: fnmatch_build_class_table */
/* Reconstructed fnmatch_build_class_table @ 0x8789c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
uint8_t *fnmatch_build_class_table(int param_1, uint8_t *param_2){
  uint8_t *pbVar1,*pbVar2,*pbVar4; uint8_t bVar3; int iVar5; unsigned int uVar6,uVar7,uVar8;
  uVar6 = (unsigned int)*param_2;
  pbVar1 = (uint8_t*)(param_1 - 1);
  if(uVar6==0x5e){ pbVar4=param_2+2; uVar6=(unsigned int)param_2[1]; bVar3=1; }
  else { pbVar4=param_2+1; bVar3=0; }
  do { pbVar1=pbVar1+1; *pbVar1=bVar3; } while(pbVar1 != (uint8_t*)(param_1+0xff));
  if(uVar6==0){ pbVar2 = pbVar4-1; }
  else {
    LAB:
    do {
      uVar7=uVar6; pbVar1=pbVar4;
      *(uint8_t*)(param_1+uVar7)=bVar3^1;
      while(1){
        pbVar4=pbVar1+1; uVar6=(unsigned int)*pbVar1;
        if(uVar6!=0x2d) break;
        uVar8=(unsigned int)pbVar1[1];
        if((uVar8==0x5d)||((int)uVar8<(int)uVar7)) goto LAB;
        pbVar1=pbVar1+2; uVar6=uVar7;
        do { uVar6=uVar6+1; *(uint8_t*)(param_1+uVar6)=bVar3^1; } while((int)uVar6<(int)uVar8);
        iVar5=(uVar8-uVar7)-1;
        if((int)uVar8<=(int)uVar7) iVar5=0;
        uVar7=uVar7+1+iVar5;
      }
      pbVar2=pbVar4;
    } while((uVar6!=0x5d) && (pbVar2=pbVar1, uVar6!=0));
  }
  return pbVar2;
}

