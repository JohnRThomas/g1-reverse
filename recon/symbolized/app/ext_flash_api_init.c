#include "g1_app_symbols.h"
/* named: ext_flash_api_init */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
//   0x20007b54  g_ext_flash_mutex            
//   0x20007b68  g_ext_flash_dev              
*/
/* Reconstructed ext_flash_api_init @ 0x2e4e8  (parity: 300/300 trials, PROVEN) */

extern void kmutex_dlist_init(unsigned int);
extern unsigned int z_device_is_ready(unsigned int);
extern unsigned short z_impl_flash_get_page_count(unsigned int);
extern unsigned int get_device_info(void);
extern void DEBUG_PRINT(unsigned int, unsigned int, ...);
extern void debug_print(void);

unsigned int ext_flash_api_init(unsigned int *param_1, unsigned int *param_2, unsigned int *param_3, unsigned int param_4)
{
    int iVar4;
    unsigned int uVar5;
    unsigned short uVar3;

    kmutex_dlist_init(((uintptr_t)&g_ext_flash_mutex) /*=0x20007b54*/);
    uVar5 = ((uintptr_t)&tbl_87b30) /*=0x87bf0*/;
    iVar4 = z_device_is_ready(((uintptr_t)&tbl_87b30) /*=0x87bf0*/);
    if (iVar4 == 0) {
        if (0 < *(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
            if (*(volatile unsigned int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                DEBUG_PRINT("%s(): FAILURE!\n" /*=0xa3aa6*/, "ext_flash_api_init" /*=0xa3ae5*/);
            } else {
                debug_print();
            }
        }
        uVar5 = 0xffffffff;
    } else {
        *param_1 = ((uintptr_t)&rodata_2e399) /*=0x2e399*/;
        *param_2 = ((uintptr_t)&tbl_2e428) /*=0x2e441*/;
        *param_3 = ((uintptr_t)&tbl_2e2c4) /*=0x2e301*/;
        iVar4 = *(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/;
        *(volatile unsigned int*)((uintptr_t)&g_ext_flash_dev) /*=0x20007b68*/ = uVar5;
        if (2 < iVar4) {
            if (*(volatile unsigned int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                DEBUG_PRINT("%s(): flash init success!\n" /*=0xa3a8b*/, "ext_flash_api_init" /*=0xa3ae5*/, ((uintptr_t)&tbl_87b30) /*=0x87bf0*/, 0, param_4);
            } else {
                debug_print();
            }
        }
        uVar3 = z_impl_flash_get_page_count(((uintptr_t)&tbl_87b30) /*=0x87bf0*/);
        iVar4 = get_device_info();
        uVar5 = 0;
        *(volatile unsigned short*)(iVar4 + 0x108a) = uVar3;
    }
    return uVar5;
}

