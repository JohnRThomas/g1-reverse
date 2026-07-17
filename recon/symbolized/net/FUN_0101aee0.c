#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0101aee0 @ 0x0101aee0
 * public-name: FUN_0101aee0
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 *   controller_radio_state_get               <= FUN_01019204 @ 0x01019204
 *   radio_slot_margin_get                    <= FUN_0101a130 @ 0x0101a130
 *   controller_timing_snapshot_build         <= FUN_0101a38c @ 0x0101a38c
 *   sdc_conn_window_admit                    <= FUN_010231c8 @ 0x010231c8
 * address symbols (name @ address):
 *   rodata_101b321                           @ 0x0101b321
 *   g_net_session_state_block                @ 0x210010a0
 */
/* net-core FUN_0101aee0 @ 0x101aee0  (parity 6 trials PROVEN) */
#include <stdint.h>

extern void sdc_assertion_fail(unsigned int a, unsigned int b);
extern void *controller_radio_state_get(void);
extern int radio_slot_margin_get(void);
extern int controller_timing_snapshot_build(void *a, int b, int c, unsigned int d);
extern int FUN_01022e34(unsigned int a, int b);
extern int sdc_conn_window_admit(unsigned char a, void *b);

#define PCVAR2 ((volatile char *)((unsigned long)&g_net_session_state_block) /*=0x210010a0*/)
#define DAT_afa4 (((unsigned long)&rodata_101b321) /*=0x101b321*/)

unsigned int FUN_0101aee0(int param_1, unsigned int param_2)
{
    volatile char *pcVar2;
    volatile unsigned char *puVar3;
    int iVar4;
    int iVar6;
    unsigned int iVar5;
    char cVar1;
    unsigned int uVar7, uVar8;
    unsigned char auStack_30[24];

    pcVar2 = PCVAR2;
    if (*pcVar2 != 0) {
        return 0xc;
    }
    puVar3 = (volatile unsigned char *)controller_radio_state_get();
    cVar1 = *(volatile char *)(param_1 + 0x300);
    *(volatile int *)(pcVar2 + 0x28) = param_1;
    if (cVar1 != 0)
        goto fatal_300;

    pcVar2[1] = 0;
    pcVar2[0x2e] = 0;
    *pcVar2 = 5;
    *(volatile uint16_t *)(pcVar2 + 0x74) = 0;
    pcVar2[0x2c] = 0;
    iVar4 = radio_slot_margin_get();
    iVar5 = 0;
    uVar7 = 0;
    uVar8 = 0;
    do {
        iVar6 = uVar7 + 2;
        uVar8 = uVar8 + 1;
        uVar7 = uVar8 & 0xff;
        iVar5 = iVar5 + iVar4 + *(int *)(pcVar2 + iVar6 * 4);
    } while (uVar7 <= (unsigned char)pcVar2[0x2f]);
    *(volatile int *)(pcVar2 + 0x58) = iVar5;

    iVar5 = FUN_01022e34(DAT_afa4, 0);
    *puVar3 = (unsigned char)iVar5;
    if (iVar5 == 0x20) {
        goto fatal_30e;
    }

    iVar5 = controller_timing_snapshot_build(auStack_30, 1, 0, param_2);
    if (iVar5 == 0) {
        goto fatal_311;
    }

    iVar5 = sdc_conn_window_admit(*puVar3, auStack_30);
    if (iVar5 != 0) {
        return 0;
    }
    sdc_assertion_fail(0x21, 0x312);
    return 0;
fatal_311:
    sdc_assertion_fail(0x21, 0x311);
    return 0;
fatal_30e:
    sdc_assertion_fail(0x21, 0x30e);
    return 0;
fatal_300:
    sdc_assertion_fail(0x21, 0x300);
    return 0;
}
