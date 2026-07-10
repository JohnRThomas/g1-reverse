/* named: img_mgmt_state_read_521fc */
/* Reconstructed img_mgmt_state_read_521fc @ 0x521fc  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
typedef unsigned char undefined1;
typedef unsigned undefined4;
extern void FUN_0004d944(unsigned a, unsigned b, void *c, unsigned d);
extern int smp_add_cmd_err(int a, int b, uint c);
extern uint FUN_00051870(int a, int b, int c, int d);
extern uint img_mgmt_impl_write_image_data(void *a, void *b);
extern void FUN_00051fe4(void);
extern unsigned FUN_00052000(unsigned a);
extern void img_mgmt_read_hash_and_flags(int a, int b, void *c, ...);
extern int FUN_00080872(int a, void *b, int c, void *d);
extern void FUN_00086c1e(int a, unsigned b, int c, int d);
extern void memset_bytes(void *a, int b, int c);

unsigned img_mgmt_state_read_521fc(int param_1)
{
    volatile unsigned *puVar1;
    uint uVar2;
    int iVar3, iVar5;
    unsigned uVar4;
    unsigned local_108, local_104;
    uint uStack_100;
    unsigned local_f4;
    unsigned local_f0[2];
    int local_e8;
    unsigned local_e4;
    char local_e0;
    undefined1 auStack_d8[4];
    int local_d4[3];
    int local_c8;
    unsigned local_c4;
    int local_c0;
    undefined1 auStack_bc[4];
    undefined1 auStack_b8[32];
    /* config struct (args to oracle; values irrelevant) */
    unsigned cfg[64];

    iVar3 = *(volatile int *)(param_1 + 4);
    iVar5 = *(volatile int *)(param_1 + 8);
    local_f4 = 0;
    memset_bytes(auStack_d8, 0, 0x20);
    local_d4[0] = -1;
    local_d4[1] = -1;
    (void)cfg;
    iVar3 = FUN_00080872(iVar3 + 4, cfg, 6, &local_f4);
    if (iVar3 != 0) {
        return 3;
    }
    uVar2 = img_mgmt_impl_write_image_data(auStack_d8, local_f0);
    iVar3 = local_d4[0];
    puVar1 = (volatile unsigned *)0x2000ab7c;
    uVar4 = 0;
    if (uVar2 == 0) {
        if (local_e0 == '\0') {
            uVar4 = FUN_00052000(*(volatile unsigned *)(param_1 + 8));
            return uVar4;
        }
        puVar1[0] = local_e4;
        puVar1[2] = local_f0[0];
        if (local_d4[0] == 0) {
            puVar1[1] = 0;
            *(volatile char *)(puVar1 + 3) = (char)local_c0;
            FUN_00086c1e((int)puVar1 + 0xd, local_c4, local_c0, 0x23);
            memset_bytes((void *)(local_c0 + 0xd + (int)puVar1), 0, 0x20 - local_c0);
        }
        if (local_c8 == 0) {
            if (puVar1[2] == puVar1[1]) {
                img_mgmt_read_hash_and_flags(1, 0, auStack_b8);
            }
        } else {
            uVar2 = FUN_00051870(iVar3, local_d4[2], local_e8, local_c8 + puVar1[1] == puVar1[2]);
            if (uVar2 != 0) {
                local_104 = 0xf280b;
                local_108 = 3;
                uStack_100 = uVar2;
                FUN_0004d944(0x88208, 0x1840, &local_108, 0);
                goto LAB_00052300;
            }
            iVar3 = puVar1[1];
            puVar1[1] = iVar3 + local_e8;
            if (iVar3 + local_e8 == (int)puVar1[2]) {
                img_mgmt_read_hash_and_flags(1, 0, auStack_b8, 0);
                FUN_00052000(*(volatile unsigned *)(param_1 + 8));
                FUN_00051fe4();
                return 0;
            }
        }
        FUN_00052000(*(volatile unsigned *)(param_1 + 8));
    } else {
        local_104 = 0xf27eb;
        local_108 = 3;
        uStack_100 = uVar2;
        FUN_0004d944(0x88208, 0x1840, &local_108, 0);
LAB_00052300:
        iVar3 = smp_add_cmd_err(iVar5 + 4, 1, uVar2 & 0xffff);
        img_mgmt_read_hash_and_flags(1, 0, auStack_b8);
        FUN_00051fe4();
        if (iVar3 == 0) {
            uVar4 = 7;
        }
    }
    return uVar4;
}

