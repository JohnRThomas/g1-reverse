#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0005ec18 @ 0x0005ec18
 * public-name: bt_keys_store
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_log_msg_runtime_create                 <= FUN_0004d944 @ 0x0004d944
 *   bt_keys_settings_store                   <= FUN_00053168 @ 0x00053168
 *   bt_keys_store                            <= FUN_0005ec18 @ 0x0005ec18
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_88158                             @ 0x00088158
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f5268                             @ 0x000f5268
 *   rodata_f5298                             @ 0x000f5298   [INLINED -- G6 literal batch]
 *   rodata_f5353                             @ 0x000f5353
 */
/* Reconstructed FUN_0005ec18 @ 0x5ec18  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void printk(unsigned int,unsigned int,unsigned int,int);
extern void assert_post_action(unsigned int,int);
extern int bt_keys_settings_store(unsigned int,void*,void*,int);
extern void z_log_msg_runtime_create(unsigned int,unsigned int,void*,int);
int bt_keys_store(unsigned char* param_1){
  int iVar1;
  struct{unsigned int a,b; int c;} log;
  if(param_1==0){
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)"keys != ((void *)0)") /*=0xf5298*/,((unsigned long)&rodata_f5268) /*=0xf5268*/,0x146);
    assert_post_action(((unsigned long)&rodata_f5268) /*=0xf5268*/,0x146);
  }
  iVar1=bt_keys_settings_store(*param_1,param_1+1,param_1+0xc,0x50);
  if(iVar1!=0){
    log.b=((unsigned long)&rodata_f5353) /*=0xf5353*/; log.a=3; log.c=iVar1;
    z_log_msg_runtime_create(((unsigned long)&rodata_88158) /*=0x88158*/,0x1840,&log,0);
  }
  return iVar1;
}
