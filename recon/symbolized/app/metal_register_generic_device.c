#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00068170 @ 0x00068170
 * public-name: metal_register_generic_device
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   metal_bus_find                           <= FUN_00068134 @ 0x00068134
 *   metal_register_generic_device            <= FUN_00068170 @ 0x00068170
 * address symbols (name @ address):
 *   rodata_f7a8c                             @ 0x000f7a8c
 *   g_metal_generic_bus                      @ 0x2000b424
 */
/* Reconstructed FUN_00068170 @ 0x68170  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int metal_bus_find(int,int);
uint32_t metal_register_generic_device(uint32_t *param_1){
  if(param_1==0) return 0xffffffea;
  uint32_t pc2 = *(volatile uint32_t*)param_1;
  if(pc2==0) return 0xffffffea;
  if(*(volatile uint8_t*)pc2==0) return 0xffffffea;
  int iVar3 = metal_bus_find((int)pc2, 0);
  if(iVar3==0) return 0xffffffef;
  uint32_t base = (uint32_t)(uintptr_t)param_1;
  *(volatile uint32_t*)(base+0x1c) = base+0x1c;
  *(volatile uint32_t*)(base+0x20) = base+0x1c;
  uint32_t g = ((unsigned long)&g_metal_generic_bus) /*=0x2000b424*/;
  uint32_t puVar6 = *(volatile uint32_t*)(g+0xc);
  *(volatile uint32_t*)(g+0xc) = base+0x24;
  *(volatile uint32_t*)(base+0x28) = puVar6;
  *(volatile uint32_t*)(base+0x24) = g+8;
  *(volatile uint32_t*)puVar6 = base+0x24;
  if(*(volatile uint8_t*)g > 6){
    uint32_t fp = *(volatile uint32_t*)(g+4);
    if(fp != 0){
      ((void(*)(int,int,int))(uintptr_t)fp)(7, ((unsigned long)&rodata_f7a8c) /*=0xf7a8c*/, *(volatile uint32_t*)base);
    }
  }
  return 0;
}
