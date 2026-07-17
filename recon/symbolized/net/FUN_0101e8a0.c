#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0101e8a0 @ 0x0101e8a0
 * public-name: FUN_0101e8a0
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 * address symbols (name @ address):
 *   g_net_ble_conn_create_ctx                @ 0x21000eac
 *   g_net_ble_conn_role_cfg                  @ 0x21001208
 */
/* net-core FUN_0101e8a0 @ 0x101e8a0  (parity 300 trials PROVEN) */
extern void sdc_assertion_fail(int,int);
extern int FUN_01009d64(int,int);
extern int FUN_01009f58(int,int,int,int,int,int);
extern int FUN_0101e274(void*);
extern int FUN_0101e660(int);
extern unsigned long long FUN_0101f8cc(void);

#define P1 ((unsigned long)&g_net_ble_conn_create_ctx) /*=0x21000eac*/   /* DAT_0101e944 */
#define P2 ((unsigned long)&g_net_ble_conn_role_cfg) /*=0x21001208*/   /* DAT_0101e948 */
#define B(a,off) (*(volatile unsigned char*)((a)+(off)))
#define H(a,off) (*(volatile unsigned short*)((a)+(off)))
#define W(a,off) (*(volatile unsigned int*)((a)+(off)))

int FUN_0101e8a0(int param_1, int param_2, int param_3, int param_4)
{
    unsigned long long c0 = FUN_0101f8cc();
    unsigned int uVar2 = (unsigned int)c0;
    int bVar10 = (uVar2 & 0x20) == 0;
    unsigned short uVar7, uVar5;
    if (bVar10) {
        uVar7 = 0x1b;
        uVar5 = 0x1b;
    } else {
        uVar7 = H(P1,4);
        uVar5 = H(P1,2);
    }
    if (bVar10) {
        H(param_1,0x56) = uVar7;
    } else {
        H(param_1,0x56) = uVar5;
    }
    H(param_1,0x58) = uVar7;

    unsigned long long c1 = FUN_0101f8cc();
    unsigned int r1v = (unsigned int)(c1 >> 32);
    if ((int)(r1v << 0x1e) < 0) {
        FUN_0101e274(0);
    }

    int bVar10_2 = B(P2,4) != 0;
    B(param_1,0x73) = (unsigned char)(bVar10_2 ? 1 : 0);
    W(param_1,0x7c) = W(P2,8);
    W(param_1,0x80) = W(P2,0xc);
    W(param_1,0x84) = W(P2,0x10);
    W(param_1,0x88) = W(P2,0x14);
    W(param_1,0x30) = W(P1,8);
    unsigned int uVar4 = bVar10_2 ? 1000u : 0x1d4cu;
    W(param_1,0x14) = uVar4;

    int iVar3call = FUN_0101e660(param_1);
    int ret_r6 = iVar3call;
    if (iVar3call != 0) {
        int iVar3c = FUN_01009d64(H(param_1,0),1);
        if (iVar3c == 0) return 9;
        sdc_assertion_fail(0x39, 0x57d);
        /* falls through into shared block below with ret_r6 = iVar3call (nonzero) */
    }
    {
        int iVar3b;
        for (;;) {
            iVar3b = FUN_01009f58(H(param_1,0), H(param_1,2),
                                  H(param_1,4), B(param_1,0),
                                  B(param_1,1), 0);
            if (iVar3b == 0) {
                return ret_r6;
            }
            /* original: b(back) into the FUN_01008d00 call site with no link,
               which falls through again into this same FUN_01009f58 sequence --
               replicate the loop so call-index progression (and therefore any
               runaway/instruction-cap timeout) matches exactly. */
            sdc_assertion_fail(0x39, 0x588);
        }
    }
}
