/* readable reconstruction; identity: FUN_000556b0 @ 0x000556b0
 * public-name: ble_conn_addr_resolve_or_create
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   adv_is_directed                          <= FUN_00055698 @ 0x00055698
 *   ble_conn_addr_resolve_or_create          <= FUN_000556b0 @ 0x000556b0
 *   ble_conn_set_state                       <= FUN_00056704 @ 0x00056704
 *   ble_conn_le_alloc                        <= FUN_00056e34 @ 0x00056e34
 * address symbols (name @ address):
 *   rodata_f2b33                             @ 0x000f2b33
 *   g_ble_dev_state                          @ 0x20002000
 */
/* Reconstructed FUN_000556b0 @ 0x556b0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int adv_is_directed(void);
extern int ble_conn_set_state(int,unsigned int);
extern int ble_conn_le_alloc(unsigned int,unsigned int);
extern int FUN_00056ea8(unsigned int,void*);
unsigned int ble_conn_addr_resolve_or_create(unsigned char* param_1,int* param_2){
  unsigned char uVar1=*param_1;
  int iVar2; unsigned int uVar3;
  *(volatile unsigned char*)(0x20002000+0x6f)=uVar1;
  iVar2=adv_is_directed();
  if(iVar2==0){
    iVar2=ble_conn_le_alloc(uVar1,0x000f2b33);
    if(iVar2!=0){ uVar3=4; ble_conn_set_state(iVar2,uVar3); *param_2=iVar2; return 0; }
  } else {
    iVar2=FUN_00056ea8(uVar1,param_1+9);
    if(iVar2!=0) return 0xffffffea;
    iVar2=ble_conn_le_alloc(*param_1,(unsigned int)(param_1+9));
    if(iVar2!=0){ uVar3=5; ble_conn_set_state(iVar2,uVar3); *param_2=iVar2; return 0; }
  }
  return 0xfffffff4;
}
