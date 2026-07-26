/* readable reconstruction; identity: FUN_00059d24 @ 0x00059d24
 * public-name: gatt_delayed_store_enqueue
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   find_sc_cfg_59b94                        <= FUN_00059b94 @ 0x00059b94
 *   gatt_delayed_store_enqueue               <= FUN_00059d24 @ 0x00059d24
 *   k_work_reschedule                        <= FUN_0007350c @ 0x0007350c
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   bt_addr_le_is_bonded                     <= FUN_00080f92 @ 0x00080f92
 *   atomic_or_0                              <= FUN_000826e0 @ 0x000826e0
 *   read_struct_first_word                   <= FUN_0008270c @ 0x0008270c
 *   bt_addr_le_copy_828da                    <= FUN_000828da @ 0x000828da
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f1722                             @ 0x000f1722   [INLINED -- G6 literal batch]
 *   rodata_f46b8                             @ 0x000f46b8
 *   rodata_f46e8                             @ 0x000f46e8   [INLINED -- G6 literal batch]
 *   g_bt_gatt_sc_cfg                         @ 0x20006328
 *   g_bt_gatt_sc_cfg0_flags                  @ 0x20006330
 *   g_bt_gatt_sc_cfg1_flags                  @ 0x2000633c
 *   g_bt_gatt_sc_cfg2_flags                  @ 0x20006348
 *   g_bt_gatt_delayed_store_work             @ 0x20006350
 */
/* Reconstructed FUN_00059d24 @ 0x59d24  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int find_sc_cfg_59b94(uint32_t,uint32_t);
extern void k_work_reschedule(uint32_t,uint32_t,int,int);
extern void assert_post_action(uint32_t,int);
extern void printk(uint32_t,...);
extern int bt_addr_le_is_bonded(void);
extern uint64_t atomic_or_0(int,uint32_t);
extern int read_struct_first_word(uint32_t);
extern void bt_addr_le_copy_828da(int,uint32_t,int);

void gatt_delayed_store_enqueue(uint32_t param_1, uint32_t param_2, uint32_t param_3){
  int iVar2 = bt_addr_le_is_bonded();
  int iVar3 = find_sc_cfg_59b94(param_1, param_2);
  if (iVar2 == 0) return;
  if (iVar3 == 0){
    int iVar4;
    int t = read_struct_first_word(0x20006330);
    if (t == 0){ iVar2 = 0; iVar4 = 0; }
    else {
      t = read_struct_first_word(0x2000633c);
      if (t == 0){ iVar4 = 1; iVar2 = 0xc; }
      else {
        t = read_struct_first_word(0x20006348);
        if (t != 0){
          printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"),((unsigned long)"el != ((void *)0)"),0xf46b8,0x577);
          printk(((unsigned long)"\tCan't save CF / CCC to flash\n"));
          assert_post_action(0xf46b8,0x577);
        }
        iVar4 = 2; iVar2 = 0x18;
      }
    }
    int iVar1 = 0x20006328;
    iVar3 = iVar2 + 0x20006328;
    bt_addr_le_copy_828da(0x20006328 + iVar2 + 1, param_2, iVar3);
    *(volatile char*)(iVar1 + iVar4*0xc) = (char)param_1;
  }
  uint64_t pending = atomic_or_0(iVar3 + 8, 1 << (param_3 & 0xff));
  k_work_reschedule(0x20006350, (uint32_t)(pending >> 32), 0x8000, 0);
}
