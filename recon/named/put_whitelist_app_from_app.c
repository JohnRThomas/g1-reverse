/* named: put_whitelist_app_from_app */
/* globals referenced:
//   0x20007554  g_log_use_alt_sink           
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
    volatile uint32_t *piVar1 = (volatile uint32_t*)0x20009fbcUL;
    uint32_t iVar2;
    uint32_t format_string;

    if (*piVar1 == 0) {
        iVar2 = malloc(0x1800);
        *piVar1 = iVar2;
        if (iVar2 == 0) {
            if (*(volatile uint32_t*)0x20007554UL == 0) {
                DEBUG_PRINT(0x000a7c9cUL, 0x000a8a6fUL, 0x1caUL);
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
            iVar2 = *(volatile uint32_t*)0x20007554UL;
            format_string = 0x000a89e8UL;
        } else {
            iVar2 = store_whitelist();
            if (iVar2 == 0) goto LAB_cleanup;
            iVar2 = *(volatile uint32_t*)0x20007554UL;
            format_string = 0x000a89c8UL;
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

