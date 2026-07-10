/* named: bt_hci_cmd_create */
/* Reconstructed bt_hci_cmd_create @ 0x53cd4  (parity: 300/300 trials, PROVEN) */

extern int FUN_000836de(int,int,int,int);
extern void net_buf_simple_reserve(int,int);
extern int net_buf_id(int);
extern int net_buf_simple_add(int,int);
extern void assert_post_action(int,int);
extern int printk(int,...);
int bt_hci_cmd_create(short param_1,int param_2){
  int iVar2=FUN_000836de(0x20003b4c,param_2,-1,-1);
  if(iVar2==0){ printk(0x99cbd,0xf45be,0xf2e84,0x10a); assert_post_action(0xf2e84,0x10a); }
  net_buf_simple_reserve(iVar2+0xc,1);
  *(volatile char*)(iVar2+0x18)=0;
  int iVar3=net_buf_id(iVar2);
  *(volatile short*)(iVar3*0xc + 0x2000abf4 + 2)=param_1;
  iVar3=net_buf_id(iVar2);
  *(volatile int*)(iVar3*0xc + 0x2000abf4 + 8)=0;
  iVar3=net_buf_id(iVar2);
  *(volatile int*)(iVar3*0xc + 0x2000abf4 + 4)=0;
  int puVar4=net_buf_simple_add(iVar2+0xc,3);
  *(volatile short*)puVar4=param_1;
  *(volatile char*)(puVar4+2)=(char)param_2;
  return iVar2;
}

