#include "g1_app_symbols.h"
#include "../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_0002e4e8 @ 0x0002e4e8
 * public-name: ext_flash_api_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   z_impl_flash_get_page_count              <= FUN_00083a9a @ 0x00083a9a
 *   z_device_is_ready                        <= FUN_0008638c @ 0x0008638c
 *   kmutex_dlist_init                        <= FUN_000864c2 @ 0x000864c2
 * address symbols (name @ address):
 *   rodata_2e301                             @ 0x0002e301
 *   ADDR_ext_flash_read_THUMB                @ 0x0002e399
 *   ADDR_ext_flash_write_THUMB               @ 0x0002e441
 *   rodata_87bf0                             @ 0x00087bf0
 *   rodata_a3a8b                             @ 0x000a3a8b   [INLINED -- G6 literal batch]
 *   rodata_a3aa6                             @ 0x000a3aa6   [INLINED -- G6 literal batch]
 *   rodata_a3ae5                             @ 0x000a3ae5   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_ext_flash_mutex                        @ 0x20007b54
 *   g_ext_flash_dev                          @ 0x20007b68
 */
/* Reconstructed ext_flash_api_init @ 0x2e4e8  (parity: 300/300 trials, PROVEN) */

extern void kmutex_dlist_init(unsigned int);
extern unsigned int z_device_is_ready(unsigned int);
extern unsigned short z_impl_flash_get_page_count(unsigned int);
extern unsigned int get_device_info(void);

unsigned int ext_flash_api_init(unsigned int *param_1, unsigned int *param_2, unsigned int *param_3, unsigned int param_4)
{
    int iVar4;
    unsigned int uVar5;
    unsigned short uVar3;

    kmutex_dlist_init(((unsigned long)&g_ext_flash_mutex) /*=0x20007b54*/);
    uVar5 = ((unsigned long)&rodata_87bf0) /*=0x87bf0*/;
    iVar4 = z_device_is_ready(((unsigned long)&rodata_87bf0) /*=0x87bf0*/);
    if (iVar4 == 0) {
        if (0 < *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/) {
            if (*(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                log_message(((unsigned long)"%s(): FAILURE!\n") /*=0xa3aa6*/, ((unsigned long)"ext_flash_api_init") /*=0xa3ae5*/);
            } else {
                debug_print(((unsigned long)"%s(): FAILURE!\n") /*=0xa3aa6*/, ((unsigned long)"ext_flash_api_init") /*=0xa3ae5*/);
            }
        }
        uVar5 = 0xffffffff;
    } else {
        *param_1 = ADDR_ext_flash_read_THUMB /*=0x2e399*/;
        *param_2 = ADDR_ext_flash_write_THUMB /*=0x2e441*/;
        *param_3 = ((unsigned long)&rodata_2e301) /*=0x2e301*/;
        iVar4 = *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/;
        *(volatile unsigned int*)((unsigned long)&g_ext_flash_dev) /*=0x20007b68*/ = uVar5;
        if (2 < iVar4) {
            if (*(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                log_message(((unsigned long)"%s(): flash init success!\n") /*=0xa3a8b*/, ((unsigned long)"ext_flash_api_init") /*=0xa3ae5*/, ((unsigned long)&g_ext_flash_dev) /*=0x20007b68*/, 0, param_4);
            } else {
                debug_print(((unsigned long)"%s(): flash init success!\n") /*=0xa3a8b*/, ((unsigned long)"ext_flash_api_init") /*=0xa3ae5*/, ((unsigned long)&g_ext_flash_dev) /*=0x20007b68*/, 0, param_4);
            }
        }
        uVar3 = z_impl_flash_get_page_count(((unsigned long)&rodata_87bf0) /*=0x87bf0*/);
        iVar4 = get_device_info();
        uVar5 = 0;
        *(volatile unsigned short*)(iVar4 + 0x108a) = uVar3;
    }
    return uVar5;
}
