#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00055614 @ 0x00055614
 * public-name: FUN_00055614
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   rodata_f2b3a                             @ 0x000f2b3a
 *   g_ble_dev_state                          @ 0x20002000
 */
/* Reconstructed FUN_00055614 @ 0x55614  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_00086be4(unsigned int,unsigned int,int,unsigned int,unsigned int);
unsigned int FUN_00055614(unsigned char* param_1,unsigned int param_2,unsigned int param_3,unsigned int param_4){
  int iVar1=((unsigned long)&g_ble_dev_state) /*=0x20002000*/;
  unsigned int uVar4=*(unsigned int*)(param_1+4);
  int iVar2,iVar3;
  if(((int)(uVar4<<0x15)>=0) &&
     (iVar3=*(int*)(param_1+0x10), (iVar3==0 || (uVar4&1)!=0))){
    if(*(volatile unsigned char*)(((unsigned long)&g_ble_dev_state) /*=0x20002000*/+7) <= (unsigned int)*param_1) return 0;
    iVar2=FUN_00086be4((unsigned int)*param_1*7+((unsigned long)&g_ble_dev_state) /*=0x20002000*/,((unsigned long)&rodata_f2b3a) /*=0xf2b3a*/,7,*(volatile unsigned char*)(((unsigned long)&g_ble_dev_state) /*=0x20002000*/+7),param_4);
    if(iVar2==0) return 0;
    if(((uVar4&1)==0)&&(*(volatile unsigned char*)(iVar1+0x70)<9)&&(*(unsigned int*)(param_1+8)<0xa0)) return 0;
    if((uVar4&0x30)==0){
      if(((int)(uVar4<<0x1b)>=0)&&(iVar3!=0)) goto L662;
    } else {
      if(iVar3==0) return 0;
      if((int)(uVar4<<0x1b)>=0) goto L662;
    }
    {
      unsigned int v8=*(unsigned int*)(param_1+8), vc=*(unsigned int*)(param_1+0xc);
      if((v8<=vc)&&(v8>0x1f)&&(vc<0x4001)){
        L662:
        if((uVar4&0x38000)!=0x38000) return 1;
        return 0;
      }
    }
  }
  return 0;
}
