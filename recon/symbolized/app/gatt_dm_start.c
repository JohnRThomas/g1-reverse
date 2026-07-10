#include "g1_app_symbols.h"
/* named: gatt_dm_start */
/* Reconstructed gatt_dm_start @ 0x4ed8c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int FUN_0004e98c(int);
extern int bt_gatt_discover(uint32_t,uint32_t);
extern int atomic_and_0(uint32_t,uint32_t);
extern int FUN_0007f406(uint32_t,uint32_t,void*);
extern int FUN_00086c1e(void*,void*,uint32_t,int);

int gatt_dm_start(uint32_t param_1, uint32_t *param_2, uint32_t param_3, uint32_t param_4){
    int iVar3;
    volatile uint32_t *g = (volatile uint32_t*)((uintptr_t)&g_gatt_dm_in_progress_flag) /*=0x2000a28c*/;
    if ( (param_2==0 || (( *(uint8_t*)param_2 & 0xfd)==0)) && (param_3!=0) ) {
        uint32_t uVar4 = *g;
        *g = uVar4 | 1;
        if ((uVar4 & 1) == 0) {
            uint32_t one = uVar4 & 1;
            *(volatile uint32_t*)((uintptr_t)&cur_service_val) /*=0x2000a154*/ = param_1;
            *(volatile uint32_t*)((uintptr_t)&g_gatt_dm_context) /*=0x2000a158*/ = param_4;
            *(volatile uint32_t*)((uintptr_t)&g_gatt_dm_chunk_list_head) /*=0x2000a2a4*/ = one;
            *(volatile uint32_t*)((uintptr_t)&g_gatt_dm_chunk_list_tail) /*=0x2000a2a8*/ = one;
            *(volatile uint8_t*)((uintptr_t)&g_gatt_dm_has_uuid_flag) /*=0x2000a2b4*/ = (param_2 != 0) ? 1 : 0;
            *(volatile uint32_t*)((uintptr_t)&g_gatt_dm_svc_range_end) /*=0x2000a2b0*/ = param_3;
            *(volatile uint32_t*)((uintptr_t)&g_gatt_dm_attr_count) /*=0x2000a288*/ = one;
            *(volatile uint32_t*)((uintptr_t)&g_gatt_dm_chunk_used_len) /*=0x2000a2ac*/ = one;
            if (param_2 != 0) {
                uint32_t uVar2 = FUN_0004e98c((uint8_t)*param_2);
                FUN_00086c1e((void*)((uintptr_t)&g_gatt_dm_svc_uuid_buf) /*=0x2000a290*/, (void*)param_2, uVar2, 0x28);
                param_2 = (uint32_t*)((uintptr_t)&g_gatt_dm_svc_uuid_buf) /*=0x2000a290*/;
            }
            *(volatile uint32_t*)((uintptr_t)&g_gatt_dm_discover_params_func) /*=0x2000a160*/ = ((uintptr_t)&tbl_4ea6c) /*=0x4ea79*/;
            *(volatile uint16_t*)((uintptr_t)&g_gatt_dm_discover_params_start_handle) /*=0x2000a164*/ = 1;
            *(volatile uint16_t*)((uintptr_t)&g_gatt_dm_discover_params_end_handle) /*=0x2000a16a*/ = ((uintptr_t)&tbl_ffc8) /*=0xffff*/;
            *(volatile uint32_t*)((uintptr_t)&g_gatt_dm_discover_params_uuid) /*=0x2000a15c*/ = (uint32_t)param_2;
            *(volatile uint8_t*)((uintptr_t)&g_gatt_dm_discover_params_type) /*=0x2000a16c*/ = 0;
            iVar3 = bt_gatt_discover(param_1, ((uintptr_t)&g_gatt_dm_discover_params_uuid) /*=0x2000a15c*/);
            if (iVar3 != 0) {
                volatile uint32_t local_28=3, local_24="Discover failed, error: %d." /*=0xf1574*/; volatile int iStack_20=iVar3;
                FUN_0007f406(((uintptr_t)&tbl_880d8) /*=0x88130*/, 0x1840, (void*)&local_28);
                atomic_and_0(((uintptr_t)&g_gatt_dm_in_progress_flag) /*=0x2000a28c*/, 0xfffffffe);
            }
        } else { iVar3 = -0x78; }
    } else { iVar3 = -0x16; }
    return iVar3;
}

