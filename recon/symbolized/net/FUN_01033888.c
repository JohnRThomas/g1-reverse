#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01033888 @ 0x01033888
 * public-name: FUN_01033888
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_1033655                           @ 0x01033655
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103e3e0                           @ 0x0103e3e0
 *   g_net_radio_crc_scratch                  @ 0x21000684
 *   g_net_radio_irq_continuation_ptr         @ 0x210049a0
 *   g_net_radio_busy_flag                    @ 0x21006458
 *   REG_41008000                             @ 0x41008000
 */
/* net-core FUN_01033888 @ 0x1033888  (parity 300 trials PROVEN) */

typedef unsigned int uint;
extern void arch_irq_enable(unsigned int); /* FUN_0102eb2c */
extern void FUN_01032988(void);
extern void FUN_01033b18(unsigned int, unsigned int);
extern void assert_post_action(unsigned int, unsigned int); /* FUN_01039bb0 */
extern void assert_print(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int); /* FUN_01039bbe */

unsigned int FUN_01033888(void)
{
    volatile unsigned char * const pb = (volatile unsigned char *)((unsigned long)&g_net_radio_busy_flag) /*=0x21006458*/; /* DAT_01033940 */
    if (*pb != 0) {
        return 0xfffffff0u;
    }
    volatile unsigned int * const p4 = (volatile unsigned int *)REG_41008000 /*=0x41008000*/; /* DAT_01033944 */
    unsigned int uVar5 = (unsigned int)(*pb); /* bVar (=0 here) widened, matches r5 = zext(byte) */
    p4[0x308/4] = 0xffffffffu;
    p4[0x110/4] = uVar5;
    (void)p4[0x110/4]; /* read-back @ 0x41008110 (original 0x010338a6) */
    volatile unsigned int * const pgp = (volatile unsigned int *)((unsigned long)&g_net_radio_irq_continuation_ptr) /*=0x210049a0*/; /* DAT_0103394c */
    *pgp = ((unsigned long)&rodata_1033655) /*=0x1033655*/; /* DAT_01033948 */
    p4[0x200/4] = 0x117;
    p4[0x304/4] = 0x10;
    *pb = 4;
    volatile unsigned char * const pb2 = (volatile unsigned char *)((unsigned long)&g_net_radio_crc_scratch) /*=0x21000684*/; /* DAT_01033950 */
    p4[0x530/4] = (unsigned int)pb2[0x12];
    unsigned int uVar5b = (unsigned int)pb2[0x13] + 0x960u;
    if (uVar5b > 0x9c4u) {
        assert_print(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103e3e0) /*=0x103e3e0*/, 0x6b7, 0, 0);
        assert_post_action(((unsigned long)&rodata_103e3e0) /*=0x103e3e0*/, 0x6b7);
        __builtin_unreachable();
    }
    p4[0x508/4] = (unsigned int)pb2[0x13];
    p4[0x504/4] = 0x2100625eu; /* DAT_0103395c */
    volatile unsigned int * const p_1033960 = (volatile unsigned int *)0xe000e100; /* DAT_01033960 */
    p_1033960[0x180/4] = 0x100;
    arch_irq_enable(8);
    p4[0x104/4] = uVar5;
    (void)p4[0x104/4]; /* read-back @ 0x41008104 (original 0x0103390e) */
    p4[0x108/4] = uVar5;
    (void)p4[0x108/4]; /* read-back @ 0x41008108 (original 0x01033918) */
    p4[0x110/4] = uVar5;
    (void)p4[0x110/4]; /* read-back @ 0x41008110 (original 0x01033922) */
    FUN_01033b18(1, uVar5);
    FUN_01032988();
    volatile unsigned int * const p_1033964 = (volatile unsigned int *)0x41014000; /* DAT_01033964 */
    p_1033964[0x18/4] = 1;
    return 0;
}
