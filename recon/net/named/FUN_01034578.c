/* readable reconstruction; identity: FUN_01034578 @ 0x01034578
 * public-name: FUN_01034578
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_01039bb0 @ 0x01039bb0
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103e66f                           @ 0x0103e66f
 *   g_sdc_res_pool_slot_tbl                  @ 0x210006a8
 *   g_net_conn_teardown_ctx_b                @ 0x2100071c
 */
/* net-core FUN_01034578 @ 0x1034578  (parity 300 trials PROVEN) */

extern unsigned int FUN_010344a8(void);
extern int FUN_01034368(unsigned int);
extern void assert_print(unsigned int, unsigned int, unsigned int);
extern void assert_post_action(unsigned int, unsigned int) __attribute__((noreturn));

void FUN_01034578(void)
{
    unsigned int iVar3 = FUN_010344a8();
    volatile unsigned short *base = (volatile unsigned short*)0x210006a8;
    unsigned int idx = iVar3 + 8;
    unsigned short uVar1 = base[idx];
    if ((int)((unsigned int)uVar1 << 0x17) < 0) {
        unsigned int uVar5 = ((unsigned int)uVar1 >> 9) & 0xF;
        base[idx] = uVar1 & 0xe0ff;
        unsigned int uVar2 = 0x2100071c;
        unsigned int pidx = 8;
        int i;
        for (i = 0; i < 0x30; i++) {
            unsigned short v = base[pidx];
            if ((v & 0x100) != 0 && uVar5 == (((unsigned int)v >> 9) & 0xF)) {
                return;
            }
            pidx++;
        }
        *(volatile unsigned int*)((char*)base + uVar5 * 8) = 0;
        int iVar4 = FUN_01034368(uVar2);
        if (iVar4 != (int)0x0bad0000) {
            assert_print(0x103d2a7, 0x103e66f, 0x15f);
            assert_post_action(0x103e66f, 0x15f);
        }
    }
}
