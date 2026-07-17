#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000560cc @ 0x000560cc
 * public-name: FUN_000560cc
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   net_buf_destroy                          <= FUN_00056080 @ 0x00056080
 *   net_buf_simple_push                      <= FUN_0005f518 @ 0x0005f518
 *   net_buf_simple_pull_5f558                <= FUN_0005f558 @ 0x0005f558
 *   mutex_lock_syscall_handler               <= FUN_00072908 @ 0x00072908
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   sys_slist_find_and_remove                <= FUN_0008137e @ 0x0008137e
 *   net_buf_get                              <= FUN_000836e8 @ 0x000836e8
 *   net_buf_simple_tailroom                  <= FUN_00083730 @ 0x00083730
 * address symbols (name @ address):
 *   g_ble_dev_state                          @ 0x20002000
 */
/* Reconstructed FUN_000560cc @ 0x560cc  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_000543c8(void);
extern void net_buf_destroy(void);
extern int net_buf_simple_push(void);
extern void net_buf_simple_pull_5f558(void);
extern void FUN_00072880(void);
extern int mutex_lock_syscall_handler(void);
extern void assert_post_action(void);
extern void printk(void);
extern void sys_slist_find_and_remove(void);
extern void FUN_000813ca(void);
extern int net_buf_simple_tailroom(void);
extern void FUN_00083740(void);
extern int net_buf_get(void);

#define S16(a) (*(volatile int16_t*)(a))
#define U16(a) (*(volatile uint16_t*)(a))
#define U32(a) (*(volatile uint32_t*)(a))
#define I32(a) (*(volatile int32_t*)(a))

unsigned FUN_000560cc(int param_1, int param_2, int param_3, unsigned param_4)
{
    int iVar2 = ((unsigned long)&g_ble_dev_state) /*=0x20002000*/;
    int iVar4;
    unsigned uVar8;
    int puVar9;
    int unaff_r10 = 0;

    iVar4 = (U16(iVar2 + 0x104) == 0) ? 0 : (iVar2 + 0x108);
    (void)iVar4;
    if (mutex_lock_syscall_handler() != 0) {
        return 0xffffff97;
    }
    if (param_3 == 0) {
        param_3 = net_buf_get();
    } else {
        unsigned local_2c = U16(iVar2 + 0x104);
        int iVar4b = param_3 + 0xc;
        unsigned uVar5 = (unsigned)net_buf_simple_tailroom();
        uint16_t uVar3;
        if (uVar5 <= local_2c) {
            uVar3 = (uint16_t)net_buf_simple_tailroom();
        } else {
            uVar3 = U16(iVar2 + 0x104);
        }
        (void)uVar3;
        FUN_00083740();
        net_buf_simple_pull_5f558();
    }
    puVar9 = (int)U32(param_3 + 0x18);
    if (*(volatile int8_t*)(param_1 + 0xd) == 7) {
        if (puVar9 == 0) {
            int v = (int)U32(param_1 + 0x18);
            int iVar4c;
            if (v == 0) {
                unaff_r10 = param_1 + 0x1c;
                iVar4c = I32(param_1 + 0x1c);
            } else {
                unaff_r10 = v + 0xc;
                iVar4c = I32(v + 0xc);
            }
            I32(unaff_r10) = iVar4c + 1;
        } else {
            U32(puVar9) = 0;
            if (U32(param_1 + 0x18) == 0) {
                U32(param_1 + 0x14) = (uint32_t)puVar9;
                U32(param_1 + 0x18) = (uint32_t)puVar9;
            } else {
                U32(U32(param_1 + 0x18)) = (uint32_t)puVar9;
                U32(param_1 + 0x18) = (uint32_t)puVar9;
            }
        }
        int puVar6 = net_buf_simple_push();
        U16(puVar6) = (uint16_t)(U16(param_1) | ((param_4 & 0xfd) << 0xc));
        U16(puVar6 + 2) = (uint16_t)(S16(param_3 + 0x10) - 4);
        *(volatile uint8_t*)(param_3 + 0x18) = 2;
        if (FUN_000543c8() == 0) {
            return 0;
        }
        FUN_000813ca();
        if (puVar9 == 0) {
            if (I32(unaff_r10) == 0) {
                printk();
                assert_post_action();
            }
            I32(unaff_r10) = I32(unaff_r10) - 1;
        } else {
            sys_slist_find_and_remove();
        }
        uVar8 = 0xfffffffb;
    } else {
        uVar8 = 0xffffff80;
    }
    FUN_00072880();
    if (puVar9 != 0) {
        U32(param_3 + 0x18) = 0;
        net_buf_destroy();
    }
    return uVar8;
}
