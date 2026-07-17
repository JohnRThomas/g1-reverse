/* readable reconstruction; identity: FUN_000548b8 @ 0x000548b8
 * public-name: FUN_000548b8
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_addr_le_str                           <= FUN_00052cdc @ 0x00052cdc
 *   ver_str                                  <= FUN_00053344 @ 0x00053344
 *   atomic_or                                <= FUN_00080e6a @ 0x00080e6a
 * address symbols (name @ address):
 *   rodata_88138                             @ 0x00088138
 *   rodata_a8ea0                             @ 0x000a8ea0
 *   rodata_f31a5                             @ 0x000f31a5
 *   rodata_f31a9                             @ 0x000f31a9
 *   rodata_f31b8                             @ 0x000f31b8
 *   rodata_f31c9                             @ 0x000f31c9
 *   rodata_f3207                             @ 0x000f3207
 *   g_ble_dev_state                          @ 0x20002000
 *   g_ble_dev_ncmd_sem                       @ 0x200020d4
 */
/* Reconstructed FUN_000548b8 @ 0x548b8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern unsigned bt_addr_le_str(int);
extern unsigned ver_str(unsigned);
extern void atomic_or(unsigned,int);
extern void FUN_00080ea2(unsigned,unsigned,void*);
void FUN_000548b8(void)
{
  unsigned char bVar1; int iVar2 = 0x20002000, iVar6, iVar7;
  unsigned uVar3, uVar4, uVar5;
  unsigned local_48, local_44, local_40, local_3c, uStack_38, local_34, local_30; unsigned short local_2c;
  atomic_or(0x200020d4, 4);
  uStack_38 = 0x000a8ea0;
  if (1 < *(unsigned char*)(iVar2 + 7)) uStack_38 = 0x000f31a5;
  local_34 = bt_addr_le_str(iVar2);
  local_3c = 0x000f31a9; iVar6 = 1; local_30 = 0x03010200; local_40 = 0x02000004;
  FUN_00080ea2(0x00088138, 0x28c0, &local_40);
  uVar5 = 0x01000004; uVar4 = 0x000f31b8; uVar3 = 0x00088138;
  iVar7 = iVar2;
  while (1) {
    iVar7 = iVar7 + 7;
    if ((int)(unsigned)*(unsigned char*)(iVar2 + 7) <= iVar6) break;
    local_34 = bt_addr_le_str(iVar7);
    local_3c = uVar4; local_30 = (local_30 & 0xffff0000) | 0x301; local_40 = uVar5; uStack_38 = iVar6;
    FUN_00080ea2(uVar3, 0x24c0, &local_40);
    iVar6 = iVar6 + 1;
  }
  bVar1 = *(unsigned char*)(iVar2 + 0x70);
  local_40 = ver_str((unsigned)bVar1);
  uStack_38 = (unsigned)*(unsigned short*)(iVar2 + 0x72);
  local_34 = (unsigned)*(unsigned short*)(iVar2 + 0x76);
  local_44 = 0x000f31c9; local_30 = (local_30 & 0xffff0000) | 0x200; local_48 = 0x01000006; local_3c = bVar1;
  FUN_00080ea2(0x00088138, 0x34c0, &local_48);
  bVar1 = *(unsigned char*)(iVar2 + 0x71);
  uStack_38 = ver_str((unsigned)bVar1);
  local_30 = (unsigned)*(unsigned short*)(iVar2 + 0x74);
  local_3c = 0x000f3207; local_2c = 0x200; local_40 = 0x01000005; local_34 = bVar1;
  FUN_00080ea2(0x00088138, 0x2cc0, &local_40);
  return;
}
