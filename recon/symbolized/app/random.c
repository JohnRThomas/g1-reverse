#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00017f70 @ 0x00017f70
 * public-name: random
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   enqueue_bt_data                          <= FUN_00017eec @ 0x00017eec
 *   random                                   <= FUN_00017f70 @ 0x00017f70
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   set_shutdown_flag                        <= FUN_0007cbfe @ 0x0007cbfe
 *   snprintk                                 <= FUN_0007ddbe @ 0x0007ddbe
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 *   strcpy                                   <= FUN_00086fee @ 0x00086fee
 * address symbols (name @ address):
 *   rodata_9a1c8                             @ 0x0009a1c8
 *   rodata_9a1cf                             @ 0x0009a1cf
 *   rodata_9a1d6                             @ 0x0009a1d6
 *   rodata_9a1e0                             @ 0x0009a1e0
 *   rodata_9a1ea                             @ 0x0009a1ea
 *   rodata_9a20d                             @ 0x0009a20d
 *   rodata_9a275                             @ 0x0009a275
 *   rodata_9a295                             @ 0x0009a295
 *   rodata_9a2b1                             @ 0x0009a2b1
 *   rodata_9a2bf                             @ 0x0009a2bf
 *   rodata_f5071                             @ 0x000f5071
 *   g_log_level                              @ 0x2000230c
 *   g_ble_conn_ctx_ptr                       @ 0x20006a30
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed FUN_00017f70 @ 0x17f70  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
typedef unsigned char undefined1;
typedef unsigned undefined4;
extern void DEBUG_PRINT(unsigned, ...);
extern unsigned get_device_info(void);
extern void enqueue_bt_data(void *a, uint b);
extern void debug_print(unsigned, ...);
extern void FUN_00072880(int a);
extern void set_shutdown_flag(unsigned a, int b);
extern void snprintk(void *a, int b, unsigned c, ...);
extern void FUN_00081526_dummy(void);
extern unsigned char *FUN_00081526(unsigned a);
extern void memcpy(void *a, void *b, uint c);
extern void memset_bytes(void *a, int b, int c);
extern void strcpy(void *a, unsigned b);
extern long long thunk_FUN_00074f68(void);

struct request_name_record {
    unsigned word;
    unsigned char tail[16];
};

struct request_log_record {
    unsigned header;
    unsigned char text[26];
};

struct forwarding_packet {
    unsigned char length;
    unsigned char payload[256];
};

