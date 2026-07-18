/* readable reconstruction; identity: FUN_01034fa8 @ 0x01034fa8
 * public-name: FUN_01034fa8
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_01039bb0 @ 0x01039bb0
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103e73b                           @ 0x0103e73b
 *   g_net_gpiote_evt_handler_table           @ 0x21004af8
 */
/* net-core FUN_01034fa8 @ 0x1034fa8  (parity 300 trials PROVEN) */

extern int FUN_01034f24(void);
extern int assert_print(int, int, int);
extern void assert_post_action(int, int) __attribute__((noreturn));

int FUN_01034fa8(unsigned int *param_1, int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned char uVar1 = *((unsigned char*)param_1 + 4);
    int iVar5 = uVar1 * 0xc;
    volatile unsigned char *base = (volatile unsigned char*)0x21004af8;
    int iVar4;
    if (*(volatile unsigned char*)(base + iVar5 + 8) == 0) {
        *(volatile unsigned int*)(base + iVar5) = param_3;
        if (param_2 != 0) {
            *(volatile unsigned int*)(base + iVar5 + 4) = *(unsigned int*)(param_2 + 8);
            unsigned int uVar6 = *param_1;
            unsigned int uVar3c = 0x4100c000;
            int matched = (uVar6 == uVar3c) || (uVar6 == uVar3c + 0xc000) || (uVar6 == uVar3c + 0xd000);
            if (!matched || (*((unsigned char*)param_2 + 5) > 3)) {
                assert_print(0x103d2a7, 0x103e73b, 0x8e);
                assert_post_action(0x103e73b, 0x8e);
            }
            iVar4 = FUN_01034f24();
        } else {
            iVar4 = 0x0bad0000;
        }
        *(volatile unsigned char*)(base + iVar5 + 8) = (iVar4 == (int)0x0bad0000) ? 1 : 0;
    } else {
        iVar4 = 0x0bad0005;
    }
    return iVar4;
}
