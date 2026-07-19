### FUN_0005fc7c  @ 0x0005fc7c  (size=626)

callers (1): dmic_stream_start
callees (4): __aeabi_uldivmod, nrfx_pdm_init, nrfx_pdm_uninit, FUN_000837a2
strings: "Cannot configure device while it is active" | "Requested configuration is not supported" | "Only 16-bit samples are supported" | "PDM clock frequency: %u, actual PCM rate: %u" | "Cannot find suitable PDM clock configuration." | "Failed to initialize PDM: 0x%08x"

```c
/* readable reconstruction; identity: FUN_0005fc7c @ 0x0005fc7c
 * public-name: FUN_0005fc7c
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   __aeabi_uldivmod                         <= FUN_0000e244 @ 0x0000e244
 *   nrfx_pdm_init                            <= FUN_0006615c @ 0x0006615c
 *   nrfx_pdm_uninit                          <= FUN_000661dc @ 0x000661dc
 * address symbols (name @ address):
 *   rodata_881a0                             @ 0x000881a0
 *   rodata_f5871                             @ 0x000f5871
 */
/* Reconstructed FUN_0005fc7c @ 0x5fc7c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned char byte; typedef uint32_t undefined4; typedef unsigned int uint; typedef unsigned short ushort;
extern int __aeabi_uldivmod(int,...);
extern int nrfx_pdm_init(int,...);
extern int nrfx_pdm_uninit(int,...);
extern int FUN_000837a2(int,...);

#define VU(a)  (*(volatile uint*)(a))
#define VB(a)  (*(volatile byte*)(a))

undefined4 FUN_0005fc7c(int param_1,uint *param_2)
{
  int iVar5 = *(int *)(param_1 + 0x10);
  uint *puVar12 = *(uint **)(param_1 + 4);
  uint *puVar7 = (uint *)param_2[4];
  byte bVar4; uint uVar2,uVar3,uVar6,uVar8,uVar9; int stk[16];

  if (VB(iVar5 + 0x51) != 0) {
    FUN_000837a2(0x881a0,0x1040,(int)stk);
    return 0xfffffff0;
  }
  bVar4 = (byte)param_2[9];
  uVar8 = (uint)bVar4;
  if (uVar8 == 1) {
    *(volatile uint64_t*)((char*)param_2 + 0x1c) = 0;      /* param_2[7],param_2[8]=0 strd */
    VB((int)param_2 + 0x25) = bVar4;
    VB((int)param_2 + 0x27) = bVar4;
    uVar2 = 0;
    if (VB((int)param_2 + 0x26) == 1) goto LAB_fd14;
  } else {
    VB((int)param_2 + 0x25) = 2;
    VU((int)param_2 + 0x20) = 0;
    VB((int)param_2 + 0x27) = 1;
    VU((int)param_2 + 0x1c) = 0x10;
    uVar2 = 0x10;
    if ((VB((int)param_2 + 0x26) == 1) && (uVar8 - 1 < 2)) goto LAB_fd14;
  }
  goto err_ea;

LAB_fd14:
  uVar9 = param_2[5];
  if (((uVar9 == uVar2) || (uVar9 == 1)) && (param_2[6] == 0)) {
    if ((*puVar7 == 0) || ((char)puVar7[1] == 0)) {
      if ((int)(((uint)VB(iVar5 + 0x50)) << 0x1e) > -1) return 0;
      nrfx_pdm_uninit(0);
      VB(iVar5 + 0x50) = VB(iVar5 + 0x50) & 0xfd;
      return 0;
    }
    if ((char)puVar7[1] == 0x10) {
      uint local_60 = (*(char *)((int)puVar12 + 0x20) == 2) ? 0x00bb8000u : 0x01e84800u;
      uint local_70 = *param_2;
      byte *pbVar11 = (byte *)0xf5871;
      int local_68 = 1;
      uVar8 = 0xffffffff;
      while (1) {
        uint local_5c = VB((int)pbVar11);
        uVar6 = *puVar7;
        uVar2 = local_5c * uVar6;
        uVar2 = __aeabi_uldivmod(uVar2 << 0x14, uVar2 >> 0xc, local_60 + (uVar2 >> 1), 0);
        uVar9 = local_60 / (0x100000u / uVar2);
        if ((local_70 <= uVar9) && (uVar9 <= param_2[1])) {
          uVar3 = uVar9 / local_5c;
          if (uVar3 < uVar6) {
            uVar6 = uVar6 - uVar3;
            if (uVar6 < uVar8) { uVar8 = uVar6; }
            else if (uVar8 == 0) goto LAB_fe56;
          } else {
            uVar6 = uVar3 - uVar6;
            if (uVar6 < uVar8) { uVar8 = uVar6; if (uVar6 == 0) goto LAB_fe56; }
          }
        }
        pbVar11 = pbVar11 + 2;
        if (local_68 != 1) break;
        local_68 = 2;
      }
      if (uVar8 != 0xffffffff) goto LAB_fe56;
      goto err_ea;
    }
  }
  goto err_ea;

err_ea:
  FUN_000837a2(0x881a0,0x1040,(int)stk);
  return 0xffffffea;

LAB_fe56:
  FUN_000837a2(0x881a0,0x20c0,(int)stk);
  if ((int)(((uint)VB(iVar5 + 0x50)) << 0x1e) < 0) {
    nrfx_pdm_uninit(0);
    VB(iVar5 + 0x50) = VB(iVar5 + 0x50) & 0xfd;
  }
  uVar9 = nrfx_pdm_init((int)stk, *puVar12);
  if (uVar9 != 0x0bad0000) {
    FUN_000837a2(0x881a0,0x1840,(int)stk);
    return 0xfffffffb;
  }
  VU(iVar5 + 0x18) = (uint)*(ushort *)((int)puVar7 + 6);
  VU(iVar5 + 0x14) = puVar7[2];
  bVar4 = *(byte *)((int)puVar12 + 0x20);
  if (bVar4 != 0) bVar4 = 1;
  bVar4 = bVar4 | 2 | (VB(iVar5 + 0x50) & 0xfc);
  VB(iVar5 + 0x50) = bVar4;
  return 0;
}
```