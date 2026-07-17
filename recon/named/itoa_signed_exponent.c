/* readable reconstruction; identity: FUN_00086daa @ 0x00086daa
 * public-name: itoa_signed_exponent
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   itoa_signed_exponent                     <= FUN_00086daa @ 0x00086daa
 */
/* Reconstructed FUN_00086daa @ 0x86daa  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
int itoa_signed_exponent(uint8_t *param_1, unsigned int param_2, unsigned int param_3){
  int bVar1; char cVar2; uint8_t *puVar3; uint8_t uVar4; uint8_t *puVar5,*puVar6,*puVar8; int iVar7;
  volatile unsigned int stackbuf[8];
  unsigned int *pStack_1c = &stackbuf[2];
  unsigned int *pStack_18 = &stackbuf[3];
  *pStack_18 = param_3;
  *pStack_1c = param_2;
  *param_1 = (char)param_3;
  if ((int)param_2 < 0){ param_2 = -param_2; uVar4 = 0x2d; }
  else { uVar4 = 0x2b; }
  param_1[1] = uVar4;
  if ((int)param_2 < 10){
    param_1[2]=0x30; puVar3=param_1+4; param_1[3]=(char)param_2+'0';
  } else {
    puVar5 = (uint8_t*)((intptr_t)pStack_1c + 3);
    puVar3 = puVar5;
    do {
      puVar6 = puVar3;
      cVar2 = (char)(param_2/10);
      puVar6[-1] = (char)param_2 + cVar2*-10 + '0';
      bVar1 = 99 < (int)param_2;
      param_2 = param_2/10;
      puVar3 = puVar6 + -1;
    } while(bVar1);
    puVar6[-2] = cVar2 + '0';
    puVar3 = param_1 + 1;
    for(puVar8 = puVar6 + -2; puVar8 < puVar5; puVar8=puVar8+1){
      puVar3=puVar3+1; *puVar3=*puVar8;
    }
    iVar7 = (int)((intptr_t)pStack_18) + (1 - (int)(intptr_t)puVar6);
    if(puVar5 < puVar6+-2){ iVar7=0; }
    puVar3 = param_1 + iVar7 + 2;
  }
  return (int)((intptr_t)puVar3) - (int)((intptr_t)param_1);
}
