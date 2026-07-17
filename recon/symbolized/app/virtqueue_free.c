#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00070ee4 @ 0x00070ee4
 * public-name: virtqueue_free
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   virtqueue_free                           <= FUN_00070ee4 @ 0x00070ee4
 * address symbols (name @ address):
 *   rodata_f7b84                             @ 0x000f7b84
 *   g_metal_generic_bus                      @ 0x2000b424
 *   metal_log_handler                        @ 0x2000b428
 */
/* Reconstructed FUN_00070ee4 @ 0x70ee4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void FUN_000868b4(int);

void virtqueue_free(int param_1){
    if (param_1 != 0){
        if (*(short*)(param_1+0x24) != *(short*)(param_1+0xa)
            && 3 < *(unsigned char*)((unsigned long)&g_metal_generic_bus) /*=0x2000b424*/
            && *(void**)((unsigned long)&metal_log_handler) /*=0x2000b428*/ != 0){
            ((void(*)(int,unsigned,int))*(void**)((unsigned long)&metal_log_handler) /*=0x2000b428*/)(4, ((unsigned long)&rodata_f7b84) /*=0xf7b84*/, *(int*)(param_1+4));
        }
        FUN_000868b4(param_1);
    }
}
