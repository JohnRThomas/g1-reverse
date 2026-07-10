/* named: FUN_00074554 */
/* Reconstructed FUN_00074554 @ 0x74554  (parity: 300/300 trials, PROVEN) */

extern void FUN_00074184(int,int);
extern void assert_post_action(int,int);
extern int printk(int,...);
void FUN_00074554(int param_1,int param_2){
  if((unsigned)(param_2+0x10) >= 0x1f){
    printk(0x99cbd,0xf85d2,0xf82f4,0x53d);
    printk(0xf7fee,param_2,0xe,0xfffffff0);
    assert_post_action(0xf82f4,0x53d);
  }
  FUN_00074184(param_1,param_2);
}

