/* named: ble_notify_disconnected */
/* globals referenced:
//   0x2000ad1c  g_ble_conn_cb_list_head      
*/
/* Reconstructed ble_notify_disconnected @ 0x56c78  (parity: 300/300 trials, PROVEN) */

extern int bt_le_conn_params_valid(int);
extern void assert_post_action(int,int);
extern int printk(int,...);
int ble_notify_disconnected(int param_1,int param_2){
  int iVar2=bt_le_conn_params_valid(param_2);
  if(iVar2==0) return 0;
  unsigned uVar1,uVar5; int iVar3,iVar4;
  for(iVar4=*(int*)0x2000ad1c; uVar1=0x88058, uVar5=0x87fec, iVar4!=0; iVar4=*(int*)(iVar4+0x20)){
    if(*(void**)(iVar4+8)!=0){
      iVar3=(*(int(**)(int,int))(iVar4+8))(param_1,param_2);
      if(iVar3==0) return 0;
      iVar3=bt_le_conn_params_valid(param_2);
      if(iVar3==0) return 0;
    }
  }
  while(1){
    if(uVar1<uVar5){ printk(0x99cbd,0xf3a8d,0xf3a5d,0x676); printk(0xf0d20); assert_post_action(0xf3a5d,0x676); }
    if(uVar1<=uVar5) break;
    if(*(void**)(uVar5+8)!=0){
      iVar4=(*(int(**)(int,int))(uVar5+8))(param_1,param_2);
      if(iVar4==0) return 0;
      iVar4=bt_le_conn_params_valid(param_2);
      if(iVar4==0) return 0;
    }
    uVar5=uVar5+0x24;
  }
  return iVar2;
}

