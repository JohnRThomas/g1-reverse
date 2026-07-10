#include "g1_app_symbols.h"
/* named: random */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20006a30  g_ble_conn_ctx_ptr           
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed random @ 0x17f70  (parity: 300/300 trials, PROVEN) */
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

void random(unsigned param_1, unsigned char *param_2, uint param_3)
{
    volatile int *piVar1;
    volatile int *piVar2;
    unsigned char *puVar3;
    unsigned uVar4;
    uint uVar5, uVar6, uVar7, uVar8, uVar9;
    int iVar10, iVar12;
    long long lVar13;
    unsigned local_158;
    undefined1 auStack_154[16];
    unsigned local_144;
    undefined1 auStack_140[28];
    undefined1 local_124;
    undefined1 auStack_123[259];
    volatile int *dbg = (volatile int *)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
    unsigned *puVar11;

    local_144 = 0;
    memset_bytes(auStack_140, 0, 0x1a);
    memset_bytes(&local_124, 0, 0x101);
    puVar3 = FUN_00081526(param_1);
    switch (*puVar3) {
    case 0: uVar4 = "public" /*=0x9a1c8*/; break;
    case 1: uVar4 = "random" /*=0x9a1cf*/; break;
    case 2: uVar4 = "public-id" /*=0x9a1d6*/; break;
    case 3: uVar4 = "random-id" /*=0x9a1e0*/; break;
    default:
        snprintk(&local_158, 10, "0x%02x" /*=0xf5071*/);
        goto LAB_00017fb6;
    }
    strcpy(&local_158, uVar4);
LAB_00017fb6:
    piVar2 = (volatile int *)((uintptr_t)&g_log_level) /*=0x2000230c*/;
    piVar1 = (volatile int *)((uintptr_t)&g_ble_conn_ctx_ptr) /*=0x20006a30*/;
    uVar5 = (uint)(unsigned char)puVar3[1];
    uVar6 = (uint)(unsigned char)puVar3[2];
    uVar7 = (uint)(unsigned char)puVar3[3];
    uVar8 = (uint)(unsigned char)puVar3[4];
    uVar9 = (uint)(unsigned char)puVar3[5];
    puVar11 = &local_158;
    snprintk(&local_144, 0x1e, "%02X:%02X:%02X:%02X:%02X:%02X (%s)" /*=0x9a1ea*/, puVar3[6], uVar9, uVar8, uVar7, uVar6, uVar5, &local_158);
    if (0 < *piVar2) {
        uVar9 = (uint)*param_2;
        uVar8 = (uint)param_2[1];
        uVar7 = (uint)param_2[2];
        uVar6 = (uint)param_2[3];
        uVar5 = (uint)param_2[4];
        puVar11 = (unsigned *)(uint)param_2[5];
        if (*dbg == 0) {
            DEBUG_PRINT("%s(): **Received data from: %s, len=%d,cmd 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x,receiver_thd_is_running is %d\n" /*=0x9a20d*/, "bt_receive_cb" /*=0x9a2bf*/, &local_144, param_3, uVar9, uVar8, uVar7, uVar6, uVar5, puVar11,
                        (uint)*(unsigned char *)(*piVar1 + 0x248));
        } else {
            debug_print(0);
        }
    }
    iVar12 = *piVar1;
    lVar13 = thunk_FUN_00074f68();
    iVar10 = *piVar1;
    *(volatile uint *)(iVar12 + 0x368) =
        (uint)(lVar13 * 1000) >> 0xf | (int)((unsigned long long)(lVar13 * 1000) >> 0x20) * ((uintptr_t)&rodata_20000) /*=0x20000*/;
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
        local_158 = 0;
        memset_bytes(auStack_154, 0, 0x10);
        if (*param_2 == 0x18) {
            uVar4 = get_device_info();
            set_shutdown_flag(uVar4, 0);
            *((unsigned char *)&local_158 + 1) = 0xc9;
            (*(void (**)(void *, int))(*piVar1 + 0xc))(&local_158, 0x14);
            return;
        }
        if (param_3 < 0x101) {
            local_124 = (undefined1)param_3;
            memset_bytes(auStack_123, 0, 0x100);
            memcpy(auStack_123, param_2, param_3);
            enqueue_bt_data(auStack_123, param_3 & 0xff);
            if (*piVar2 < 1) return;
            if (*dbg != 0) {
                debug_print(0);
                return;
            }
            DEBUG_PRINT("%s(): enqueue because busy\n" /*=0x9a295*/, "bt_receive_cb" /*=0x9a2bf*/);
            return;
        }
        if (*dbg == 0) {
            uVar4 = 0x59;
LAB_000180e2:
            DEBUG_PRINT("[%s-%d]len is %d, too large ! \n" /*=0x9a275*/, "bt_receive_cb" /*=0x9a2b1*/, uVar4, param_3, uVar9, uVar8, uVar7, uVar6, uVar5, puVar11);
            return;
        }
        uVar4 = 0x59;
LAB_000180d4:
        debug_print("[%s-%d]len is %d, too large ! \n" /*=0x9a275*/, "bt_receive_cb" /*=0x9a2b1*/, uVar4, param_3);
    }
    return;
}

