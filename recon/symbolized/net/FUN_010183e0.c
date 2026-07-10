#include "g1_net_symbols.h"
/* net-core FUN_010183e0 @ 0x10183e0  (parity 300 trials PROVEN) */
extern void FUN_01020500(void);
extern void FUN_01016828(void) __attribute__((noreturn));
extern int FUN_01019aa0(void *a0, unsigned int a1, void *a2, unsigned int a3, unsigned int a4, unsigned int a5, int a6, unsigned int a7);
extern int FUN_01017018(unsigned int a0, unsigned int a1);
extern int FUN_0100aa3c(unsigned int a0, void *a1, unsigned int a2, unsigned int a3);
extern void FUN_01017658(void *a0, void *a1, void *a2, void *a3);
extern void FUN_01019660(void);

unsigned int FUN_010183e0(char *param_1)
{
    char cVar1;
    unsigned char bVar2;
    unsigned char uVar3;
    unsigned char uVar4;
    int iVar5;
    int iVar6;
    unsigned int uVar7;
    unsigned char uVar8;
    unsigned int uVar9;
    unsigned char bVar10;
    char local_1b;
    char local_1a[2];

    iVar6 = ((uintptr_t)&g_sdc_conn_ctx) /*=0x21000f90*/;
    if (*(volatile char *)(((uintptr_t)&g_sdc_conn_ctx) /*=0x21000f90*/ + 0x57) == 0) {
LAB_01018406:
        FUN_01020500();
        return 5;
    }
    if (*(volatile char *)(((uintptr_t)&g_sdc_conn_ctx) /*=0x21000f90*/ + 0x82) == 0) {
        if (*(volatile char *)(((uintptr_t)&g_sdc_conn_ctx) /*=0x21000f90*/ + 0x83) == 0) goto LAB_01018406;
        cVar1 = *param_1;
    } else {
        cVar1 = *param_1;
    }
    if (cVar1 != 1) {
        if (cVar1 == 2) {
            FUN_01020500();
            if (*(volatile char *)(iVar6 + 0x54) == 3) return 5;
            if ((param_1[1] & 0x18) != 0x18) return 5;
            cVar1 = *(volatile char *)((uintptr_t)&g_net_ble_pending_channel_idx) /*=0x2100001c*/;
            if (cVar1 != 0x7f) {
                uVar8 = *(volatile unsigned char *)(iVar6 + 0x79);
                uVar3 = *(volatile unsigned char *)(iVar6 + 0x8f);
                *(volatile char *)((uintptr_t)&g_net_ble_pending_channel_idx) /*=0x2100001c*/ = 0x7f;
                iVar5 = FUN_01019aa0(param_1, 0xff, (void*)((uintptr_t)&g_net_ll_event_scratch_buf) /*=0x21000fd6*/, *(volatile unsigned char *)(iVar6 + 0xb9), uVar3, uVar8, (int)cVar1, 0);
                if (iVar5 == 0) return 5;
                uVar8 = 2;
LAB_0101854a:
                iVar5 = FUN_01017018(1, *(unsigned int *)(param_1 + 0x18));
                if (iVar5 == 0) return 5;
                *(volatile unsigned char *)(iVar6 + 0x88) = uVar8;
                return 3;
            }
        } else {
            if (cVar1 != 0) goto LAB_01018406;
            FUN_01020500();
            if (*(volatile char *)(iVar6 + 0x54) == 3) return 5;
            bVar2 = (unsigned char)param_1[1];
            if ((bVar2 & 0x10) == 0) uVar7 = 1; else uVar7 = 8;
            if ((uVar7 & (unsigned int)(unsigned char)~bVar2) != 0) return 5;
            local_1b = 0;
            local_1a[0] = 0;
            local_1a[1] = 0;
            if (*(unsigned int *)(param_1 + 8) == 0) {
                bVar10 = 0xff;
            } else {
                FUN_01017658(param_1, local_1a, &local_1b, local_1a + 1);
                bVar10 = *(volatile unsigned char *)(iVar6 + 0x45);
                if (local_1b == 0) {
                    iVar5 = FUN_0100aa3c(bVar10, (void*)((uintptr_t)&g_net_ll_event_scratch_buf) /*=0x21000fd6*/, (unsigned char)param_1[0x12], *(unsigned int *)(param_1 + 8));
                    if (iVar5 == 0) {
                        if (1 < (unsigned char)(*(volatile unsigned char *)(iVar6 + 0x55) - 2)) return 5;
                        if (local_1a[0] == 0) return 5;
                        if (local_1b != 0) return 5;
                        bVar10 = 0xfe;
                    }
                } else {
                    bVar10 = bVar10 | 2;
                }
            }
            iVar5 = (int)*(volatile char *)((uintptr_t)&g_net_ble_pending_channel_idx) /*=0x2100001c*/;
            if ((int)((unsigned int)bVar2 << 0x1b) < 0) {
                if (iVar5 != 0x7f) {
                    uVar3 = *(volatile unsigned char *)(iVar6 + 0x79);
                    uVar8 = 0;
                    uVar4 = *(volatile unsigned char *)(iVar6 + 0x8f);
                    *(volatile char *)((uintptr_t)&g_net_ble_pending_channel_idx) /*=0x2100001c*/ = 0x7f;
                    iVar5 = FUN_01019aa0(param_1, bVar10, (void*)((uintptr_t)&g_net_ll_event_scratch_buf) /*=0x21000fd6*/, *(volatile unsigned char *)(iVar6 + 0xb9), uVar4, uVar3, iVar5, 0);
                    if (iVar5 == 0) return 5;
                    goto LAB_0101854a;
                }
            } else if (iVar5 != 0x7f) {
                *(volatile char *)((uintptr_t)&g_net_ble_pending_channel_idx) /*=0x2100001c*/ = 0x7f;
                uVar9 = 0;
                if (*(volatile char *)(iVar6 + 0x70) != 5) {
                    if (*(volatile char *)(iVar6 + 0x70) == 8) uVar9 = 3; else uVar9 = 1;
                }
                iVar6 = FUN_01019aa0(param_1, bVar10, (void*)((uintptr_t)&g_net_ll_event_scratch_buf) /*=0x21000fd6*/, *(volatile unsigned char *)(iVar6 + 0xb9), *(volatile unsigned char *)(iVar6 + 0x8f), *(volatile unsigned char *)(iVar6 + 0x79), iVar5, uVar9);
                if (iVar6 != 0) {
                    FUN_01019660();
                    return 5;
                }
                return 5;
            }
        }
        goto LAB_0101867a;
    }
    FUN_01020500();
    if (*(volatile char *)(iVar6 + 0xb9) == 2) {
        if ((param_1[1] & 0x19) != 0x19) return 5;
    } else if ((param_1[1] & 0x18) != 0x18) return 5;
    if (*(volatile char *)(iVar6 + 0x54) == 3) {
        if (*(unsigned int *)(param_1 + 4) != 0) {
            iVar5 = FUN_0100aa3c(*(volatile unsigned char *)(iVar6 + 0x90), (void*)(((uintptr_t)&g_net_link_ctx_field_buf) /*=0x21000fec*/ + 0x2d), *(volatile unsigned char *)(iVar6 + 0x5b), 0);
            if (*(volatile char *)(iVar6 + 0x56) != 1) {
                if (*(volatile char *)(iVar6 + 0x56) != 0) return 5;
                if ((iVar5 == 0) && (*(volatile char *)(iVar6 + 0x78) != *(volatile char *)(iVar6 + 0x7b))) return 5;
            }
        }
        if (*(unsigned int *)(param_1 + 8) != 0) return 5;
        if ((*(volatile unsigned char *)(*(unsigned int *)(param_1 + 0x18) + 2) & 0xe0) == 0) {
            cVar1 = *(volatile char *)(iVar6 + 0x7e);
        } else {
            if ((*(volatile unsigned char *)(*(unsigned int *)(param_1 + 0x18) + 2) & 0xe0) != 0x40) goto LAB_01018442;
            cVar1 = *(volatile char *)(iVar6 + 0x7f);
        }
        if (cVar1 == 0) return 5;
    }
LAB_01018442:
    cVar1 = *(volatile char *)((uintptr_t)&g_net_ble_pending_channel_idx) /*=0x2100001c*/;
    if (cVar1 != 0x7f) {
        uVar8 = *(volatile unsigned char *)(iVar6 + 0x79);
        *(volatile char *)((uintptr_t)&g_net_ble_pending_channel_idx) /*=0x2100001c*/ = 0x7f;
        iVar5 = FUN_01019aa0(param_1, 0xff, (void*)((uintptr_t)&g_net_ll_event_scratch_buf) /*=0x21000fd6*/, *(volatile unsigned char *)(iVar6 + 0xb9), *(volatile unsigned char *)(iVar6 + 0x8f), uVar8, (int)cVar1, 0);
        if (iVar5 == 0) return 5;
        iVar5 = FUN_01017018(1, *(unsigned int *)(param_1 + 0x18));
        if (iVar5 != 0) {
            *(volatile unsigned char *)(iVar6 + 0x88) = 1;
            return 3;
        }
        return 5;
    }
LAB_0101867a:
    FUN_01016828();
}

