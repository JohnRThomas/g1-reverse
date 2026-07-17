#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00018730 @ 0x00018730
 * public-name: pairing_complete
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   format_bt_addr_str                       <= FUN_00018334 @ 0x00018334
 *   pairing_complete                         <= FUN_00018730 @ 0x00018730
 *   is_battery_critical                      <= FUN_00032ee4 @ 0x00032ee4
 *   k_sem_give                               <= FUN_00072880 @ 0x00072880
 * address symbols (name @ address):
 *   rodata_9a638                             @ 0x0009a638
 *   g_ancs_active_conn                       @ 0x20006ab8
 *   g_bonded_count                           @ 0x20007514
 */
/* Reconstructed FUN_00018730 @ 0x18730  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern uint32_t FUN_00081526(void);
extern void format_bt_addr_str(void*,void*);
extern int get_device_info(void);
extern int is_battery_critical(void);
extern int FUN_00086be4(int,void*,int);
extern void FUN_0005420c(int,int);
extern void k_sem_give(int);
extern void DEBUG_PRINT(unsigned, ...);

void pairing_complete(unsigned param_1, unsigned param_2){
    unsigned char auStack_38[32];
    uint32_t *puVar1 = (uint32_t*)FUN_00081526();
    format_bt_addr_str(puVar1, auStack_38);
    int iVar2 = get_device_info();
    if (*(char*)(iVar2+0x1071) != 0){
        iVar2 = get_device_info();
        *(char*)(iVar2+0x1071) = 0;
    }
    int iVar5 = is_battery_critical();
    if (iVar5 == 0){
        iVar2 = get_device_info();
        iVar2 = FUN_00086be4(iVar2+0x1069, puVar1, 7);
        if (iVar2 != 0){
            iVar2 = get_device_info();
            FUN_0005420c(iVar5, iVar2+0x1069);
            iVar2 = get_device_info();
            *(unsigned char*)(iVar2+0x1070) = (unsigned char)iVar5;
            iVar2 = get_device_info();
            *(int*)(iVar2+0x104c) = iVar5;
            iVar2 = get_device_info();
            k_sem_give(iVar2+0x80);
        }
    }
    iVar2 = get_device_info();
    *(int*)(iVar2+0x1069) = *(int*)puVar1;
    *(short*)(iVar2+0x106d) = *(short*)((char*)puVar1+4);
    *(unsigned char*)(iVar2+0x106f) = *(unsigned char*)((char*)puVar1+6);
    DEBUG_PRINT(((unsigned long)&rodata_9a638) /*=0x9a638*/, auStack_38, param_2, iVar2 + 0x1069);
    *(int*)((unsigned long)&g_bonded_count) /*=0x20007514*/ += 1;
    *(unsigned char*)(*(int*)((unsigned long)&g_ancs_active_conn) /*=0x20006ab8*/ + 0x367) = 0;
}
