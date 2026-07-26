#include "g1_app_symbols.h"
#include "../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_00021c04 @ 0x00021c04
 * public-name: mobile_send_notification_to_ble_device_test
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   strlen                                   <= FUN_0000ef12 @ 0x0000ef12
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   subcontracing_send_data_pkcs7            <= FUN_00021a40 @ 0x00021a40
 *   cjson_delete                             <= FUN_00064b1c @ 0x00064b1c
 *   cjson_create_object                      <= FUN_00064ca4 @ 0x00064ca4
 *   cjson_print_pretty                       <= FUN_00085014 @ 0x00085014
 *   cjson_add_item_to_object_thunk           <= FUN_00085046 @ 0x00085046
 *   cjson_add_string_to_object               <= FUN_0008509e @ 0x0008509e
 * address symbols (name @ address):
 *   rodata_9b257                             @ 0x0009b257
 *   rodata_9d749                             @ 0x0009d749   [INLINED -- G6 literal batch]
 *   rodata_9d759                             @ 0x0009d759
 *   rodata_9d768                             @ 0x0009d768
 *   rodata_9d76c                             @ 0x0009d76c
 *   rodata_9d775                             @ 0x0009d775
 *   rodata_9d77d                             @ 0x0009d77d   [INLINED -- G6 literal batch]
 *   rodata_9d789                             @ 0x0009d789   [INLINED -- G6 literal batch]
 *   rodata_9d790                             @ 0x0009d790
 *   rodata_9d79d                             @ 0x0009d79d
 *   rodata_9d7ae                             @ 0x0009d7ae   [INLINED -- G6 literal batch]
 *   rodata_9dfe8                             @ 0x0009dfe8   [INLINED -- G6 literal batch]
 *   rodata_f3fde                             @ 0x000f3fde
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed mobile_send_notification_to_ble_device_test @ 0x21c04  (parity: 300/300 trials, PROVEN) */

typedef unsigned int uint32_t;

extern uint32_t cjson_create_object(void);
extern void cjson_add_string_to_object(uint32_t a, uint32_t b, uint32_t c);
extern void cjson_add_item_to_object_thunk(uint32_t a, uint32_t b, uint32_t c);
extern uint32_t cjson_print_pretty(uint32_t a);
extern uint32_t strlen(uint32_t a);
extern void subcontracing_send_data_pkcs7(uint32_t a, uint32_t b, uint32_t c, uint32_t d);
extern void cjson_delete(uint32_t a);

uint32_t mobile_send_notification_to_ble_device_test(uint32_t param_1, uint32_t param_2, uint32_t param_3)
{
    uint32_t uVar1;
    uint32_t uVar2;
    uint32_t uVar3;

    uVar1 = cjson_create_object();
    cjson_add_string_to_object(uVar1, ((unsigned long)&rodata_9d759) /*=0x9d759*/, ((unsigned long)"com.tencent.xin") /*=0x9d749*/);
    cjson_add_string_to_object(uVar1, ((unsigned long)&rodata_9b257) /*=0x9b257*/, param_1);
    cjson_add_string_to_object(uVar1, ((unsigned long)&rodata_9d76c) /*=0x9d76c*/, ((unsigned long)&rodata_9d768) /*=0x9d768*/);
    cjson_add_string_to_object(uVar1, ((unsigned long)&rodata_9d775) /*=0x9d775*/, param_2);
    cjson_add_string_to_object(uVar1, ((unsigned long)&rodata_f3fde) /*=0xf3fde*/, ((unsigned long)"08-04 09:50") /*=0x9d77d*/);
    cjson_add_string_to_object(uVar1, ((unsigned long)&rodata_9d790) /*=0x9d790*/, ((unsigned long)"\345\276\256\344\277\241") /*=0x9d789*/);
    uVar2 = cjson_create_object();
    cjson_add_item_to_object_thunk(uVar2, ((unsigned long)&rodata_9d79d) /*=0x9d79d*/, uVar1);
    uVar1 = cjson_print_pretty(uVar2);
    if (*(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/ > 2) {
        if (*(volatile uint32_t*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            log_message(((unsigned long)"%s(): %s\n") /*=0x9d7ae*/, ((unsigned long)"mobile_send_notification_to_ble_device_test") /*=0x9dfe8*/, uVar1);
        } else {
            debug_print(((unsigned long)"%s(): %s\n") /*=0x9d7ae*/, ((unsigned long)"mobile_send_notification_to_ble_device_test") /*=0x9dfe8*/, uVar1);
        }
    }
    uVar3 = strlen(uVar1);
    subcontracing_send_data_pkcs7(uVar1, uVar3, 0x4b, param_3);
    cjson_delete(uVar2);
    return 0;
}
