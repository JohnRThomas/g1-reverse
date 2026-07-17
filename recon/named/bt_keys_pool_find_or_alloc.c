/* readable reconstruction; identity: FUN_0005e614 @ 0x0005e614
 * public-name: bt_keys_pool_find_or_alloc
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_keys_pool_find_or_alloc               <= FUN_0005e614 @ 0x0005e614
 * address symbols (name @ address):
 *   rodata_f2b3a                             @ 0x000f2b3a
 *   bt_keys_pool                             @ 0x2000af4c
 *   g_bt_keys_pool_entry0_addr               @ 0x2000af4d
 *   g_bt_keys_pool_entry1_addr               @ 0x2000afa9
 */
/* Reconstructed FUN_0005e614 @ 0x5e614  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int FUN_00086be4(int,...);
unsigned char* bt_keys_pool_find_or_alloc(unsigned param_1, unsigned *param_2, unsigned p3, unsigned p4){
  volatile unsigned char *pbVar1=(volatile unsigned char*)0x2000af4cUL;
  int iVar2;
  if(*pbVar1==param_1){
    iVar2=FUN_00086be4((int)(pbVar1+1),(int)param_2,7,(unsigned)*pbVar1,p4);
    if(iVar2==0) return (unsigned char*)pbVar1;
  }
  iVar2=FUN_00086be4(0x2000af4d,0xf2b3a,7);
  unsigned uVar4=(unsigned)pbVar1[0x5c];
  if(iVar2==0){
    if(uVar4==param_1){
      int iVar3=FUN_00086be4(0x2000afa9,(int)param_2,7,uVar4,p4);
      if(iVar3==0) return (unsigned char*)(pbVar1+0x5c);
    }
    iVar2=0;
  } else {
    if(uVar4==param_1){
      iVar2=FUN_00086be4(0x2000afa9,(int)param_2,7,uVar4,p4);
      if(iVar2==0) return (unsigned char*)(pbVar1+0x5c);
    }
    iVar2=FUN_00086be4(0x2000afa9,0xf2b3a,7);
    if(iVar2!=0) return (unsigned char*)0;
    iVar2=1;
  }
  iVar2=iVar2*0x5c;
  pbVar1[iVar2]=(unsigned char)param_1;
  *(volatile uint32_t*)(pbVar1+iVar2+1)=*param_2;
  *(volatile uint16_t*)(pbVar1+iVar2+5)=*(uint16_t*)((char*)param_2+4);
  pbVar1[iVar2+7]=*(uint8_t*)((char*)param_2+6);
  return (unsigned char*)(pbVar1+iVar2);
}
