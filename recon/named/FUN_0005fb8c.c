/* readable reconstruction; identity: FUN_0005fb8c @ 0x0005fb8c
 * public-name: FUN_0005fb8c
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nrfx_pdm_stop                            <= FUN_00066300 @ 0x00066300
 * address symbols (name @ address):
 *   rodata_837a9                             @ 0x000837a9
 *   rodata_881a0                             @ 0x000881a0
 *   rodata_f5660                             @ 0x000f5660
 *   rodata_f56ae                             @ 0x000f56ae
 *   rodata_f56ca                             @ 0x000f56ca
 */
/* Reconstructed FUN_0005fb8c @ 0x5fb8c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;

extern int FUN_0004b908(uint32_t,void*);
extern uint32_t FUN_0005fb30(void*);
extern void nrfx_pdm_stop(void);
extern void FUN_000837a2(uint32_t,uint32_t,void*);

uint FUN_0005fb8c(int param_1, uint32_t param_2)
{
  int iVar3 = *(volatile int*)(param_1 + 0x10);
  switch (param_2) {
    case 0: case 2:
      if (*(volatile int8_t*)(iVar3 + 0x51) != 0) {
        *(volatile uint8_t*)(iVar3 + 0x52) = 1;
        nrfx_pdm_stop();
      }
      break;
    case 1: case 3: {
      uint8_t b50 = *(volatile uint8_t*)(iVar3 + 0x50);
      if ((int32_t)((uint32_t)b50 << 0x1e) >= 0) {
        struct { uint32_t a,b; } s = { 2, 0x000f5660UL };
        FUN_000837a2(0x000881a0UL, 0x1040, &s);
        return 0xfffffffbUL;
      }
      if (*(volatile int8_t*)(iVar3 + 0x51) == 0) {
        *(volatile uint8_t*)(iVar3 + 0x52) = 0;
        uint32_t *puVar4 = *(volatile uint32_t**)(param_1 + 0x10);
        *(volatile uint8_t*)((char*)puVar4 + 0x51) = 1;
        uint8_t bChk = *(volatile uint8_t*)((char*)puVar4 + 0x50);
        if ((int32_t)((uint32_t)bChk << 0x1f) >= 0) {
          uint32_t uv = FUN_0005fb30(puVar4);
          return uv & (uint32_t)((int32_t)uv >> 31);
        }
        puVar4[4] = 0;
        puVar4[2] = 0x000837a9UL;
        puVar4[3] = 3;
        int iStack_38 = FUN_0004b908(puVar4[0], puVar4 + 1);
        if (iStack_38 < 0) {
          *(volatile uint8_t*)((char*)puVar4 + 0x51) = 0;
          struct { uint32_t a,b,c; } s = { 3, 0x000f56aeUL, (uint32_t)iStack_38 };
          FUN_000837a2(0x000881a0UL, 0x1840, &s);
          return 0xfffffffbUL;
        }
      }
      break;
    }
    default: {
      struct { uint32_t a,b,c; } s = { 3, 0x000f56caUL, param_2 };
      FUN_000837a2(0x000881a0UL, 0x1840, &s);
      return 0xffffffeaUL;
    }
  }
  return 0;
}
