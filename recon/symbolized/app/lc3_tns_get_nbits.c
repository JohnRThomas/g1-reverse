#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000709d8 @ 0x000709d8
 * public-name: lc3_tns_get_nbits
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   lc3_tns_get_nbits                        <= FUN_000709d8 @ 0x000709d8
 * address symbols (name @ address):
 *   lc3_tns_coeffs_bits                      @ 0x0008fd50
 *   lc3_tns_order_bits                       @ 0x00090080
 */
/* Reconstructed FUN_000709d8 @ 0x709d8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned uint; typedef unsigned short ushort;
#define T34(x) ((uint)*(volatile ushort*)(((unsigned long)&lc3_tns_coeffs_bits) /*=0x8fd50*/ + (unsigned)(x) * 2))
#define T30(x) (*(volatile ushort*)(((unsigned long)&lc3_tns_order_bits) /*=0x90080*/ + (unsigned)(x) * 2))

int lc3_tns_get_nbits(int *param_1)
{
    int iVar1,iVar2,iVar3;
    if(0 < *param_1){
        iVar1 = param_1[2];
        if(iVar1 < 1){ iVar1 = 1; }
        else {
            iVar2 = T34(param_1[4] + 8) + T30(iVar1 - 1 + (uint)*(unsigned char*)(param_1+1) * 8) + 0x800;
            if((((iVar1 != 1) &&
                 (iVar2 = iVar2 + T34(param_1[5] + 0x19), iVar1 != 2))
                && (iVar2 = iVar2 + T34(param_1[6] + 0x2a), iVar1 != 3)
                ) && (((iVar2 = iVar2 + T34(param_1[7] + 0x3b),
                       iVar1 != 4 &&
                       (iVar2 = iVar2 + T34(param_1[8] + 0x4c), iVar1 != 5)) &&
                      ((iVar2 = iVar2 + T34(param_1[9] + 0x5d),
                       iVar1 != 6 &&
                       (iVar2 = iVar2 + T34(param_1[10] + 0x6e), iVar1 != 7)))))){
                iVar2 = iVar2 + T34(param_1[0xb] + 0x7f);
            }
            iVar1 = iVar2 + 0x7ff >> 0xb;
        }
        if(*param_1 != 1){
            iVar2 = param_1[3];
            if(iVar2 < 1){ iVar2 = 1; }
            else {
                iVar3 = T34(param_1[0xc] + 8) + T30(iVar2 - 1 + (uint)*(unsigned char*)(param_1+1) * 8) + 0x800;
                if((((iVar2 != 1) &&
                     (iVar3 = iVar3 + T34(param_1[0xd] + 0x19), iVar2 != 2)) &&
                    ((iVar3 = iVar3 + T34(param_1[0xe] + 0x2a),
                     iVar2 != 3 &&
                     (((iVar3 = iVar3 + T34(param_1[0xf] + 0x3b),
                       iVar2 != 4 &&
                       (iVar3 = iVar3 + T34(param_1[0x10] + 0x4c), iVar2 != 5)) &&
                      (iVar3 = iVar3 + T34(param_1[0x11] + 0x5d), iVar2 != 6)))))) &&
                   (iVar3 = iVar3 + T34(param_1[0x12] + 0x6e), iVar2 != 7)){
                    iVar3 = iVar3 + T34(param_1[0x13] + 0x7f);
                }
                iVar2 = iVar3 + 0x7ff >> 0xb;
            }
            iVar1 = iVar1 + iVar2;
        }
        return iVar1;
    }
    return 0;
}
