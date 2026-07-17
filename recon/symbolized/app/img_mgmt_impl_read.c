#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000517d8 @ 0x000517d8
 * public-name: img_mgmt_impl_read
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   flash_area_open                          <= FUN_0004e048 @ 0x0004e048
 *   img_mgmt_impl_read                       <= FUN_000517d8 @ 0x000517d8
 *   nullsub_3                                <= FUN_0007ef7e @ 0x0007ef7e
 *   flash_area_read                          <= FUN_0007ef80 @ 0x0007ef80
 * address symbols (name @ address):
 *   rodata_88208                             @ 0x00088208
 *   rodata_f25fb                             @ 0x000f25fb
 *   rodata_f26c4                             @ 0x000f26c4
 */
/* Reconstructed FUN_000517d8 @ 0x517d8  (parity: 300/300 trials, PROVEN) */

extern unsigned long long FUN_0005169c(void);
extern int flash_area_open(unsigned a, void*b);
extern int flash_area_read(unsigned a, int b, unsigned c, unsigned d);
extern void nullsub_3(unsigned a);
extern void FUN_0008096a(unsigned a, unsigned b, void*c);
int img_mgmt_impl_read(unsigned param_1, unsigned param_2, unsigned param_3, unsigned param_4){
    unsigned local_1c; unsigned s[4]; int iVar1;
    unsigned long long uVar2 = FUN_0005169c();
    unsigned uStack_28 = (unsigned)uVar2;
    if ((int)uStack_28 < 0){ iVar1 = 0xe; }
    else {
        int local_24 = flash_area_open(uStack_28 & 0xff, &local_1c);
        if (local_24 == 0){
            iVar1 = flash_area_read(local_1c, (int)(uVar2>>32), param_3, param_4);
            nullsub_3(local_1c);
            if (iVar1 != 0){
                s[1] = ((unsigned long)&rodata_f26c4) /*=0xf26c4*/; s[0] = 3; s[2] = (unsigned)iVar1;
                FUN_0008096a(((unsigned long)&rodata_88208) /*=0x88208*/, 0x1840, s);
                iVar1 = 0xb;
            }
        } else {
            s[1] = ((unsigned long)&rodata_f25fb) /*=0xf25fb*/; s[0] = 4;
            FUN_0008096a(((unsigned long)&rodata_88208) /*=0x88208*/, 0x2040, s);
            iVar1 = 10;
        }
    }
    return iVar1;
}