void random(unsigned param_1, unsigned char *param_2, uint param_3)
{
    volatile int *piVar1;
    volatile int *piVar2;
    unsigned char *puVar3;
    unsigned uVar4;
    uint uVar5, uVar6, uVar7, uVar8, uVar9;
    int iVar10, iVar12;
    long long lVar13;
    struct request_name_record request_name;
    struct request_log_record log_record;
    struct forwarding_packet forwarding;
    volatile int *dbg = (volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
    unsigned *puVar11;

    log_record.header = 0;
    memset_bytes(log_record.text, 0, sizeof(log_record.text));
    memset_bytes(&forwarding, 0, sizeof(forwarding));
    puVar3 = FUN_00081526(param_1);
    switch (*puVar3) {
    case 0: uVar4 = ((unsigned long)&rodata_9a1c8) /*=0x9a1c8*/; break;
    case 1: uVar4 = ((unsigned long)&rodata_9a1cf) /*=0x9a1cf*/; break;
    case 2: uVar4 = ((unsigned long)&rodata_9a1d6) /*=0x9a1d6*/; break;
    case 3: uVar4 = ((unsigned long)&rodata_9a1e0) /*=0x9a1e0*/; break;
    default:
        snprintk(&request_name, 10, ((unsigned long)&rodata_f5071) /*=0xf5071*/);
        goto LAB_00017fb6;
    }
    strcpy(&request_name, uVar4);
LAB_00017fb6:
    piVar2 = (volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/;
    piVar1 = (volatile int *)((unsigned long)&g_ble_conn_ctx_ptr) /*=0x20006a30*/;
    uVar5 = (uint)(unsigned char)puVar3[1];
    uVar6 = (uint)(unsigned char)puVar3[2];
    uVar7 = (uint)(unsigned char)puVar3[3];
    uVar8 = (uint)(unsigned char)puVar3[4];
    uVar9 = (uint)(unsigned char)puVar3[5];
    puVar11 = &request_name.word;
    snprintk(&log_record, 0x1e, ((unsigned long)&rodata_9a1ea) /*=0x9a1ea*/, puVar3[6], uVar9, uVar8, uVar7, uVar6, uVar5, &request_name);
    if (0 < *piVar2) {
        uVar9 = (uint)*param_2;
        uVar8 = (uint)param_2[1];
        uVar7 = (uint)param_2[2];
        uVar6 = (uint)param_2[3];
        uVar5 = (uint)param_2[4];
        puVar11 = (unsigned *)(uint)param_2[5];
        if (*dbg == 0) {
            DEBUG_PRINT(((unsigned long)&rodata_9a20d) /*=0x9a20d*/, ((unsigned long)&rodata_9a2bf) /*=0x9a2bf*/, &log_record, param_3, uVar9, uVar8, uVar7, uVar6, uVar5, puVar11,
                        (uint)*(unsigned char *)(*piVar1 + 0x248));
        } else {
            debug_print(0);
        }
    }
    iVar12 = *piVar1;
    lVar13 = thunk_FUN_00074f68();
    iVar10 = *piVar1;
    *(volatile uint *)(iVar12 + 0x368) =
        (uint)(lVar13 * 1000) >> 0xf | (int)((unsigned long long)(lVar13 * 1000) >> 0x20) * 0x20000;
    if ((*(volatile char *)(iVar10 + 0x248) == '\0') && (*(volatile int *)(iVar10 + 0x220) == 0)) {
        iVar10 = *piVar1;
        if (param_3 < 0x15) {
            memcpy(*(void **)(iVar10 + 0x254), param_2, param_3);
            memset_bytes((void *)(*(int *)(iVar10 + 0x254) + param_3), 0, 0x14 - param_3);
            *(volatile unsigned *)(iVar10 + 0x358) = 0;
            *(volatile uint *)(iVar10 + 0x360) = param_3;
        } else {
            if (0x100 < param_3) {
                if (*dbg == 0) {
                    uVar4 = 0x6a;
                    goto LAB_000180e2;
                }
                uVar4 = 0x6a;
                goto LAB_000180d4;
            }
            memcpy((void *)(iVar10 + 600), param_2, param_3);
            *(volatile uint *)(iVar10 + 0x358) = param_3;
        }
        *(volatile unsigned *)(iVar10 + 0x35c) = 1;
        FUN_00072880(iVar10 + 0x218);
    } else {
        request_name.word = 0;
        memset_bytes(request_name.tail, 0, sizeof(request_name.tail));
        if (*param_2 == 0x18) {
            uVar4 = get_device_info();
            set_shutdown_flag(uVar4, 0);
            ((unsigned char *)&request_name)[1] = 0xc9;
            (*(void (**)(void *, int))(*piVar1 + 0xc))(&request_name, sizeof(request_name));
            return;
        }
        if (param_3 < 0x101) {
            forwarding.length = (undefined1)param_3;
            memset_bytes(forwarding.payload, 0, sizeof(forwarding.payload));
            memcpy(forwarding.payload, param_2, param_3);
            enqueue_bt_data(forwarding.payload, param_3 & 0xff);
            if (*piVar2 < 1) return;
            if (*dbg != 0) {
                debug_print(0);
                return;
            }
            DEBUG_PRINT(((unsigned long)&rodata_9a295) /*=0x9a295*/, ((unsigned long)&rodata_9a2bf) /*=0x9a2bf*/);
            return;
        }
        if (*dbg == 0) {
            uVar4 = 0x59;
LAB_000180e2:
            DEBUG_PRINT(((unsigned long)&rodata_9a275) /*=0x9a275*/, ((unsigned long)&rodata_9a2b1) /*=0x9a2b1*/, uVar4, param_3, uVar9, uVar8, uVar7, uVar6, uVar5, puVar11);
            return;
        }
        uVar4 = 0x59;
LAB_000180d4:
        debug_print(((unsigned long)&rodata_9a275) /*=0x9a275*/, ((unsigned long)&rodata_9a2b1) /*=0x9a2b1*/, uVar4, param_3);
    }
    return;
}
