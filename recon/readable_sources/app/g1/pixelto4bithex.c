#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0003678c @ 0x0003678c
 * public-name: pixelto4bithex
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   pixelto4bithex                           <= FUN_0003678c @ 0x0003678c
 *   malloc                                   <= FUN_00076d6c @ 0x00076d6c
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_a8d69                             @ 0x000a8d69   [INLINED -- G6 literal batch]
 *   rodata_a8e18                             @ 0x000a8e18   [INLINED -- G6 literal batch]
 *   g_pixel4bit_bitpos                       @ 0x20009fc4
 *   g_pixel4bit_row_buf_off                  @ 0x20009fc8
 *   g_pixel4bit_row_buf                      @ 0x20009fcc
 */
/* Reconstructed FUN_0003678c @ 0x3678c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
#include "../../../headers/g1_log.h"
extern int malloc(int,...);
extern int memset_bytes(int,...);
void pixelto4bithex(int param_1,int param_2,unsigned param_3,unsigned param_4){
  volatile int *piVar1 = (volatile int*)((unsigned long)&g_pixel4bit_row_buf) /*=0x20009fcc*/;
  if(*piVar1==0){
    int iVar4 = malloc(0x140);
    *piVar1 = iVar4;
    if(iVar4==0){ log_message(((unsigned long)"[%s-%d]malloc error \n") /*=0xa8d69*/,((unsigned long)"pixelto4bithex") /*=0xa8e18*/,0xa7,param_4); return; }
    memset_bytes(iVar4,0,0x140);
  }
  volatile int *piVar3 = (volatile int*)((unsigned long)&g_pixel4bit_row_buf_off) /*=0x20009fc8*/;
  volatile int *piVar2 = (volatile int*)((unsigned long)&g_pixel4bit_bitpos) /*=0x20009fc4*/;
  unsigned uVar5 = 0;
  do{
    int iVar4 = *piVar2;
    if(param_2 <= iVar4) return;
    *piVar2 = iVar4 + 2;
    unsigned uVar7 = ((unsigned)param_1 << (uVar5 & 0xff)) & 0xc0;
    unsigned char uVar6;
    if(uVar7==0xc0) uVar6=0;
    else if(uVar7==0x80) uVar6=0xf;
    else if(uVar7==0x40) uVar6=0xf0;
    else if(uVar7==0) uVar6=0xff;
    else uVar6=0x99;
    *(volatile uint8_t*)((unsigned)*piVar1 + (unsigned)*piVar3) = uVar6;
    uVar5 += 2;
    *piVar3 = *piVar3 + 1;
  } while(uVar5!=8);
}
