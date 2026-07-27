#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00084dea @ 0x00084dea
 * public-name: flash_write_padded_entry
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   flash_area_write                         <= FUN_0007efaa @ 0x0007efaa
 *   flash_area_align                         <= FUN_0007f000 @ 0x0007f000
 *   flash_area_erased_val                    <= FUN_0007f012 @ 0x0007f012
 *   flash_write_padded_entry                 <= FUN_00084dea @ 0x00084dea
 *   safe_memcpy_checked                      <= FUN_00086c1e @ 0x00086c1e
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 */
/* Reconstructed FUN_00084dea @ 0x84dea  (parity: 300/300 trials, PROVEN) */
extern int flash_area_write(unsigned,unsigned,void*,unsigned);
extern unsigned flash_area_align(void);
extern unsigned flash_area_erased_val(unsigned);
extern void safe_memcpy_checked(void*,unsigned,int,int);
extern void memset_bytes(void*, int, int);
int flash_write_padded_entry(unsigned param_1, unsigned param_2, unsigned param_3, int param_4){
    unsigned auStack_28[3];
    auStack_28[0]=param_1; auStack_28[1]=param_2; auStack_28[2]=param_3;
    unsigned i = flash_area_align();
    unsigned uVar3 = ((unsigned)(param_4 - 1) + i) & (unsigned)(-(int)i);
    if (uVar3 < 9){
        unsigned uVar2 = flash_area_erased_val(param_1);
        safe_memcpy_checked(auStack_28, param_3, param_4, 8);
        memset_bytes((char*)auStack_28 + param_4, uVar2, uVar3 - (unsigned)param_4);
        int iVar1 = flash_area_write(param_1, param_2, auStack_28, uVar3);
        if (iVar1 != 0) return 1;
        return iVar1;
    }
    return -1;
}
