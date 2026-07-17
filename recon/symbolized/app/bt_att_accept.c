#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00058930 @ 0x00058930
 * public-name: bt_att_accept
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_att_accept                            <= FUN_00058930 @ 0x00058930
 *   k_mem_slab_alloc                         <= FUN_00071c20 @ 0x00071c20
 *   k_current_get                            <= FUN_000748ac @ 0x000748ac
 *   z_impl_k_queue_init                      <= FUN_000864e8 @ 0x000864e8
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_88100                             @ 0x00088100
 *   g_bt_att_chan_ops                        @ 0x200029ac
 *   g_bt_att_slab                            @ 0x20003738
 *   g_bt_att_chan_slab                       @ 0x20003758
 *   att_handle_rsp_thread                    @ 0x2000ae9c
 */
/* Reconstructed FUN_00058930 @ 0x58930  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int k_mem_slab_alloc(int,...);
extern int k_current_get(int,...);
extern int FUN_00081ddc(int,...);
extern int z_impl_k_queue_init(int,...);
extern int memset_bytes(int,...);
unsigned int bt_att_accept(int param_1, int *param_2)
{
  int *local_20, *local_1c;
  int dummy[16];
  local_1c = (int*)k_mem_slab_alloc(((unsigned long)&g_bt_att_slab) /*=0x20003738*/, &local_20, 0, 0);
  if (local_1c == 0) {
    int uVar2 = k_current_get(0);
    int *puVar1 = local_20;
    *(volatile int*)((unsigned long)&att_handle_rsp_thread) /*=0x2000ae9c*/ = uVar2;
    memset_bytes((int)(local_20 + 1), 0, 0x34);
    *puVar1 = param_1;
    local_20[1] = 0;
    local_20[2] = 0;
    local_20[0xc] = 0;
    local_20[0xd] = 0;
    int iVar3 = k_mem_slab_alloc(((unsigned long)&g_bt_att_chan_slab) /*=0x20003758*/, &local_1c, 0, 0);
    if (iVar3 == 0) {
      iVar3 = memset_bytes((int)local_1c, 0, 0x198);
      *(int*)(iVar3 + 0xc) = ((unsigned long)&g_bt_att_chan_ops) /*=0x200029ac*/;
      z_impl_k_queue_init(iVar3 + 0x128);
      puVar1 = local_1c;
      uVar2 = local_1c[0x48];
      local_1c[0x48] = 0;
      *local_1c = (int)local_20;
      if (local_20[0xc] == 0) {
        z_impl_k_queue_init((int)(local_20 + 3), 0, uVar2);
        local_20[10] = 0;
        local_20[0xb] = 0;
      }
      int *puVar4 = puVar1 + 100;
      puVar1[100] = local_20[0xc];
      local_20[0xc] = (int)puVar4;
      if (local_20[0xd] == 0) local_20[0xd] = (int)puVar4;
      *(short*)((int)local_1c + 0x2e) = 0x17;
      *(short*)((int)local_1c + 0x1e) = 0x17;
      *param_2 = (int)(local_1c + 2);
      return 0;
    }
    FUN_00081ddc(((unsigned long)&rodata_88100) /*=0x88100*/, 0x1880, dummy);
  } else {
    FUN_00081ddc(((unsigned long)&rodata_88100) /*=0x88100*/, 0x1840, dummy);
  }
  return 0xfffffff4;
}
