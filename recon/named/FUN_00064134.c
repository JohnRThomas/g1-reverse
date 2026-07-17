/* readable reconstruction; identity: FUN_00064134 @ 0x00064134
 * public-name: FUN_00064134
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nvs_ate_id_matches                       <= FUN_00084d70 @ 0x00084d70
 *   flash_area_write_and_close               <= FUN_00084e72 @ 0x00084e72
 * address symbols (name @ address):
 *   rodata_8bb90                             @ 0x0008bb90
 *   rodata_f694f                             @ 0x000f694f
 */
/* Reconstructed FUN_00064134 @ 0x64134  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
typedef unsigned int uint;
extern int FUN_0007ef04(uint, void*);
extern int nvs_ate_id_matches(uint8_t, uint);
extern int flash_area_write_and_close(uint32_t, void*);

uint FUN_00064134(uint param_1, uint32_t param_2, uint param_3, uint32_t param_4){
  int iVar1, iVar2;
  uint8_t *puVar3;
  uint uVar4, uVar5;
  volatile uint8_t S[16];
  *(volatile uint32_t*)(S+0) = param_1;
  *(volatile uint32_t*)(S+4) = param_2;
  *(volatile uint32_t*)(S+8) = param_3;
  *(volatile uint32_t*)(S+12) = param_4;
  iVar1 = FUN_0007ef04(param_1, (void*)S);
  if (iVar1 == 1){
    iVar1 = flash_area_write_and_close(*(uint32_t*)(0x8bb90 + param_1*8), (void*)S);
  }
  if (iVar1 == 0){
    iVar1 = flash_area_write_and_close(*(uint32_t*)(0x8bb90 + param_1*8 + 4), (void*)(S+8));
    if (iVar1 == 1){ S[8]=3; S[0xb]=3; }
    else if (iVar1 != 0) return 0xff;
    int cnt = 0;
    uVar4 = S[0];
    uVar5 = S[8];
    puVar3 = (uint8_t*)0xf694f;
    do {
      iVar2 = nvs_ate_id_matches(puVar3[0], uVar4);
      if (iVar2 != 0 && (iVar2 = nvs_ate_id_matches(puVar3[1], uVar5), iVar2 != 0)
          && (puVar3[2] == 4 || S[3] == puVar3[2])
          && (puVar3[3] == 4 || S[0xb] == puVar3[3])
          && (puVar3[4] == 4 || S[2] == puVar3[4])){
        if ((uint8_t)(puVar3[5] - 2) < 3) return puVar3[5];
        return 0xff;
      }
      cnt = cnt + 1;
      puVar3 = puVar3 + 6;
    } while (cnt != 3);
    return 1;
  }
  return 0xff;
}
