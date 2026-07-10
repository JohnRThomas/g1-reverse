/* named: pairing_complete */
/* globals referenced:
//   0x20006ab8  g_ancs_active_conn           
*/
/* Reconstructed pairing_complete @ 0x18730  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern uint32_t FUN_00081526(void);
extern void format_bt_addr_str(void*,void*);
extern int get_device_info(void);
extern int is_battery_critical(void);
extern int memcmp(int,void*,int);
extern void FUN_0005420c(int,int);
extern void FUN_00072880(int);
extern void DEBUG_PRINT(unsigned,void*,unsigned);

void pairing_complete(unsigned param_1, unsigned param_2){
    unsigned char auStack_38[36];
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
        iVar2 = memcmp(iVar2+0x1069, puVar1, 7);
        if (iVar2 != 0){
            iVar2 = get_device_info();
            FUN_0005420c(iVar5, iVar2+0x1069);
            iVar2 = get_device_info();
            *(unsigned char*)(iVar2+0x1070) = (unsigned char)iVar5;
            iVar2 = get_device_info();
            *(int*)(iVar2+0x104c) = iVar5;
            iVar2 = get_device_info();
            FUN_00072880(iVar2+0x80);
        }
    }
    iVar2 = get_device_info();
    *(int*)(iVar2+0x1069) = *(int*)puVar1;
    *(short*)(iVar2+0x106d) = *(short*)((char*)puVar1+4);
    *(unsigned char*)(iVar2+0x106f) = *(unsigned char*)((char*)puVar1+6);
    DEBUG_PRINT(0x0009a638, auStack_38, param_2);
    *(int*)0x20007514 += 1;
    *(unsigned char*)(*(int*)0x20006ab8 + 0x367) = 0;
}

