#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004ea28 @ 0x0004ea28
 * public-name: uuid_store
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gatt_dm_attr_alloc                       <= FUN_0004e8e8 @ 0x0004e8e8
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 * address symbols (name @ address):
 *   rodata_88130                             @ 0x00088130
 *   rodata_f1270                             @ 0x000f1270
 *   rodata_f1284                             @ 0x000f1284
 */
/* Reconstructed FUN_0004ea28 @ 0x4ea28  (parity: 300/300 trials, PROVEN) */

extern void memcpy(int,void*,int);
extern int gatt_dm_attr_alloc(int);
extern int FUN_0004e98c(int);
extern void FUN_0007f406(int,int,void*);

#define get_uuid_size FUN_0004e98c
#define user_data_alloc gatt_dm_attr_alloc
#define memcpy memcpy

int uuid_store(unsigned char *param_1)
{
    /* This is one two-word log argument record.  Keeping the words in a
     * single object preserves the firmware ABI: the logger receives the
     * address of word 0 (severity), followed immediately by the message ID. */
    int log_args[2];
    int uVar1, iVar2;
    if (param_1 == 0) {
        log_args[1] = ((unsigned long)&rodata_f1270) /*=0xf1270*/;
    } else {
        uVar1 = get_uuid_size(*param_1);
        iVar2 = user_data_alloc(uVar1);
        if (iVar2 != 0) {
            memcpy(iVar2, param_1, uVar1);
            return iVar2;
        }
        log_args[1] = ((unsigned long)&rodata_f1284) /*=0xf1284*/;
    }
    log_args[0] = 2;
    FUN_0007f406(((unsigned long)&rodata_88130) /*=0x88130*/, 0x1040, log_args);
    return 0;
}
