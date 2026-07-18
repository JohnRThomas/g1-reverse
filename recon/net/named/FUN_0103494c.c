/* readable reconstruction; identity: FUN_0103494c @ 0x0103494c
 * public-name: FUN_0103494c
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_01039bb0 @ 0x01039bb0
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103e66f                           @ 0x0103e66f
 *   g_sdc_res_pool_slot_tbl                  @ 0x210006a8
 */
/* net-core FUN_0103494c @ 0x103494c  (parity 300 trials PROVEN) */

extern int FUN_010344d4(void);
extern unsigned long long FUN_010344a8(unsigned int a);
extern void assert_print(unsigned int a, unsigned int b, unsigned int c);
extern void assert_post_action(unsigned int a, unsigned int b);

unsigned int FUN_0103494c(unsigned int param_1, int param_2)
{
    int iVar1;
    unsigned int uVar2;
    unsigned long long uVar3;
    unsigned int base;
    unsigned char *ptr;
    unsigned short hw;
    if (param_2 == 0) {
        assert_print(0x0103d2a7, 0x0103e66f, 0x265);
        assert_post_action(0x0103e66f, 0x265);
        return 0;
    }
    iVar1 = FUN_010344d4();
    uVar2 = 0x0bad0004;
    if (iVar1 != 0) {
        uVar3 = FUN_010344a8(param_1);
        uVar2 = 0x0bad0000;
        base = 0x210006a8;
        ptr = (unsigned char *)(unsigned int)(uVar3 >> 32);
        hw = *(unsigned short *)(base + ((unsigned int)uVar3 + 8) * 2);
        *ptr = (unsigned char)(hw >> 0xd);
    }
    return uVar2;
}
