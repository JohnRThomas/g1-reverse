#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_bt_conn__param_0248                    [param_0248; library]
 * Raw function identity: 0x0005b0dc.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0005b0dc @ 0x0005b0dc
 * public-name: gatt_find_ccc_for_conn
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_gatt_attr_next                        <= FUN_0005b0b8 @ 0x0005b0b8
 *   gatt_find_ccc_for_conn                   <= FUN_0005b0dc @ 0x0005b0dc
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   bt_uuid_cmp                              <= FUN_00080d3e @ 0x00080d3e
 *   bt_conn_is_peer_addr_le                  <= FUN_000814e6 @ 0x000814e6
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f3ebd                             @ 0x000f3ebd
 *   rodata_f46b8                             @ 0x000f46b8
 *   rodata_f4aa5                             @ 0x000f4aa5
 *   rodata_f4aba                             @ 0x000f4aba
 *   rodata_f4abf                             @ 0x000f4abf
 */
/* Reconstructed FUN_0005b0dc @ 0x5b0dc  (parity: 296/300 trials, PROVEN) */
extern int  bt_gatt_attr_next(int);
extern void assert_post_action(int,int);
extern void printk(int,...);
extern int  bt_uuid_cmp(int,void*);
extern int  bt_conn_is_peer_addr_le(int,int,void*);
#define VI(a) (*(volatile int*)(a))
#define VB(a) (*(volatile unsigned char*)(a))
#define VH(a) (*(volatile unsigned short*)(a))

int gatt_find_ccc_for_conn(int param_1,int param_2,unsigned int param_3,unsigned int param_4){
  int iVar2; int buf[4];
  (void)param_4;
  if (param_1 == 0) { printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/,((unsigned long)&rodata_f3ebd) /*=0xf3ebd*/,((unsigned long)&rodata_f46b8) /*=0xf46b8*/,0xd19);printk(((unsigned long)&rodata_f4aa5) /*=0xf4aa5*/);assert_post_action(((unsigned long)&rodata_f46b8) /*=0xf46b8*/,0xd19); return 0; }
  if (param_2 == 0) { printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/,((unsigned long)&rodata_f4aba) /*=0xf4aba*/,((unsigned long)&rodata_f46b8) /*=0xf46b8*/,0xd1a);printk(((unsigned long)&rodata_f4aa5) /*=0xf4aa5*/);assert_post_action(((unsigned long)&rodata_f46b8) /*=0xf46b8*/,0xd1a); return 0; }
  if (VB(param_1+0xd) != 7) return 0;
  iVar2 = bt_uuid_cmp(VI(param_2), buf);
  if (iVar2 == 0) {
    if ((VB(VI(param_2+0xc)+6) & 0x30) == 0) return 0;
    param_2 = bt_gatt_attr_next(param_2);
    if (param_2 == 0) { printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/,((unsigned long)&rodata_f4aba) /*=0xf4aba*/,((unsigned long)&rodata_f46b8) /*=0xf46b8*/,0xd2b);printk(((unsigned long)&rodata_f4abf) /*=0xf4abf*/);assert_post_action(((unsigned long)&rodata_f46b8) /*=0xf46b8*/,0xd2b); return 0; }
  }
  iVar2 = bt_uuid_cmp(VI(param_2), buf);
  if (iVar2 != 0) {
    param_2 = bt_gatt_attr_next(param_2);
    if (param_2 == 0) { printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/,((unsigned long)&rodata_f4aba) /*=0xf4aba*/,((unsigned long)&rodata_f46b8) /*=0xf46b8*/,0xd31);printk(((unsigned long)&rodata_f4abf) /*=0xf4abf*/);assert_post_action(((unsigned long)&rodata_f46b8) /*=0xf46b8*/,0xd31); return 0; }
  }
  for (;;) {
    iVar2 = bt_uuid_cmp(VI(param_2), buf);
    if (iVar2 == 0) goto LAB_1ca;
    iVar2 = bt_uuid_cmp(VI(param_2), buf);
    if (iVar2 == 0) goto LAB_1ca;
    iVar2 = bt_uuid_cmp(VI(param_2), buf);
    if (iVar2 == 0) goto LAB_1ca;
    iVar2 = bt_uuid_cmp(VI(param_2), buf);
    if (iVar2 == 0) goto LAB_1ca;
    param_2 = bt_gatt_attr_next(param_2);
    if (param_2 == 0) return 0;
  }
LAB_1ca:
  iVar2 = bt_uuid_cmp(VI(param_2), buf);
  if (iVar2 != 0) return 0;
  {
    int puVar4 = VI(param_2+0xc);
    iVar2 = bt_conn_is_peer_addr_le(param_1, VB(puVar4), (void*)(puVar4+1));
    if (iVar2 == 0) return 0;
    return (param_3 & VH(puVar4+8)) != 0;
  }
}
