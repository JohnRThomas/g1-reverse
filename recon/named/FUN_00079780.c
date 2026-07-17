/* readable reconstruction; identity: FUN_00079780 @ 0x00079780
 * public-name: FUN_00079780
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_misc_deferred_req_params               @ 0x20002ef8
 *   g_misc_deferred_call_desc                @ 0x20002f0c
 */
/* Reconstructed FUN_00079780 @ 0x79780  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
typedef void (*code)(int, uint32_t);
typedef void (*unary_code)(int);
void FUN_00079780(uint32_t *param_1, uint32_t *param_2){
  volatile uint32_t *puVar1 = (volatile uint32_t*)0x20002f0cUL;
  code pcVar6 = (code)param_1[0];
  puVar1[1]=param_1[1];
  uint32_t uVar4=param_1[3];
  puVar1[2]=param_1[2];
  puVar1[3]=uVar4;
  puVar1[0]=(uint32_t)pcVar6;
  int iVar3=0x2000cc30;
  volatile uint32_t *puVar2=(volatile uint32_t*)0x20002ef8UL;
  puVar2[0]=param_2[0];
  uint32_t uVar5=*(volatile uint32_t*)(iVar3+0x118);
  puVar2[1]=param_2[1]; puVar2[2]=param_2[2];
  uVar4=param_2[4]; puVar2[3]=param_2[3]; puVar2[4]=uVar4;
  uint32_t callback_context=uVar4;
  uVar4=0xa95c5f2c;
  if((uVar5 & 0x3a000000)!=0){
    *(volatile uint32_t*)(iVar3+0x114)=0;
    *(volatile uint32_t*)(iVar3+0x1b8)=0;
    *(volatile uint32_t*)(iVar3+0x118)=uVar4;
    *(volatile uint32_t*)(iVar3+0x1bc)=uVar4;
    pcVar6(iVar3+0x114, callback_context);
    ((unary_code)(puVar1[0]))(iVar3+0x1b8);
    return;
  }
  return;
}
