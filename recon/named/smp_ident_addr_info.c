/* readable reconstruction; identity: FUN_0005de70 @ 0x0005de70
 * public-name: smp_ident_addr_info
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_addr_le_str                           <= FUN_00052cdc @ 0x00052cdc
 *   bt_id_find_conflict                      <= FUN_0005503c @ 0x0005503c
 *   ble_conn_visit_by_fixed_index            <= FUN_00056960 @ 0x00056960
 *   ble_notify_identity_resolved             <= FUN_00056d1c @ 0x00056d1c
 *   smp_pairing_complete                     <= FUN_0005daf0 @ 0x0005daf0
 *   smp_ident_addr_info                      <= FUN_0005de70 @ 0x0005de70
 *   bt_keys_find_addr                        <= FUN_0005e938 @ 0x0005e938
 *   bt_keys_get_type                         <= FUN_0005e9d0 @ 0x0005e9d0
 *   bt_keys_clear                            <= FUN_0005ea18 @ 0x0005ea18
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   atomic_test_bit                          <= FUN_00082ff6 @ 0x00082ff6
 *   atomic_set_bit                           <= FUN_00083090 @ 0x00083090
 *   memcmp                                   <= FUN_00086be4 @ 0x00086be4
 * address symbols (name @ address):
 *   ADDR_convert_to_id_on_match_THUMB        @ 0x000831e3
 *   rodata_88180                             @ 0x00088180
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f50a7                             @ 0x000f50a7
 *   rodata_f50d6                             @ 0x000f50d6
 *   rodata_f512c                             @ 0x000f512c
 */
/* Reconstructed FUN_0005de70 @ 0x5de70  (parity: 200/200 trials, PROVEN) */
typedef unsigned int u32;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int undefined4;

extern int bt_addr_le_str(int a);
extern int bt_id_find_conflict(int a);
extern void bt_id_add(int a); /* SDK public wrapper; FUN_0005505c @ 0x0005505c */
extern void ble_conn_visit_by_fixed_index(int a, u32 b, void *c);
extern void ble_notify_identity_resolved(int a);
extern void smp_pairing_complete(int a, int event);
extern int bt_keys_find_addr(u32 a, void *b);
extern int bt_keys_get_type(int a, u32 b, int c);
extern void bt_keys_clear(int a);
extern void assert_post_action(u32 a, u32 b);
extern void printk(u32 a, u32 b, u32 c, u32 d);
extern int atomic_test_bit(void *a, int b);
extern int FUN_00083002(int a, int b);
extern void FUN_00083062(int a, void *b);
extern void FUN_00083074(u32 a, u32 b, void *c);
extern void atomic_set_bit(int a, int b);
extern int memcmp(int a, void *b, int c);

undefined4 smp_ident_addr_info(int param_1, int param_2)
{
  char *pcVar6;
  int iVar5, iVar7, iVar1, iVar2;
  undefined4 uVar3;
  char *pcVar4;

  pcVar6 = *(char **)(param_2 + 0xc);
  *(volatile u8*)(long)(param_1 + 0xe9) = (u8)(*(volatile u8*)(long)(param_1 + 0xe9) & 0xfd);
  iVar5 = *(int *)(long)(param_1 + 0xf0);
  iVar7 = iVar5 + 0x90;

  if ((*pcVar6 != 0) && ((pcVar6[6] & 0xc0) != 0xc0)) {
    bt_addr_le_str((int)(long)pcVar6);
    FUN_00083074(0x00088180u, 0x1c40u, 0);
    bt_addr_le_str(iVar7);
    FUN_00083074(0x00088180u, 0x1c40u, 0);
    return 10;
  }

  iVar1 = memcmp(iVar7, pcVar6, 7);
  if (iVar1 == 0 || (iVar1 = bt_keys_find_addr(*(u8*)(long)(iVar5+8), pcVar6), iVar1 == 0)) {
LAB_df2c:
    iVar1 = atomic_test_bit((void*)(long)(param_1+4), 0xd);
    if (iVar1 != 0) {
      iVar1 = bt_keys_get_type(2, *(u8*)(long)(iVar5+8), iVar7);
      if (iVar1 == 0) {
        bt_addr_le_str(iVar7);
        FUN_00083074(0x00088180u, 0x1c40u, 0);
        goto LAB_df70;
      }
      if (*(char*)(long)(iVar5+3) == 0) {
        pcVar4 = (char*)(long)(iVar5 + 0x9e);
      } else {
        pcVar4 = (char*)(long)(iVar5 + 0x97);
      }
      if ((*pcVar4 == 1) && ((pcVar4[6] & 0xc0) == 0x40)) {
        *(u32*)(long)(iVar1+0x3a) = *(u32*)((long)pcVar4+1);
        *(u16*)(long)(iVar1+0x3e) = *(u16*)((long)pcVar4+5);
        if ((*(char*)(long)(iVar5+0x90) != 0) && ((*(u8*)(long)(iVar5+0x96) & 0xc0) != 0xc0)) {
          ble_conn_visit_by_fixed_index(1, 0x000831e3u, 0);
          FUN_00083062(iVar1+1, pcVar6);
          ble_notify_identity_resolved(iVar5);
        }
      }
      if ((int)((u32)(*(volatile u8*)(long)(param_1+0xe9)) << 0x1e) < 0) {
        printk(0x00099cbdu, 0x000f50d6u, 0x000f50a7u, 0xec9u);
        uVar3 = 0xec9;
        assert_post_action(0x000f50a7u, uVar3);
      }
      iVar5 = bt_id_find_conflict(iVar1);
      if (iVar5 != 0) {
        FUN_00083074(0x00088180u, 0x1080u, 0);
        return 3;
      }
      iVar5 = bt_id_find_conflict(iVar1);
      if (iVar5 != 0) {
        printk(0x00099cbdu, 0x000f512cu, 0x000f50a7u, 0xee5u);
        uVar3 = 0xee5;
        assert_post_action(0x000f50a7u, uVar3);
      }
      bt_id_add(iVar1);
    }
    if ((int)((u32)(*(volatile u8*)(long)(param_1+0xe9)) << 0x1d) < 0) {
      atomic_set_bit(param_1, 10);
    }
    if (*(volatile u16*)(long)(param_1+0xe8) == 0) {
      smp_pairing_complete(param_1, 0);
    }
    uVar3 = 0;
  } else {
    iVar2 = FUN_00083002(param_1, iVar1);
    if (iVar2 != 0) {
      bt_keys_clear(iVar1);
      goto LAB_df2c;
    }
LAB_df70:
    uVar3 = 8;
  }
  return uVar3;
}
