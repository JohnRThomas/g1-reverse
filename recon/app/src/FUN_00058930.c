/* Reconstructed FUN_00058930 @ 0x58930  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_00071c20(int,...);
extern int FUN_000748ac(int,...);
extern int FUN_00081ddc(int,...);
#define g1_recon_z_impl_k_queue_init FUN_000864e8
extern void g1_recon_z_impl_k_queue_init(void *queue);
extern int FUN_00086c78(int,...);
unsigned int FUN_00058930(int param_1, int *param_2)
{
  int *local_20, *local_1c;
  int dummy[16];
  local_1c = (int*)FUN_00071c20(0x20003738, &local_20, 0, 0);
  if (local_1c == 0) {
    int uVar2 = FUN_000748ac(0);
    int *puVar1 = local_20;
    *(volatile int*)0x2000ae9cUL = uVar2;
    FUN_00086c78((int)(local_20 + 1), 0, 0x34);
    *puVar1 = param_1;
    local_20[1] = 0;
    local_20[2] = 0;
    local_20[0xc] = 0;
    local_20[0xd] = 0;
    int iVar3 = FUN_00071c20(0x20003758, &local_1c, 0, 0);
    if (iVar3 == 0) {
      iVar3 = FUN_00086c78((int)local_1c, 0, 0x198);
      *(int*)(iVar3 + 0xc) = 0x200029ac;
      g1_recon_z_impl_k_queue_init((void *)(iVar3 + 0x128));
      puVar1 = local_1c;
      uVar2 = local_1c[0x48];
      local_1c[0x48] = 0;
      *local_1c = (int)local_20;
      if (local_20[0xc] == 0) {
        g1_recon_z_impl_k_queue_init((void *)(local_20 + 3));
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
    FUN_00081ddc(0x88100, 0x1880, dummy);
  } else {
    FUN_00081ddc(0x88100, 0x1840, dummy);
  }
  return 0xfffffff4;
}
