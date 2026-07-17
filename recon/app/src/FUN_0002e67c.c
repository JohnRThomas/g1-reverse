/* Reconstructed FUN_0002e67c @ 0x2e67c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
extern void DEBUG_PRINT(int,...);
extern int FUN_000167a8(void);
extern void FUN_00019c70(int, ...);
extern int FUN_0002e594(int a, void *b);
extern int FUN_0008638c(int a);

struct opt3001_init_frame {
    uint16_t register_value;
    uint16_t configuration;
    uint8_t payload[3];
    uint8_t reserved;
    uint8_t *data;
    uint32_t length;
    uint8_t type;
    uint8_t padding[3];
};

_Static_assert(sizeof(struct opt3001_init_frame) == 20,
               "option initialization frame layout");

unsigned FUN_0002e67c(int param_1)
{
    struct opt3001_init_frame local;
    int iVar5;
    uint uVar6;
    unsigned uVar4;
    volatile int *piVar1 = (volatile int *)0x2000230cUL;
    volatile int *piVar2 = (volatile int *)0x20007b6cUL;
    volatile int *dbg    = (volatile int *)0x20007554UL;
    volatile int *piVar3v= (volatile int *)0x200023fcUL;
    volatile unsigned char *flag8da1 = (volatile unsigned char *)0x20018da1UL;

    local.register_value = 0;
    if (param_1 == 0) {
        param_1 = FUN_000167a8();
        param_1 = param_1 + 0xf80;
    }
    *piVar2 = param_1;
    iVar5 = *piVar1;
    if (2 < iVar5) {
        if (*dbg == 0) DEBUG_PRINT(0xa3b3f, 0xa3d00);
        else FUN_00019c70(0x000a3b3fUL, 0x000a3d00UL);
    }
    iVar5 = FUN_0002e594(0x7e, &local.register_value);
    if (iVar5 == 0) {
        uVar6 = (uint)local.register_value;
        if (1 < *piVar1) {
            if (*dbg == 0) DEBUG_PRINT(0xa3b7a, 0xa3d00, uVar6);
            else FUN_00019c70(0x000a3b7aUL, 0x000a3d00UL, uVar6);
        }
        if (uVar6 == 0x5449) {
            iVar5 = FUN_0002e594(0x7f, &local.register_value);
            if (iVar5 != 0) {
                if (*piVar1 < 1) return 0xfffffffb;
                iVar5 = *dbg;
                uVar4 = 0xa3bb6;
                goto LAB_0002e6c8;
            }
            uVar6 = (uint)local.register_value;
            if (1 < *piVar1) {
                if (*dbg == 0) DEBUG_PRINT(0xa3bd6, 0xa3d00, uVar6);
                else FUN_00019c70(0x000a3bd6UL, 0x000a3d00UL, uVar6);
            }
            if (uVar6 == 0x3001) {
                iVar5 = FUN_0002e594(1, &local.configuration);
                if (iVar5 == 0) {
                    local.payload[1] =
                        (unsigned char)((local.configuration & 63999) >> 8) | 6;
                    local.payload[0] = 1;
                    local.payload[2] =
                        (unsigned char)(local.configuration & 63999);
                    iVar5 = FUN_0008638c(*piVar3v);
                    if (iVar5 == 0) {
                        if (*piVar1 < 1) return 0xfffffffb;
                        if (*dbg == 0) DEBUG_PRINT(0xa3af8, 0xa3cee);
                        else FUN_00019c70(0x000a3af8UL, 0x000a3ceeUL);
                    } else {
                        typedef int (*transfer_fn)(int, void *, int, int);
                        int controller = *piVar3v;
                        transfer_fn transfer = *(volatile transfer_fn*)(
                            *(volatile uint32_t*)(controller + 8) + 8);
                        local.data = local.payload;
                        local.length = 3;
                        local.type = 2;
                        iVar5 = transfer(controller, &local.data, 1, 0x45);
                        if (-1 < iVar5) {
                            if (*piVar2 != 0) {
                                *(int *)(*piVar2 + 0x10) = 1;
                            }
                            if (2 < *piVar1) {
                                if (*dbg == 0) DEBUG_PRINT(0xa3c68, 0xa3d00);
                                else FUN_00019c70(0x000a3c68UL,
                                                 0x000a3d00UL);
                            }
                            *flag8da1 = 1;
                            return 0;
                        }
                        if (*piVar1 < 1) return 0xfffffffb;
                        if (*dbg == 0) DEBUG_PRINT(0xa3c0c, 0xa3cee);
                        else FUN_00019c70(0x000a3c0cUL, 0x000a3ceeUL);
                    }
                }
                if (*piVar1 < 1) return 0xfffffffb;
                if (*dbg != 0) {
                    FUN_00019c70(0x000a3c2dUL, 0x000a3d00UL);
                    return 0xfffffffb;
                }
                DEBUG_PRINT(0xa3c2d, 0xa3d00);
                return 0xfffffffb;
            }
            if (*piVar1 < 1) return 0xffffff7a;
            iVar5 = *dbg;
            uVar4 = 0xa3bea;
        } else {
            if (*piVar1 < 1) return 0xffffff7a;
            iVar5 = *dbg;
            uVar4 = 0xa3b8e;
        }
        if (iVar5 == 0) DEBUG_PRINT(uVar4, 0xa3d00, uVar6);
        else FUN_00019c70(uVar4, 0x000a3d00UL, uVar6);
        return 0xffffff7a;
    }
    if (*piVar1 < 1) return 0xfffffffb;
    iVar5 = *dbg;
    uVar4 = 0xa3b5a;
LAB_0002e6c8:
    if (iVar5 == 0) DEBUG_PRINT(uVar4, 0xa3d00,
                               (uint)local.register_value);
    else FUN_00019c70(uVar4, 0x000a3d00UL,
                      (uint)local.register_value);
    return 0xfffffffb;
}
