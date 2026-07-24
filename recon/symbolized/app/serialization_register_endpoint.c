#include "g1_app_symbols.h"
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
    local[1] = ((unsigned long)&rodata_f0c32) /*=0xf0c32*/;
    local[0] = 2;
    ipc_log_forward(((unsigned long)&rodata_881d8) /*=0x881d8*/, 0x1040, local);
    return 0xffffffea;
  }
  int iVar2 = *(volatile int*)(param_1+8);
  if(iVar2 != 0 && *(volatile int*)(iVar2+0xc) != 0){
    *param_2 = param_1;
    uint32_t fp = *(volatile uint32_t*)(iVar2+0xc);
    /* DEFECT FIX (P4 iteration 7) — the third argument was dropped.
     * This is `ipc_service_register_endpoint(instance, ept, cfg)`; the backend
     * vtable slot at +0xc is `register_endpoint(instance, &ept->token, cfg)`.
     * ORIGINAL bytes (app_update.bin @0x4cc34, r2 never written since entry):
     *     4cc34: str.w r0,[r1],#4          ; ept->instance = instance
     *     4cc38: ldr   r3,[r4,#12]         ; backend->register_endpoint
     *     4cc3a: add   sp,#28
     *     4cc3c: ldmia.w sp!,{r4,r5,lr}
     *     4cc40: bx    r3                  ; r0=instance r1=&ept->token r2=cfg
     * The recovered form called it with two arguments, so r2 carried whatever
     * the caller happened to leave there and `cfg` was garbage.  tools/parity
     * and cfg_verify cannot see this class (callees are order-keyed oracles
     * that ignore arguments) — same family as iteration 5 §3(b) and the net
     * core's FUN_0102d558 in iteration 6 §4. */
    return ((uint32_t(*)(int,int*,int))(uintptr_t)fp)(param_1, param_2+1, param_3);
  }
  local[1] = ((unsigned long)&rodata_f0c14) /*=0xf0c14*/;
  local[0] = 2;
  ipc_log_forward(((unsigned long)&rodata_881d8) /*=0x881d8*/, 0x1040, local);
  return 0xfffffffb;
}
