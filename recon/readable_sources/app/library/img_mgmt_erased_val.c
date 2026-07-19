#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   local_1c         => struct g1_layout_flash_area_info__stack_1118            [stack_1118; library]
 * Raw function identity: 0x00051a5c.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00051a5c @ 0x00051a5c
 * public-name: img_mgmt_erased_val
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   flash_area_open                          <= FUN_0004e048 @ 0x0004e048
 *   img_mgmt_flash_area_id                   <= FUN_0005169c @ 0x0005169c
 *   img_mgmt_erased_val                      <= FUN_00051a5c @ 0x00051a5c
 *   nullsub_3                                <= FUN_0007ef7e @ 0x0007ef7e
 *   flash_area_erased_val                    <= FUN_0007f012 @ 0x0007f012
 *   z_log_msg_static_create_img_mgmt         <= FUN_0008096a @ 0x0008096a
 * address symbols (name @ address):
 *   rodata_88208                             @ 0x00088208
 *   rodata_f25fb                             @ 0x000f25fb
 */
/* Reconstructed FUN_00051a5c @ 0x51a5c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern long long img_mgmt_flash_area_id(void);
extern int flash_area_open(unsigned a, void* b);
extern unsigned char flash_area_erased_val(unsigned a);
extern void nullsub_3(unsigned a);
extern void z_log_msg_static_create_img_mgmt(unsigned a, int b, void* c);
unsigned img_mgmt_erased_val(void){
    unsigned local_1c[2];
    long long uVar3 = img_mgmt_flash_area_id();
    int r5 = (int)(unsigned)uVar3;
    unsigned uVar2;
    if (r5 < 0){
        uVar2 = 0xe;
    } else {
        int local_24 = flash_area_open((unsigned)r5 & 0xff, &local_1c[0]);
        if (local_24 == 0){
            unsigned char uVar1 = flash_area_erased_val(local_1c[0]);
            *(volatile unsigned char*)(uintptr_t)((unsigned long long)uVar3 >> 32) = uVar1;
            nullsub_3(local_1c[0]);
            uVar2 = 0;
        } else {
            volatile struct { unsigned a, b, c, d; } s;
            s.a = 4; s.b = ((unsigned long)&rodata_f25fb) /*=0xf25fb*/; s.c = (unsigned)r5; s.d = (unsigned)local_24;
            z_log_msg_static_create_img_mgmt(((unsigned long)&rodata_88208) /*=0x88208*/, 0x2040, (void*)&s);
            uVar2 = 0xa;
        }
    }
    return uVar2;
}
