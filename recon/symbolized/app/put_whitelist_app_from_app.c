#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00035688 @ 0x00035688
 * public-name: put_whitelist_app_from_app
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   parse_receiver_pack_pkcs7                <= FUN_00019cd0 @ 0x00019cd0
 *   parse_whitelist_json                     <= FUN_00034dbc @ 0x00034dbc
 *   verify_whitelist_json                    <= FUN_00035050 @ 0x00035050
 *   store_whitelist                          <= FUN_00035608 @ 0x00035608
 *   malloc                                   <= FUN_00076d6c @ 0x00076d6c
 *   heap_free                                <= FUN_00076d7c @ 0x00076d7c
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_a7c9c                             @ 0x000a7c9c
 *   rodata_a89c8                             @ 0x000a89c8
 *   rodata_a8a6f                             @ 0x000a8a6f
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_whitelist_app_parse_buf                @ 0x20009fbc
 */
/* Reconstructed put_whitelist_app_from_app @ 0x35688  (parity: 300/300 trials, PROVEN) */

typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
typedef void (*fn2_t)(uint32_t, uint32_t);

extern void DEBUG_PRINT(uint32_t a, uint32_t b, uint32_t c);
extern void debug_print(void);
extern uint32_t parse_receiver_pack_pkcs7(uint32_t a, uint32_t b, uint32_t c);
extern uint32_t parse_whitelist_json(uint32_t a);
extern uint32_t verify_whitelist_json(uint32_t a);
extern uint32_t store_whitelist(void);
extern uint32_t malloc(uint32_t a);
extern void heap_free(uint32_t a);
extern void memset_bytes(uint32_t a, uint32_t b, uint32_t c);

void put_whitelist_app_from_app(uint32_t param_1, uint32_t param_2, uint32_t param_3, uint32_t param_4, uint32_t param_5)
{
    volatile uint32_t *piVar1 = (volatile uint32_t*)((unsigned long)&g_whitelist_app_parse_buf) /*=0x20009fbc*/;
    uint32_t iVar2;
    uint32_t format_string;

    if (*piVar1 == 0) {
        iVar2 = malloc(0x1800);
        *piVar1 = iVar2;
        if (iVar2 == 0) {
            if (*(volatile uint32_t*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                DEBUG_PRINT(((unsigned long)&rodata_a7c9c) /*=0xa7c9c*/, ((unsigned long)&rodata_a8a6f) /*=0xa8a6f*/, 0x1caUL);
            } else {
                debug_print();
            }
        } else {
            memset_bytes(iVar2, 0, 0x1800);
        }
    }
    if (*piVar1 == 0) goto LAB_call;

    iVar2 = parse_receiver_pack_pkcs7(*piVar1, param_3, param_4);
    *(uint8_t*)(param_5 + 1) = (uint8_t)iVar2;
    if (iVar2 != 0xc9) goto LAB_call;

    iVar2 = verify_whitelist_json(*piVar1);
    if (iVar2 == 0) {
        iVar2 = parse_whitelist_json(*piVar1);
        if (iVar2 == 0) {
            iVar2 = *(volatile uint32_t*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
            format_string = 0x000a89e8UL;
        } else {
            iVar2 = store_whitelist();
            if (iVar2 == 0) goto LAB_cleanup;
            iVar2 = *(volatile uint32_t*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
            format_string = ((unsigned long)&rodata_a89c8) /*=0xa89c8*/;
        }
        if (iVar2 == 0) {
            DEBUG_PRINT(format_string, 0, 0);
        } else {
            debug_print();
        }
        *(uint8_t*)(param_5 + 1) = 0xca;
    }

LAB_cleanup:
    heap_free(*piVar1);
    *piVar1 = 0;
LAB_call:
    ((fn2_t)(*(uint32_t*)(param_1 + 0xc)))(param_5, 2);
}
