#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00032b24 @ 0x00032b24
 * public-name: pt_cmd_dispatch_and_encode_response
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   pt_cmd_dispatch_and_encode_response      <= FUN_00032b24 @ 0x00032b24
 *   buffer_append_sum_checksum               <= FUN_0007d16a @ 0x0007d16a
 * address symbols (name @ address):
 *   rodata_8a208                             @ 0x0008a208
 *   rodata_a74b9                             @ 0x000a74b9   [INLINED -- G6 literal batch]
 *   g_pt_msg_encode_buf                      @ 0x20019ef5
 */
/* Reconstructed FUN_00032b24 @ 0x32b24  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../../../headers/g1_log.h"
extern int buffer_append_sum_checksum(void*,void*);
typedef int (*fp5)(void*,int,void*,void*,uint32_t);
uint32_t pt_cmd_dispatch_and_encode_response(int param_1, char* param_2, int param_3, uint32_t* param_4, uint8_t* param_5, uint32_t param_6){
    if(param_2==0 || param_3==0 || param_4==0 || param_5==0 || param_1==2){
        log_message(((unsigned long)"process_pt_protocol para is error\n") /*=0xa74b9*/); return 0xffffffff;
    }
    int iVar3=0;
    uint8_t cVar1=*(volatile uint8_t*)param_2;
    char* pcVar5=(char*)(uintptr_t)((unsigned long)&rodata_8a208) /*=0x8a208*/;
    while(*(volatile uint8_t*)pcVar5 != cVar1 || *(void* volatile*)(pcVar5+4)==0){
        iVar3++; pcVar5+=8;
        if(iVar3==0x2d){
            uint8_t* p=(uint8_t*)(uintptr_t)*(volatile uint32_t*)param_4;
            *(volatile uint8_t*)(p+1)=1; *(volatile uint8_t*)(p+3)=1; *(volatile uint8_t*)(p+0)=cVar1; *(volatile uint8_t*)(p+2)=3; *(volatile uint8_t*)(p+4)=2;
            *param_5=5;
            goto L68;
        }
    }
    (*(volatile fp5*)(pcVar5+4))(param_2,param_3,param_4,param_5,param_6);
L68:;
    volatile uint8_t* puVar2=(volatile uint8_t*)(uintptr_t)((unsigned long)&g_pt_msg_encode_buf) /*=0x20019ef5*/;
    if(param_1!=0){
        if(param_1!=1) return 0;
        uint8_t original_length = *(volatile uint8_t*)param_5;
        uint8_t* puVar4=(uint8_t*)(uintptr_t)*(volatile uint32_t*)param_4;
        volatile uint8_t* puVar6=(volatile uint8_t*)(uintptr_t)((unsigned long)&g_pt_msg_encode_buf) /*=0x20019ef5*/;
        for(iVar3=0; iVar3<(int)original_length; iVar3++){
            *puVar6=*(volatile uint8_t*)(puVar4+iVar3); puVar6++;
        }
        /* The shipped STR may target an unaligned packet buffer.  A fixed
         * four-byte memcpy preserves that store without alignment UB. */
        uint32_t header = ((uint32_t)original_length << 24) | 0x00ffa55aU;
        __builtin_memcpy(puVar4, &header, sizeof(header));
        for (iVar3 = 0; iVar3 < (int)original_length; iVar3++) {
            puVar4[4 + iVar3] = puVar2[iVar3];
        }
        *param_5 = (uint8_t)(original_length + 4U);
    }
    { int r=buffer_append_sum_checksum(param_4,param_5); if(r==0) return 0; return 0xfffffffc; }
}
