/* readable reconstruction; identity: FUN_0101e6ac @ 0x0101e6ac
 * public-name: FUN_0101e6ac
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 *   controller_interval_code_to_duration     <= FUN_0100d600 @ 0x0100d600
 *   controller_timing_state_reset            <= FUN_0101e274 @ 0x0101e274
 * address symbols (name @ address):
 *   rodata_103ec0a                           @ 0x0103ec0a
 *   g_net_ble_conn_create_ctx                @ 0x21000eac
 *   g_net_ble_conn_role_cfg                  @ 0x21001208
 *   g_net_bufpool_id_tag                     @ 0x21001225
 */
/* net-core FUN_0101e6ac @ 0x101e6ac  (parity 300 trials PROVEN) */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void sdc_assertion_fail(int,int);
extern int FUN_01009f58(u16,u16,u16,u8,u8);
extern int FUN_0100d14c(void*,int);
extern u32 controller_interval_code_to_duration(u16);
extern u32 FUN_0100f66c(void);
extern void FUN_0101bbc0(void*);
extern u32 FUN_0101ded0(u32,u32,int);
extern void controller_timing_state_reset(void*);
extern u32 FUN_0101e660(void*);
extern unsigned long long FUN_0101f8cc(void);
extern u32 FUN_01028256(void);

#define SRC1   0x0103ec0a          /* DAT_0101e818 */
#define CONST2 0x21001225u         /* DAT_0101e81c */
#define TBL2   0x21000eac          /* DAT_0101e820, r6 */
#define TBL3   0x21001208          /* DAT_0101e824, r7 */

unsigned int FUN_0101e6ac(unsigned short *param_1, unsigned short param_2, int param_3, int param_4)
{
    unsigned char *P = (unsigned char*)param_1;

    u32 uVar3 = *(volatile u32*)SRC1;
    u8 uVar1 = *(volatile u8*)(SRC1+4);
    int iVar8 = param_3;

    FUN_0100d14c(param_1, 0);

    *param_1 = param_2;
    *(volatile u32*)(P+0x310) = CONST2;

    u32 uVar4 = (u32)FUN_0101f8cc();
    unsigned char *puVar2 = (unsigned char*)TBL2;
    int bVar15 = (uVar4 & 0x20) == 0;
    u16 uVar13, uVar7 = (u16)iVar8;
    if (bVar15) {
        uVar13 = 0x1b;
    } else {
        uVar13 = *(volatile u16*)(TBL2+4);
        uVar7 = *(volatile u16*)(TBL2+2);
    }
    if (bVar15) *(volatile u16*)(P+0x56) = uVar13;
    if (!bVar15) *(volatile u16*)(P+0x56) = uVar7;
    *(volatile u16*)(P+0x58) = uVar13;

    unsigned long long f2 = FUN_0101f8cc();
    unsigned int extraout_r1 = (unsigned int)(f2 >> 32);

    if ((int)(extraout_r1 << 30) < 0) {
        struct {
            u32 mode;
            unsigned short *owner;
        } descriptor = {0, param_1};
        controller_timing_state_reset(&descriptor);
    }

    int iVarS = TBL3;
    char cVar12 = *(volatile char*)(TBL3+4);
    unsigned char *puVar9 = (unsigned char*)(TBL3+8);
    if (cVar12 != 0) cVar12 = 1;
    *(volatile char*)(P+0x73) = cVar12;

    u32 w1 = *(volatile u32*)(puVar9);
    u32 w2 = *(volatile u32*)(TBL3+0xc);
    u32 w3 = *(volatile u32*)(TBL3+0x10);
    u32 w4 = *(volatile u32*)(TBL3+0x14);
    *(volatile u32*)(P+0x7c) = w1;
    *(volatile u32*)(P+0x80) = w2;
    *(volatile u32*)(P+0x84) = w3;
    *(volatile u32*)(P+0x88) = w4;

    int iVar5 = FUN_01009f58(*param_1, *(volatile u16*)(puVar2+2), *(volatile u16*)(puVar2+4),
                              puVar2[0], puVar2[1]);
    if (iVar5 != 0) {
        sdc_assertion_fail(0x39, 0xffb);
        return 0;
    }

    u32 rc = FUN_01028256();
    *(volatile u32*)(P+0x18) = rc;
    if (param_4 != 0) {
        u32 t = FUN_0100f66c();
        *(volatile u32*)(P+0x20) = t & 0xffffffu;
    }

    u8 idx = *(volatile u8*)(param_3 + 0x4d);
    int p3 = param_3 + (unsigned)idx * 2;
    u32 uVar6a = controller_interval_code_to_duration(*(volatile u16*)(p3+0x24));
    u32 uVar4b = controller_interval_code_to_duration(*(volatile u16*)(p3+0x2a));
    u16 uVar7b;
    if (uVar4b < 0x1d4c) {
        uVar7b = 1000;
    } else {
        uVar4b = FUN_0101ded0(uVar6a, uVar4b, 0x4e2);
        uVar7b = 0x4e2;
    }
    *(volatile u32*)(P+0x14) = uVar4b;
    *(volatile u32*)(P+0x2e8) = uVar4b;
    *(volatile u16*)(P+0x2ec) = uVar7b;

    u32 uVar6b = *(volatile u32*)(puVar2+8);
    param_3 = param_3 + (unsigned)idx * 2;
    *(volatile u16*)(P+0x1c) = *(volatile u16*)(param_3+0x30);
    u16 uVar7c = *(volatile u16*)(param_3+0x36);
    *(volatile u32*)(P+0x30) = uVar6b;
    *(volatile u16*)(P+0x1e) = uVar7c;

    FUN_0101bbc0(param_1);

    *(volatile u32*)(P+0xce) = uVar3;
    *(volatile u8*)(P+0xd2) = uVar1;
    *(volatile u8*)(P+0x314) = 0xff;

    void (*cb)(void*, void*, int) = *(void(**)(void*,void*,int))(TBL3+0x24);
    if (cb != 0) {
        cb(param_1, P+0x162, 1);
    }

    u32 uVar6c = FUN_0101e660(param_1);
    u32 uVar4c = FUN_0100f66c();
    u32 uVar11 = uVar4c % 12 + 5;
    if (uVar11 < 9) {
        *(volatile char*)(P+0xd9) = (char)(uVar4c % 12) + 13;
    } else {
        *(volatile char*)(P+0xd9) = (char)uVar11;
    }
    FUN_0100d14c(param_1, 1);
    return uVar6c;
}
