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
extern void g1_recon_k_free(void *allocation);

void virtqueue_free(int param_1){
    if (param_1 != 0){
        if (*(short*)(param_1+0x24) != *(short*)(param_1+0xa)
            && 3 < *(unsigned char*)0x2000b424
            && *(void**)0x2000b428 != 0){
            ((void(*)(int,unsigned,int))*(void**)0x2000b428)(4, 0x000f7b84, *(int*)(param_1+4));
        }
        g1_recon_k_free((void *)(uintptr_t)(unsigned)param_1);
    }
}
