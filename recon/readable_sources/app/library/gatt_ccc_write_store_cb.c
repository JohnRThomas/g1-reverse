#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_gatt_ccc_store_ctx__param_0245         [param_0245; library]
 *   param_3          => struct g1_layout_gatt_ccc_cfg__param_0246               [param_0246; library]
 * Raw function identity: 0x00059dec.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00059dec @ 0x00059dec
 * public-name: gatt_ccc_write_store_cb
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gatt_ccc_write_store_cb                  <= FUN_00059dec @ 0x00059dec
 *   ccc_find_cfg                             <= FUN_000826c2 @ 0x000826c2
 *   bt_addr_le_copy_828da                    <= FUN_000828da @ 0x000828da
 * address symbols (name @ address):
 *   ADDR_gatt_ccc_write_THUMB                @ 0x0005a465
 *   rodata_f2b3a                             @ 0x000f2b3a
 */
/* Reconstructed FUN_00059dec @ 0x59dec  (parity: 300/300 trials, PROVEN) */

extern int ccc_find_cfg(int,...);
extern void bt_addr_le_copy_828da(int,int);
int gatt_ccc_write_store_cb(int param_1, unsigned param_2, int *param_3){
  if(*(int*)(param_1+8) != ADDR_gatt_ccc_write_THUMB /*=0x5a465*/) return 1;
  int r6=*(int*)(param_1+0xc);
  int r5=param_3[2];
  if(r5==0){
    int p=ccc_find_cfg(r6, param_3[0], *(unsigned char*)((int)param_3+4));
    if(p==0) return 1;
    bt_addr_le_copy_828da(p+1, ((unsigned long)&rodata_f2b3a) /*=0xf2b3a*/);
    *(volatile unsigned char*)p = 0;
    *(volatile unsigned short*)(p+8) = 0;
    return 1;
  }
  if(param_3[3]==0) return 0;
  unsigned r3h=*(unsigned short*)r5;
  int p;
  if(r3h==param_2){
    int r5b=param_3[0];
    p=ccc_find_cfg(r6, param_3[0], *(unsigned char*)((int)param_3+4));
    if(p==0){
      p=ccc_find_cfg(r6, ((unsigned long)&rodata_f2b3a) /*=0xf2b3a*/);
      if(p==0) goto L_e2a;
      bt_addr_le_copy_828da(p+1, r5b);
      *(volatile unsigned char*)p = *(unsigned char*)((int)param_3+4);
    }
    *(volatile unsigned short*)(p+8) = *(unsigned short*)(param_3[2]+2);
    goto L_e2a;
  } else if(r3h>=param_2){ return 1; }
L_e2a:;
  int iv=param_3[3]-1;
  *(volatile int*)((int)param_3+0xc)=iv;
  int ret=(iv!=0)?1:0;
  *(volatile int*)((int)param_3+8)=param_3[2]+4;
  return ret;
}
