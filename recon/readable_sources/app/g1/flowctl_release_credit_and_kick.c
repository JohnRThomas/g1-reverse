#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_uarte_driver_ctx__param_0314           [param_0314; G1-original]
 * Raw function identity: 0x00084b32.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00084b32 @ 0x00084b32
 * public-name: flowctl_release_credit_and_kick
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   uarte_blocking_transfer                  <= FUN_00084a54 @ 0x00084a54
 *   flowctl_release_credit_and_kick          <= FUN_00084b32 @ 0x00084b32
 */
/* Reconstructed FUN_00084b32 @ 0x84b32  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int uarte_blocking_transfer(int,int,int);
void flowctl_release_credit_and_kick(int param_1, uint32_t param_2){
  int iVar5 = *(volatile int*)(param_1+0x10);
  int iVar4 = *(volatile int*)(iVar5+0xc);
  *(volatile uint32_t*)(iVar4+0xc0) = *(volatile uint32_t*)(iVar4+0xc0) & ~param_2;
  int r5 = *(volatile int*)(iVar5+0xc);
  if(*(volatile int*)(r5+0xc0) == 0){
    if(param_2 == 2){
      int r = uarte_blocking_transfer(*(volatile int*)(param_1+4), r5+0xc4, 5);
      *(volatile uint8_t*)(r5+0xc9) = (uint8_t)r;
    }
    int base = *(volatile int*)(*(volatile int*)(param_1+4));
    *(volatile uint32_t*)(base+0x500) = 0;
  }
}
