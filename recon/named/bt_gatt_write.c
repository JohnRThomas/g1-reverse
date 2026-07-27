/* readable reconstruction; identity: FUN_0005c22c @ 0x0005c22c
 * public-name: bt_gatt_write
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_gatt_write                            <= FUN_0005c22c @ 0x0005c22c
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   bt_att_get_mtu                           <= FUN_000823fa @ 0x000823fa
 *   gatt_req_send                            <= FUN_00082aee @ 0x00082aee
 * address symbols (name @ address):
 *   rodata_82603                             @ 0x00082603
 *   ADDR_gatt_write_encode_THUMB             @ 0x0008281b
 *   ADDR_gatt_prepare_write_encode_THUMB     @ 0x00082857
 *   ADDR_l2cap_reassemble_frag_THUMB         @ 0x00082e05
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f3ebd                             @ 0x000f3ebd
 *   rodata_f46b8                             @ 0x000f46b8
 *   rodata_f4a0a                             @ 0x000f4a0a   [INLINED -- G6 literal batch]
 *   rodata_f4c07                             @ 0x000f4c07   [INLINED -- G6 literal batch]
 *   rodata_f4cce                             @ 0x000f4cce   [INLINED -- G6 literal batch]
 */
#include "../headers/g1_log.h"
/* Reconstructed FUN_0005c22c @ 0x5c22c  (parity: 300/300 trials, PROVEN) */
extern int assert_post_action(int, int);
extern int bt_att_get_mtu(int);
extern int gatt_req_send(void*, void*, void*, void*, unsigned long, unsigned long);
int bt_gatt_write(int param_1, int *param_2){
  short sVar1; int iVar2; int uVar3; unsigned short uVar4; unsigned uVar5; int uVar6; int uVar7;
  if (param_1==0){
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"),0x000f3ebd,0x000f46b8,0x13de,0,(int)param_2);
    printk(((unsigned long)"\tinvalid parameters\n\n")); uVar3=0x13de; assert_post_action(0x000f46b8,uVar3);
    param_2=(int*)0x13de; goto recheck;
  }
 recheck:
  if (param_2==0 || *param_2==0){
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"),((unsigned long)"params && params->func"),0x000f46b8,0x13df,param_1,(int)param_2);
    printk(((unsigned long)"\tinvalid parameters\n\n")); uVar3=0x13df; assert_post_action(0x000f46b8,uVar3);
    param_2=(int*)0x13df; goto recheck;
  }
  if ((short)param_2[1]==0){
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"),((unsigned long)"params->handle"),0x000f46b8,0x13e0,param_1,(int)param_2);
    printk(((unsigned long)"\tinvalid parameters\n\n")); uVar3=0x13e0; assert_post_action(0x000f46b8,uVar3);
    param_2=(int*)0x13e0; goto recheck;
  }
  if (*(char*)(param_1+0xd)!=7) return 0xffffff80;
  uVar4 = *(unsigned short*)((char*)param_2+0xc);
  if (*(short*)((char*)param_2+6)==0){
    iVar2 = bt_att_get_mtu(param_1);
    uVar5 = (unsigned short)(uVar4+2);
    if (uVar5 <= (unsigned)(iVar2-1U)){
      uVar7=0x12; uVar3=0x00082603; uVar6=0x0008281b; goto LAB;
    }
  }
  sVar1 = bt_att_get_mtu(param_1);
  uVar4 = *(unsigned short*)((char*)param_2+0xc);
  if ((unsigned short)(sVar1-5U) <= *(unsigned short*)((char*)param_2+0xc)) uVar4 = sVar1-5U;
  uVar5 = (unsigned)(unsigned short)(uVar4+4);
  uVar7=0x16; uVar3=0x00082e05; uVar6=0x00082857;
 LAB:
  uVar3 = gatt_req_send(param_1,uVar3,param_2,uVar6,uVar7,uVar5);
  return uVar3;
}
