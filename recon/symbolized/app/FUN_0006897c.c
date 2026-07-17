#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0006897c @ 0x0006897c
 * public-name: FUN_0006897c
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   rodata_10000                             @ 0x00010000
 */
/* Reconstructed FUN_0006897c @ 0x6897c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t u32;
#define R32(o) (*(volatile u32*)(param_1+(o)))
#define RI(o)  (*(volatile int*)(param_1+(o)))
void FUN_0006897c(int param_1){
    u32 uVar1 = R32(8);
    if(uVar1 >= ((unsigned long)&rodata_10000) /*=0x10000*/) return;
    u32 uVar4 = R32(4);
    do {
        if(uVar4 < 0xff0000 || RI(0x10) != 0){
            if(RI(0xc) >= 0){
                char* pcVar2 = *(char* volatile*)(param_1+0x30);
                if(pcVar2 < *(char* volatile*)(param_1+0x2c)){
                    *(char* volatile*)(param_1+0x30) = pcVar2+1;
                    *(volatile char*)pcVar2 = (char)(RI(0xc) + RI(0x10));
                }
            }
            int iVar3 = RI(0x14);
            while(iVar3 > 0){
                char* pcVar2 = *(char* volatile*)(param_1+0x30);
                if(*(char* volatile*)(param_1+0x2c) <= pcVar2){
                    RI(0x14) = iVar3-1;
                    if(iVar3-1 > 0) R32(0x14) = 0;
                    break;
                }
                *(char* volatile*)(param_1+0x30) = pcVar2+1;
                *(volatile char*)pcVar2 = (char)(-(RI(0x10)==0));
                iVar3 = RI(0x14) - 1;
                RI(0x14) = iVar3;
            }
            uVar4 = R32(4);
            uVar1 = R32(8);
            R32(0xc) = uVar4 >> 0x10;
            R32(0x10) = 0;
        } else {
            RI(0x14) = RI(0x14) + 1;
        }
        uVar1 = uVar1 << 8;
        uVar4 = (uVar4 & 0xffff) << 8;
        R32(4) = uVar4;
        R32(8) = uVar1;
        if(uVar1 >= ((unsigned long)&rodata_10000) /*=0x10000*/) return;
    } while(1);
}
