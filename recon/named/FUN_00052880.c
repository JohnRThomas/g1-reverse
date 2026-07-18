/* readable reconstruction; identity: FUN_00052880 @ 0x00052880
 * public-name: FUN_00052880
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_gatt_notify_cb                        <= FUN_0005b754 @ 0x0005b754
 *   z_impl_k_sem_take                        <= FUN_00072908 @ 0x00072908
 *   mutex_unlock_syscall_handler             <= FUN_000745c8 @ 0x000745c8
 *   att_get_max_payload_len                  <= FUN_00080c7c @ 0x00080c7c
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   ADDR_z_impl_net_if_ipv6_addr_rm_by_index_THUMB @ 0x00080c8d
 *   g_200028ec                               @ 0x200028ec
 */
/* Reconstructed FUN_00052880 @ 0x52880  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_000527dc(int,...);
extern int FUN_00056f4c(int,...);
extern int bt_gatt_notify_cb(int,...);
extern int z_impl_k_sem_take(int,...);
extern int FUN_000729fc(int,...);
extern int mutex_unlock_syscall_handler(int,...);
extern int FUN_00080c06(int,...);
extern int att_get_max_payload_len(int,...);
extern int memset_bytes(int,...);
extern int smp_packet_free(int,...);
unsigned int FUN_00052880(int param_1)
{
  struct {
    uint32_t reserved0;
    uint32_t endpoint;
    uint32_t cursor;
    uint16_t chunk_length;
    uint16_t reserved_e;
    uint32_t completion;
    uint32_t reserved14;
  } request;
  unsigned char buf50[0x28];
  unsigned int uVar6, uVar4;
  memset_bytes((int)&request, 0, sizeof(request));
  request.endpoint = 0x200028ecU;
  int iVar8 = *(int*)(param_1+0x18);
  request.cursor = *(uint32_t*)(param_1+0xc);
  request.completion = 0x00080c8dU;
  if ((iVar8 != 0) && (FUN_00056f4c(iVar8, (int)buf50) == 0) && (buf50[0x24] == 2)) {
    uVar4 = (unsigned int)att_get_max_payload_len(param_1);
    if (uVar4 == 0) { uVar6 = 1; goto DONE; }
    int iVar3 = FUN_000527dc(iVar8);
    if ((iVar3 != 0) && (*(unsigned char*)(iVar3+0x69) != 0) &&
        (*(unsigned char*)(param_1+0x1c) == *(unsigned char*)(iVar3+0x69))) {
      FUN_000729fc(iVar3+0x6c);
      unsigned int uVar7 = 0; int bVar2 = 0; unsigned int uVar5;
      while ((uVar6 = 0), (uVar5 = *(unsigned short*)(param_1+0x10)), (uVar7 < uVar5)) {
        if ((*(unsigned char*)(iVar3+0x69) == 0) ||
            (*(unsigned char*)(param_1+0x1c) != *(unsigned char*)(iVar3+0x69))) goto LAB_528a8;
        if ((int)uVar5 < (int)(uVar7 + uVar4)) uVar4 = (uVar5 - uVar7) & 0xffff;
        request.chunk_length = (uint16_t)uVar4;
        int r9 = bt_gatt_notify_cb(iVar8, (int)&request);
        if (r9 == -0xc) {
          if (!bVar2) {
            if (uVar4 < 0x14) { uVar6 = 2; break; }
            uVar4 = (uVar4 << 0xf) >> 0x10;
          }
          mutex_unlock_syscall_handler(0);
        } else {
          if (r9 != 0) { uVar6 = 1; goto DONE; }
          unsigned short uVar1 = (unsigned short)((short)uVar7 + (short)uVar4);
          uVar7 = uVar1;
          request.cursor = *(uint32_t*)(param_1+0xc) + uVar1;
          z_impl_k_sem_take(iVar3+0x6c, 0, 0xffffffff, 0xffffffff);
          bVar2 = 1;
        }
      }
      goto DONE;
    }
  }
LAB_528a8:
  uVar6 = 5;
DONE:
  FUN_00080c06(param_1+0x18);
  smp_packet_free(param_1);
  return uVar6;
}
