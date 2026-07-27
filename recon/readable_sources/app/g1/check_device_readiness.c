#include "g1_app_symbols.h"
#include "../../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_000167b4 @ 0x000167b4
 * public-name: check_device_readiness
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_device_is_ready                        <= FUN_0008638c @ 0x0008638c
 * address symbols (name @ address):
 *   rodata_87bf0                             @ 0x00087bf0
 *   rodata_99726                             @ 0x00099726   [INLINED -- G6 literal batch]
 *   rodata_a40ec                             @ 0x000a40ec
 */
/* Reconstructed check_device_readiness @ 0x167b4  (parity: 300/300 trials, PROVEN) */

extern _Bool z_device_is_ready(const struct device *);
unsigned int check_device_readiness(void){
    unsigned int *puVar1 = (unsigned int*)((unsigned long)&rodata_87bf0) /*=0x87bf0*/;
    int iVar2 = z_device_is_ready((unsigned int)puVar1);
    unsigned int uVar3;
    if(iVar2==0){
        log_message(((unsigned long)&rodata_a40ec) /*=0xa40ec*/, puVar1[0]);
        uVar3 = 0xffffffffU;
    } else {
        void (*fn)(unsigned int,unsigned int,unsigned int) = (void*)(*(unsigned int*)(puVar1[2] + 8));
        fn((unsigned int)puVar1, 0, 0x130000);
        log_message(((unsigned long)"erase_dfu_flash done.\n") /*=0x99726*/);
        uVar3 = 0;
    }
    return uVar3;
}
