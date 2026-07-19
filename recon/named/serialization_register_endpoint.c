/* readable reconstruction; identity: FUN_0004cbec @ 0x0004cbec
 * public-name: serialization_register_endpoint
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   serialization_register_endpoint          <= FUN_0004cbec @ 0x0004cbec
 *   ipc_log_forward                          <= FUN_0007e9ea @ 0x0007e9ea
 * address symbols (name @ address):
 *   rodata_881d8                             @ 0x000881d8
 *   rodata_f0c14                             @ 0x000f0c14
 *   rodata_f0c32                             @ 0x000f0c32
 */
/* Reconstructed FUN_0004cbec @ 0x4cbec  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int ipc_log_forward(int,int,void*);
uint32_t serialization_register_endpoint(int param_1, int *param_2, int param_3){
  uint32_t local[2];
  if(param_1==0 || param_2==0 || param_3==0){
    local[1] = 0x000f0c32;
    local[0] = 2;
    ipc_log_forward(0x000881d8, 0x1040, local);
    return 0xffffffea;
  }
  int iVar2 = *(volatile int*)(param_1+8);
  if(iVar2 != 0 && *(volatile int*)(iVar2+0xc) != 0){
    *param_2 = param_1;
    uint32_t fp = *(volatile uint32_t*)(iVar2+0xc);
    return ((uint32_t(*)(int,int*))(uintptr_t)fp)(param_1, param_2+1);
  }
  local[1] = 0x000f0c14;
  local[0] = 2;
  ipc_log_forward(0x000881d8, 0x1040, local);
  return 0xfffffffb;
}
