/* readable reconstruction; identity: FUN_0005b270 @ 0x0005b270
 * public-name: gatt_indicate
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_att_create_pdu                        <= FUN_00058eb0 @ 0x00058eb0
 *   bt_att_req_alloc                         <= FUN_000596c0 @ 0x000596c0
 *   bt_att_req_free                          <= FUN_00059708 @ 0x00059708
 *   bt_att_req_send                          <= FUN_00059a90 @ 0x00059a90
 *   gatt_indicate                            <= FUN_0005b270 @ 0x0005b270
 *   net_buf_simple_add                       <= FUN_0005f5d0 @ 0x0005f5d0
 *   bt_att_set_tx_meta_data                  <= FUN_000825ac @ 0x000825ac
 *   bt_gatt_check_perm                       <= FUN_00082cba @ 0x00082cba
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 * address symbols (name @ address):
 *   ADDR_gatt_indicate_rsp_THUMB             @ 0x000825d5
 *   rodata_88128                             @ 0x00088128
 *   rodata_f0000                             @ 0x000f0000
 *   rodata_f4ad5                             @ 0x000f4ad5
 *   rodata_f4aeb                             @ 0x000f4aeb
 *   rodata_f4b16                             @ 0x000f4b16
 */
/* Reconstructed FUN_0005b270 @ 0x5b270  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int bt_att_create_pdu(unsigned,int,int);
extern int bt_att_req_alloc(int,int);
extern void bt_att_req_free(int);
extern int bt_att_req_send(unsigned,int);
extern int FUN_0005b0dc(unsigned,unsigned,int);
extern unsigned net_buf_simple_add(int,int);
extern void bt_att_set_tx_meta_data(int,int,int,int);
extern void FUN_00082a42(unsigned,int,void*);
extern int bt_gatt_check_perm(unsigned,unsigned,int);
extern void memcpy(void*,unsigned,unsigned);
int gatt_indicate(unsigned param_1, unsigned short param_2, int param_3)
{
  unsigned short uVar1; unsigned uVar2; int iVar3, iVar5; unsigned short *puVar4;
  unsigned local_28, local_24;
  iVar3 = bt_gatt_check_perm(param_1, *(unsigned*)(param_3+4), 0x94);
  if (iVar3 == 0) {
    iVar3 = FUN_0005b0dc(param_1, *(unsigned*)(param_3+4), 2);
    if (iVar3 == 0) {
      local_24 = 0x000f4aeb; local_28 = 2; iVar3 = -0x16;
      FUN_00082a42(0x00088128, 0x1080, &local_28);
    } else {
      uVar1 = *(unsigned short*)(param_3+0x14);
      iVar3 = bt_att_req_alloc(0xf0000, 0);
      uVar2 = 0x000825d5;
      iVar5 = uVar1 + 2;
      if (iVar3 != 0) {
        *(volatile int*)(iVar3+0x14) = iVar5;
        *(volatile unsigned char*)(iVar3+0x11) = 0x1d;
        *(volatile unsigned*)(iVar3+0xc) = 0;
        *(volatile unsigned*)(iVar3+4) = uVar2;
        *(volatile int*)(iVar3+0x18) = param_3;
        iVar5 = bt_att_create_pdu(param_1, 0x1d, iVar5);
        if (iVar5 != 0) {
          bt_att_set_tx_meta_data(iVar5, 0, 0, 1);
          puVar4 = (unsigned short*)net_buf_simple_add(iVar5+0xc, 2);
          *(volatile unsigned short*)puVar4 = param_2;
          net_buf_simple_add(iVar5+0xc, *(unsigned short*)(param_3+0x14));
          memcpy(puVar4+1, *(unsigned*)(param_3+0x10), *(unsigned short*)(param_3+0x14));
          *(volatile int*)(iVar3+8) = iVar5;
          iVar5 = bt_att_req_send(param_1, iVar3);
          if (iVar5 == 0) return 0;
          bt_att_req_free(iVar3);
          return iVar5;
        }
        local_24 = 0x000f4b16; local_28 = 2;
        FUN_00082a42(0x00088128, 0x1080, &local_28);
        bt_att_req_free(iVar3);
      }
      iVar3 = -0xc;
    }
  } else {
    iVar3 = -1;
    local_24 = 0x000f4ad5; local_28 = 2;
    FUN_00082a42(0x00088128, 0x1080, &local_28);
  }
  return iVar3;
}
