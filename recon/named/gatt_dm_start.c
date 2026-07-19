/* readable reconstruction; identity: FUN_0004ed8c @ 0x0004ed8c
 * public-name: gatt_dm_start
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   uuid_len_from_type                       <= FUN_0004e98c @ 0x0004e98c
 *   gatt_dm_start                            <= FUN_0004ed8c @ 0x0004ed8c
 *   bt_gatt_discover                         <= FUN_0005b9cc @ 0x0005b9cc
 *   atomic_and_0                             <= FUN_0007f3f0 @ 0x0007f3f0
 *   gatt_dm_log_helper                       <= FUN_0007f406 @ 0x0007f406
 *   safe_memcpy_checked                      <= FUN_00086c1e @ 0x00086c1e
 * address symbols (name @ address):
 *   ADDR_FUN_0004ea78_THUMB                  @ 0x0004ea79
 *   rodata_88130                             @ 0x00088130
 *   rodata_f1574                             @ 0x000f1574
 *   cur_service_val                          @ 0x2000a154
 *   g_gatt_dm_context                        @ 0x2000a158
 *   g_gatt_dm_discover_params_uuid           @ 0x2000a15c
 *   g_gatt_dm_discover_params_func           @ 0x2000a160
 *   g_gatt_dm_discover_params_start_handle   @ 0x2000a164
 *   g_gatt_dm_discover_params_end_handle     @ 0x2000a16a
 *   g_gatt_dm_discover_params_type           @ 0x2000a16c
 *   g_gatt_dm_attr_count                     @ 0x2000a288
 *   g_gatt_dm_in_progress_flag               @ 0x2000a28c
 *   g_gatt_dm_svc_uuid_buf                   @ 0x2000a290
 *   g_gatt_dm_chunk_list_head                @ 0x2000a2a4
 *   g_gatt_dm_chunk_list_tail                @ 0x2000a2a8
 *   g_gatt_dm_chunk_used_len                 @ 0x2000a2ac
 *   g_gatt_dm_svc_range_end                  @ 0x2000a2b0
 *   g_gatt_dm_has_uuid_flag                  @ 0x2000a2b4
 */
/* Reconstructed FUN_0004ed8c @ 0x4ed8c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int uuid_len_from_type(int);
extern int bt_gatt_discover(uint32_t,uint32_t);
extern int atomic_and_0(uint32_t,uint32_t);
extern int gatt_dm_log_helper(uint32_t,uint32_t,void*);
extern int safe_memcpy_checked(void*,void*,uint32_t,int);

int gatt_dm_start(uint32_t param_1, uint32_t *param_2, uint32_t param_3, uint32_t param_4){
    int iVar3;
    uint32_t *g = (uint32_t*)0x2000a28cUL;
    if ( (param_2==0 || (( *(uint8_t*)param_2 & 0xfd)==0)) && (param_3!=0) ) {
        uint32_t uVar4 = __atomic_fetch_or(g, 1u, __ATOMIC_SEQ_CST);
        if ((uVar4 & 1) == 0) {
            uint32_t one = uVar4 & 1;
            *(volatile uint32_t*)0x2000a154UL = param_1;
            *(volatile uint32_t*)0x2000a158UL = param_4;
            *(volatile uint32_t*)0x2000a2a4UL = one;
            *(volatile uint32_t*)0x2000a2a8UL = one;
            *(volatile uint8_t*)0x2000a2b4UL = (param_2 != 0) ? 1 : 0;
            *(volatile uint32_t*)0x2000a2b0UL = param_3;
            *(volatile uint32_t*)0x2000a288UL = one;
            *(volatile uint32_t*)0x2000a2acUL = one;
            if (param_2 != 0) {
                uint32_t uVar2 = uuid_len_from_type((uint8_t)*param_2);
                safe_memcpy_checked((void*)0x2000a290UL, (void*)param_2, uVar2, 0x28);
                param_2 = (uint32_t*)0x2000a290UL;
            }
            *(volatile uint32_t*)0x2000a160UL = 0x0004ea79UL;
            *(volatile uint16_t*)0x2000a164UL = 1;
            *(volatile uint16_t*)0x2000a16aUL = 0xffff;
            *(volatile uint32_t*)0x2000a15cUL = (uint32_t)param_2;
            *(volatile uint8_t*)0x2000a16cUL = 0;
            iVar3 = bt_gatt_discover(param_1, 0x2000a15cUL);
            if (iVar3 != 0) {
                struct { uint32_t level, message; int error; } log = {
                    3, 0x000f1574, iVar3
                };
                gatt_dm_log_helper(0x00088130UL, 0x1840, &log);
                atomic_and_0(0x2000a28cUL, 0xfffffffe);
            }
        } else { iVar3 = -0x78; }
    } else { iVar3 = -0x16; }
    return iVar3;
}
