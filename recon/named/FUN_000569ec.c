/* named: FUN_000569ec */
/* globals referenced:
//   0x00088108  log_module_bt_conn           
*/
/* Reconstructed FUN_000569ec @ 0x569ec  (parity: 300/300 trials, PROVEN) */

extern int net_buf_simple_reserve(int,int);
extern void assert_post_action(unsigned,unsigned);
extern void printk(unsigned,...);
extern int FUN_000813ca(unsigned,unsigned,void*);
extern int FUN_000836de(int,unsigned,unsigned,unsigned);
extern int k_is_in_isr(void);
int FUN_000569ec(int param_1,int param_2,unsigned param_3,unsigned param_4){
  int iVar1; unsigned local_20, local_1c;
  iVar1 = k_is_in_isr();
  if(iVar1!=0){
    printk(0x99cbd,0xf3d75,0xf3a5d,0x55f);
    assert_post_action(0xf3a5d,0x55f);
  }
  if(param_1==0) param_1=0x20003a7c;
  iVar1=FUN_000836de(param_1,0x20003a7c,param_3,param_4);
  if(iVar1==0){
    local_1c=0xf3d84; local_20=2;
    FUN_000813ca(0x88108,0x1080,&local_20);
  } else {
    net_buf_simple_reserve(iVar1+0xc, param_2+5);
  }
  return iVar1;
}

