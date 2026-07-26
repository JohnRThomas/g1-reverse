/* readable reconstruction; identity: FUN_00032628 @ 0x00032628
 * public-name: get_flash_info
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   device_api_call_slot0                    <= FUN_0007d120 @ 0x0007d120
 *   z_device_is_ready                        <= FUN_0008638c @ 0x0008638c
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 * address symbols (name @ address):
 *   rodata_87bf0                             @ 0x00087bf0
 *   rodata_9e2da                             @ 0x0009e2da   [INLINED -- G6 literal batch]
 *   rodata_a40e6                             @ 0x000a40e6   [INLINED -- G6 literal batch]
 *   rodata_a69f3                             @ 0x000a69f3   [INLINED -- G6 literal batch]
 *   rodata_a6a0b                             @ 0x000a6a0b   [INLINED -- G6 literal batch]
 *   rodata_a6aab                             @ 0x000a6aab   [INLINED -- G6 literal batch]
 *   rodata_a76cb                             @ 0x000a76cb   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_flash_info                             @ 0x20019daf
 */
/* Reconstructed get_flash_info @ 0x32628  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
#include "../headers/g1_log.h"
extern int get_device_info(void);
extern int device_api_call_slot0(int,int,int,int,void*);
extern int z_device_is_ready(int);
extern int memcpy(void*,int,int);

uint32_t get_flash_info(int param_1, uint32_t param_2, uint32_t *param_3, uint8_t *param_4){
    volatile uint8_t *puVar4;
    int iVar2;
    uint8_t uVar3;
    volatile uint8_t *puVar5 = (volatile uint8_t*)param_4;
    log_message(((unsigned long)"join in get_flash_info\n"));
    if (param_3==0 || param_4==0){ log_message(((unsigned long)"get_flash_info para is NULL\n")); return 0xffffffff; }
    puVar4 = (volatile uint8_t*)*param_3;
    *puVar4 = 0x1e;
    uVar3 = *(volatile uint8_t*)(param_1+1);
    puVar4[2]=3; puVar4[1]=uVar3; puVar4[3]=4;
    iVar2 = z_device_is_ready(0x00087bf0);
    if (iVar2==0){
        if (0 < *(volatile int*)0x2000230cUL){
            uint32_t v = *(volatile uint32_t*)0x00087bf0UL;
            int c = *(volatile int*)0x20007554UL;
            if (c==0){ log_message(((unsigned long)"%s():  [%s] device not ready.\n"),((unsigned long)"get_flash_info"),v); }
            else { debug_print(((unsigned long)"%s():  [%s] device not ready.\n"),((unsigned long)"get_flash_info"),v); }
        }
        *puVar4=0x1e; puVar4[1]=*(volatile uint8_t*)(param_1+1); puVar4[2]=3; uVar3=1; puVar4[3]=1;
        puVar4[4]=uVar3; uVar3=5;
    } else {
        iVar2 = get_device_info();
        if (*(volatile int*)(iVar2+0x1030) != 0){
            iVar2 = device_api_call_slot0(0x00087bf0, 0x002612d2, 0x20019daf, 0x4e, (void*)puVar5);
            if (iVar2 != 0){
                log_message(((unsigned long)"Flash read failed! %d\n"), iVar2);
                *puVar4=0x1e; uVar3=*(volatile uint8_t*)(param_1+1); puVar4[2]=3; puVar4[1]=uVar3; puVar4[3]=1; uVar3=2;
                puVar4[4]=uVar3; uVar3=5;
                *(volatile uint8_t*)param_4=uVar3; return 0;
            }
            log_message(((unsigned long)"flash read ok\n"), 0);
        }
        memcpy((void*)(puVar4+4), 0x20019daf, 0x4e);
        uVar3=0x52;
    }
    *(volatile uint8_t*)param_4=uVar3;
    return 0;
}
