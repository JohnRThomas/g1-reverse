/* readable reconstruction; identity: FUN_01033660 @ 0x01033660
 * public-name: FUN_01033660
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_esb_tx_buf_pool                        @ 0x210049d4
 *   g_esb_state                              @ 0x21004a94
 *   g_esb_pipe_pid_cnt                       @ 0x21006256
 *   g_net_radio_busy_flag                    @ 0x21006458
 *   g_esb_enabled_flag                       @ 0x21006459
 */
/* net-core FUN_01033660 @ 0x1033660  (parity 300 trials PROVEN) */
#include <stdint.h>
#include <cmsis_gcc.h>

static inline int isCurrentModePrivileged(void){return (__get_CONTROL()&1)==0;}
static inline int getBasePriority(void){return (int)__get_BASEPRI();}
static inline void setBasePriority(int p){__set_BASEPRI((unsigned)p);}
static inline void InstructionSynchronizationBarrier(int x){(void)x;__ISB();}

typedef unsigned char u8;
typedef unsigned int u32;
typedef int i32;

extern void FUN_0103b614(i32 a, u8* b, i32 c, i32 d, u32 e);
extern void FUN_01032c28(void);

#define A_01033790 0x21006459u
#define A_01033794 0x21004a94u
#define A_01033798 0x21004a60u
#define A_0103379c 0x21006256u
#define A_010337a0 0x210049d4u
#define A_010337a4 0x210049b4u
#define A_010337a8 0x21006458u

u32 FUN_01033660(u8 *param_1, u32 param_2, u32 param_3, u32 param_4)
{
    u32 iVar3 = A_01033798;
    u32 pcVar2 = A_01033794;
    if (*(volatile u8*)A_01033790 == 0) {
        return 0xfffffff3;
    }
    if (param_1 != 0) {
        if ( ((u8)(*param_1 - 1)) > 0xfa ||
             ( (*(volatile u8*)A_01033794 == 0) && (*(volatile u8*)(A_01033794+0x11) < *param_1) )
           ) {
            return 0xffffff86;
        }
        if (*(volatile u32*)(A_01033798+0x28) > 7) {
            return 0xfffffff4;
        }
        if (param_1[1] < 8) {
            u32 uVar6 = 0;
            int bVar1;
            u32 uVar4;
            i32 iVar7, iVar5, iVar8, iVar9;

            bVar1 = isCurrentModePrivileged();
            if (bVar1) uVar6 = (u32)getBasePriority();
            bVar1 = isCurrentModePrivileged();
            if (bVar1) {
                uVar4 = (u32)getBasePriority();
                if (uVar4 == 0 || uVar4 > 0x40) setBasePriority(0x40);
            }
            InstructionSynchronizationBarrier(0xf);
            if (*(volatile u8*)(A_01033794+1) == 0) {
                iVar7 = *(volatile i32*)(A_01033798 + *(volatile i32*)(A_01033798+0x20)*4);
                FUN_0103b614(iVar7, param_1, 0x100, *(volatile i32*)(A_01033798+0x20), param_4);
                iVar5 = A_0103379c;
                *(volatile u8*)(A_0103379c + param_1[1]) = (u8)((*(volatile u8*)(A_0103379c+param_1[1]) + 1) & 3);
                *(volatile u8*)(iVar7+4) = *(volatile u8*)(iVar5+param_1[1]);
                uVar4 = *(volatile u32*)(iVar3+0x20) + 1;
                if (uVar4 > 7) uVar4 = 0;
                *(volatile u32*)(iVar3+0x20) = uVar4;
                *(volatile i32*)(iVar3+0x28) = *(volatile i32*)(iVar3+0x28) + 1;
            } else {
                iVar7 = 0;
                iVar5 = A_010337a0;
                for (;;) {
                    if (*(volatile u8*)(iVar5+4) == 0) {
                        iVar7 = iVar7 * 0xc;
                        iVar9 = *(volatile i32*)(A_010337a0+iVar7);
                        iVar8 = A_010337a0 + iVar7;
                        *(volatile u8*)(iVar8+4) = 1;
                        *(volatile u32*)(iVar8+8) = 0;
                        FUN_0103b614(iVar9, param_1, 0x100, iVar7, param_4);
                        iVar5 = A_0103379c;
                        *(volatile u8*)(A_0103379c + param_1[1]) = (u8)((*(volatile u8*)(A_0103379c+param_1[1]) + 1) & 3);
                        iVar7 = A_010337a4;
                        *(volatile u8*)(iVar9+4) = *(volatile u8*)(iVar5+param_1[1]);
                        iVar5 = *(volatile i32*)(iVar7 + param_1[1]*4);
                        if (iVar5 == 0) {
                            *(volatile i32*)(iVar7 + param_1[1]*4) = iVar8;
                        } else {
                            do {
                                iVar7 = iVar5;
                                iVar5 = *(volatile i32*)(iVar7+8);
                            } while (iVar5 != 0);
                            *(volatile i32*)(iVar7+8) = iVar8;
                        }
                        *(volatile i32*)(iVar3+0x28) = *(volatile i32*)(iVar3+0x28) + 1;
                        goto done;
                    }
                    iVar7 = iVar7 + 1;
                    iVar5 = iVar5 + 0xc;
                    if (iVar7 == 8) break;
                }
            }
            done:;
            bVar1 = isCurrentModePrivileged();
            if (bVar1) setBasePriority((int)uVar6);
            InstructionSynchronizationBarrier(0xf);
            if ( (*(volatile u8*)(pcVar2+1) == 0 && *(volatile u8*)(pcVar2+0x10) == 0) && (*(volatile u8*)A_010337a8 == 0) ) {
                FUN_01032c28();
            }
            return 0;
        }
    }
    return 0xffffffea;
}
