#include "g1_app_symbols.h"
/* named: mobile_send_notification_to_ble_device_test */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed mobile_send_notification_to_ble_device_test @ 0x21c04  (parity: 300/300 trials, PROVEN) */

extern uint32_t cjson_create_object(void);
extern void FUN_0008509e(uint32_t a, uint32_t b, uint32_t c);
extern void FUN_00085046(uint32_t a, uint32_t b, uint32_t c);
extern uint32_t FUN_00085014(uint32_t a);
extern void DEBUG_PRINT(uint32_t a, uint32_t b, uint32_t c);
extern void debug_print(void);
extern uint32_t strlen(uint32_t a);
extern void subcontracing_send_data_pkcs7(uint32_t a, uint32_t b, uint32_t c, uint32_t d);
extern void cjson_delete(uint32_t a);

uint32_t mobile_send_notification_to_ble_device_test(uint32_t param_1, uint32_t param_2, uint32_t param_3)
{
    uint32_t uVar1;
    uint32_t uVar2;
    uint32_t uVar3;

    uVar1 = cjson_create_object();
    FUN_0008509e(uVar1, "app_identifier" /*=0x9d759*/, "com.tencent.xin" /*=0x9d749*/);
    FUN_0008509e(uVar1, "title" /*=0x9b257*/, param_1);
    FUN_0008509e(uVar1, "subtitle" /*=0x9d76c*/, "aaa" /*=0x9d768*/);
    FUN_0008509e(uVar1, "message" /*=0x9d775*/, param_2);
    FUN_0008509e(uVar1, "date" /*=0xf3fde*/, "08-04 09:50" /*=0x9d77d*/);
    FUN_0008509e(uVar1, "display_name" /*=0x9d790*/, ((uintptr_t)&tbl_9d64e) /*=0x9d789*/);
    uVar2 = cjson_create_object();
    FUN_00085046(uVar2, "ncs_notification" /*=0x9d79d*/, uVar1);
    uVar1 = FUN_00085014(uVar2);
    if (*(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/ > 2) {
        if (*(volatile uint32_t*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            DEBUG_PRINT("%s(): %s\n" /*=0x9d7ae*/, "mobile_send_notification_to_ble_device_test" /*=0x9dfe8*/, uVar1);
        } else {
            debug_print();
        }
    }
    uVar3 = strlen(uVar1);
    subcontracing_send_data_pkcs7(uVar1, uVar3, 0x4b, param_3);
    cjson_delete(uVar2);
    return 0;
}

