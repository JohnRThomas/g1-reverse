/* readable reconstruction; identity: FUN_000613c4 @ 0x000613c4
 * public-name: gpio_manage_callback
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gpio_manage_callback                     <= FUN_000613c4 @ 0x000613c4
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f5dfc                             @ 0x000f5dfc
 *   rodata_f5e38                             @ 0x000f5e38
 *   rodata_f5e41                             @ 0x000f5e41
 *   rodata_f5e50                             @ 0x000f5e50
 *   rodata_f5e62                             @ 0x000f5e62
 */
/* Reconstructed FUN_000613c4 @ 0x613c4  (parity: 300/300 trials, PROVEN) */

extern void assert_post_action(int,int);
extern int printk(int,...);
int gpio_manage_callback(int param_1, int *param_2, int param_3){
  int iVar4=*(int*)(param_1+0x10);
  if(param_2==0){ printk(0x99cbd,0xf5e38,0xf5dfc,0x3a); printk(0xf5e41); assert_post_action(0xf5dfc,0x3a); }
  if(param_2[1]==0){ printk(0x99cbd,0xf5e50,0xf5dfc,0x3b); printk(0xf5e62); assert_post_action(0xf5dfc,0x3b); }
  int *puVar1=*(int**)(iVar4+4);
  if(puVar1==0){
  LAB:
    if(param_3==0) return 0xffffffea;
  } else {
    if(puVar1==param_2){
      int uVar3=*param_2;
      *(volatile int*)(iVar4+4)=uVar3;
      if(param_2==*(int**)(iVar4+8)) *(volatile int*)(iVar4+8)=uVar3;
    } else {
      int *puVar2;
      do{ puVar2=puVar1; puVar1=(int*)*(volatile int*)puVar2; if(puVar1==0) goto LAB; }while(param_2!=puVar1);
      *(volatile int*)puVar2=*param_2;
      if(param_2==*(int**)(iVar4+8)) *(volatile int*)(iVar4+8)=(int)puVar2;
    }
    *(volatile int*)param_2=0;
    if(param_3==0) return 0;
  }
  *(volatile int*)param_2=*(volatile int*)(iVar4+4);
  *(volatile int*)(iVar4+4)=(int)param_2;
  if(*(int*)(iVar4+8)==0) *(volatile int*)(iVar4+8)=(int)param_2;
  return 0;
}
