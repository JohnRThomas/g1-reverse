/* Reconstructed FUN_00017f70 @ 0x17f70  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
typedef unsigned char undefined1;
typedef unsigned undefined4;
extern void DEBUG_PRINT(unsigned, ...);
extern unsigned FUN_000167a8(void);
extern void FUN_00017eec(void *a, uint b);
extern void FUN_00019c70(unsigned, ...);
extern void FUN_00072880(int a);
extern void FUN_0007cbfe(unsigned a, int b);
extern void FUN_0007ddbe(void *a, int b, unsigned c, ...);
extern void FUN_00081526_dummy(void);
extern unsigned char *FUN_00081526(unsigned a);
extern void FUN_00086c04(void *a, void *b, uint c);
extern void FUN_00086c78(void *a, int b, int c);
extern void FUN_00086fee(void *a, unsigned b);
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

void FUN_00017f70(unsigned param_1, unsigned char *param_2, uint param_3)
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
    volatile int *dbg = (volatile int *)0x20007554;
    unsigned *puVar11;

    log_record.header = 0;
    FUN_00086c78(log_record.text, 0, sizeof(log_record.text));
    FUN_00086c78(&forwarding, 0, sizeof(forwarding));
    puVar3 = FUN_00081526(param_1);
    switch (*puVar3) {
    case 0: uVar4 = 0x9a1c8; break;
    case 1: uVar4 = 0x9a1cf; break;
    case 2: uVar4 = 0x9a1d6; break;
    case 3: uVar4 = 0x9a1e0; break;
    default:
        FUN_0007ddbe(&request_name, 10, 0xf5071);
        goto LAB_00017fb6;
    }
    FUN_00086fee(&request_name, uVar4);
LAB_00017fb6:
    piVar2 = (volatile int *)0x2000230c;
    piVar1 = (volatile int *)0x20006a30;
    uVar5 = (uint)(unsigned char)puVar3[1];
    uVar6 = (uint)(unsigned char)puVar3[2];
    uVar7 = (uint)(unsigned char)puVar3[3];
    uVar8 = (uint)(unsigned char)puVar3[4];
    uVar9 = (uint)(unsigned char)puVar3[5];
    puVar11 = &request_name.word;
    FUN_0007ddbe(&log_record, 0x1e, 0x9a1ea, puVar3[6], uVar9, uVar8, uVar7, uVar6, uVar5, &request_name);
    if (0 < *piVar2) {
        uVar9 = (uint)*param_2;
        uVar8 = (uint)param_2[1];
        uVar7 = (uint)param_2[2];
        uVar6 = (uint)param_2[3];
        uVar5 = (uint)param_2[4];
        puVar11 = (unsigned *)(uint)param_2[5];
        if (*dbg == 0) {
            DEBUG_PRINT(0x9a20d, 0x9a2bf, &log_record, param_3, uVar9, uVar8, uVar7, uVar6, uVar5, puVar11,
                        (uint)*(unsigned char *)(*piVar1 + 0x248));
        } else {
            FUN_00019c70(0);
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
            FUN_00086c04(*(void **)(iVar10 + 0x254), param_2, param_3);
            FUN_00086c78((void *)(*(int *)(iVar10 + 0x254) + param_3), 0, 0x14 - param_3);
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
            FUN_00086c04((void *)(iVar10 + 600), param_2, param_3);
            *(volatile uint *)(iVar10 + 0x358) = param_3;
        }
        *(volatile unsigned *)(iVar10 + 0x35c) = 1;
        FUN_00072880(iVar10 + 0x218);
    } else {
        request_name.word = 0;
        FUN_00086c78(request_name.tail, 0, sizeof(request_name.tail));
        if (*param_2 == 0x18) {
            uVar4 = FUN_000167a8();
            FUN_0007cbfe(uVar4, 0);
            ((unsigned char *)&request_name)[1] = 0xc9;
            (*(void (**)(void *, int))(*piVar1 + 0xc))(&request_name, sizeof(request_name));
            return;
        }
        if (param_3 < 0x101) {
            forwarding.length = (undefined1)param_3;
            FUN_00086c78(forwarding.payload, 0, sizeof(forwarding.payload));
            FUN_00086c04(forwarding.payload, param_2, param_3);
            FUN_00017eec(forwarding.payload, param_3 & 0xff);
            if (*piVar2 < 1) return;
            if (*dbg != 0) {
                FUN_00019c70(0);
                return;
            }
            DEBUG_PRINT(0x9a295, 0x9a2bf);
            return;
        }
        if (*dbg == 0) {
            uVar4 = 0x59;
LAB_000180e2:
            DEBUG_PRINT(0x9a275, 0x9a2b1, uVar4, param_3, uVar9, uVar8, uVar7, uVar6, uVar5, puVar11);
            return;
        }
        uVar4 = 0x59;
LAB_000180d4:
        FUN_00019c70(0x9a275, 0x9a2b1, uVar4, param_3);
    }
    return;
}
