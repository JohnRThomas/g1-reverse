#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00051a5c @ 0x00051a5c
 * public-name: img_mgmt_impl_erased_val
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   flash_area_open                          <= FUN_0004e048 @ 0x0004e048
 *   img_mgmt_impl_erased_val                 <= FUN_00051a5c @ 0x00051a5c
 *   nullsub_3                                <= FUN_0007ef7e @ 0x0007ef7e
 *   flash_area_erased_val                    <= FUN_0007f012 @ 0x0007f012
 * address symbols (name @ address):
 *   rodata_88208                             @ 0x00088208
 *   rodata_f25fb                             @ 0x000f25fb
 */
/* Reconstructed FUN_00051a5c @ 0x51a5c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern long long FUN_0005169c(void);
extern int flash_area_open(unsigned a, void* b);
extern unsigned char flash_area_erased_val(unsigned a);
extern void nullsub_3(unsigned a);
extern void FUN_0008096a(unsigned a, int b, void* c);
unsigned img_mgmt_impl_erased_val(void){
    unsigned local_1c[2];
    long long uVar3 = FUN_0005169c();
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
            FUN_0008096a(((unsigned long)&rodata_88208) /*=0x88208*/, 0x2040, (void*)&s);
            uVar2 = 0xa;
        }
    }
    return uVar2;
}
