#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00053cd4 @ 0x00053cd4
 * public-name: bt_hci_cmd_create
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_hci_cmd_create                        <= FUN_00053cd4 @ 0x00053cd4
 *   net_buf_id                               <= FUN_0005ee18 @ 0x0005ee18
 *   net_buf_simple_reserve                   <= FUN_0005f4d4 @ 0x0005f4d4
 *   net_buf_simple_add                       <= FUN_0005f5d0 @ 0x0005f5d0
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   bt_conn_alloc_pdu_buf                    <= FUN_000836de @ 0x000836de
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f2e84                             @ 0x000f2e84
 *   rodata_f45be                             @ 0x000f45be
 *   g_hci_cmd_pool                           @ 0x20003b4c
 *   bt_hci_cmd_data                          @ 0x2000abf4
 */
/* Reconstructed FUN_00053cd4 @ 0x53cd4  (parity: 300/300 trials, PROVEN) */

extern int bt_conn_alloc_pdu_buf(int,int,int,int);
extern void net_buf_simple_reserve(int,int);
extern int net_buf_id(int);
extern int net_buf_simple_add(int,int);
extern void assert_post_action(int,int);
extern int printk(int,...);
int bt_hci_cmd_create(short param_1,int param_2){
  int iVar2=bt_conn_alloc_pdu_buf(((unsigned long)&g_hci_cmd_pool) /*=0x20003b4c*/,param_2,-1,-1);
  if(iVar2==0){ printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/,((unsigned long)&rodata_f45be) /*=0xf45be*/,((unsigned long)&rodata_f2e84) /*=0xf2e84*/,0x10a); assert_post_action(((unsigned long)&rodata_f2e84) /*=0xf2e84*/,0x10a); }
  net_buf_simple_reserve(iVar2+0xc,1);
  *(volatile char*)(iVar2+0x18)=0;
  int iVar3=net_buf_id(iVar2);
  *(volatile short*)(iVar3*0xc + ((unsigned long)&bt_hci_cmd_data) /*=0x2000abf4*/ + 2)=param_1;
  iVar3=net_buf_id(iVar2);
  *(volatile int*)(iVar3*0xc + ((unsigned long)&bt_hci_cmd_data) /*=0x2000abf4*/ + 8)=0;
  iVar3=net_buf_id(iVar2);
  *(volatile int*)(iVar3*0xc + ((unsigned long)&bt_hci_cmd_data) /*=0x2000abf4*/ + 4)=0;
  int puVar4=net_buf_simple_add(iVar2+0xc,3);
  *(volatile short*)puVar4=param_1;
  *(volatile char*)(puVar4+2)=(char)param_2;
  return iVar2;
}
